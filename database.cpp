#include "database.h"

void menu() {
    cout << "Меню управления системой базы данных" << endl;
    cout << "1 - Добавить запись" << endl;
    cout << "2 - Вывести все записи" << endl;
    cout << "3 - Найти запись по ID" << endl;
    cout << "4 - Показать статистику" << endl;
    cout << "5 - Сохранить файл" << endl;
    cout << "6 - Удалить запись" << endl;
    cout << "7 - Выход из системы" << endl;
    cout << "Выбирайте действие" << endl;
}

void SaveToFile(const vector <Record>& db_vector, const string& filename) {
    cout << "Сохраняю " << db_vector.size() << " записей в " << filename << endl;
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия базы данных" << endl;
    }

    for (const auto& r : db_vector) {
        file << r.id << "," << r.name << "," << r.value << endl;
    }

    file.close();
    cout << "Данные сохранены в database.txt" << endl;
}

void LoadFromFile(vector<Record>& db_vector, map<int, Record>& book, const string& filename) {
    cout << "Загружаю из файла: " << filename << endl;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Файл не найден " << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idstr, namestr, valuestr;

        getline(ss, idstr, ',');
        getline(ss, namestr, ',');
        getline(ss, valuestr, ',');

        try {
            int id = stoi(idstr);
            double value = stod(valuestr);

            Record rec = {id, namestr, value};
            db_vector.push_back(rec);
            book[id] = rec;
        } catch (const exception& e) {cout << "Ошибка чтения строки" << line << endl;}
    }

    file.close();
    cout << "База данных загружена. Количество записей: " << db_vector.size() << endl;
}

void addRecord(vector <Record>& db_vector, map <int, Record>& book) {
    int id;
    string name;
    double value;

    cout << "Введите ваше айди: ";
    cin >> id;
    cout << "Введите ваше имя: ";
    cin >> name;
    cout << "Введите код доступа: ";
    cin >> value;
    
    if (book.find(id) != book.end()) {
        cout << "Такой пользователь уже имеетс в системе" << endl;
    } else {
        book[id] = {id, name, value};
        db_vector.push_back(book[id]);
    }

}

void printAll(const vector <Record>& db_vector) {
    for (const auto& i : db_vector) {
        cout << "ID: " << i.id << " " << "Имя: " << i.name << " " << "Код доступа: " << i.value << endl;
    }
}

void sortRecords(vector <Record>& db_vector) {
    int n = db_vector.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (db_vector[j].id < db_vector[min_idx].id) {
                min_idx = j;
            }
        }
        Record temp = db_vector[i];
        db_vector[i] = db_vector[min_idx];
        db_vector[min_idx] = temp;
    }
}

int findBinary(vector <Record>& db_vector, int i) {

    int left = 0;
    int right = db_vector.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (db_vector[mid].id == i) {
            return mid;
        } else if (db_vector[mid].id < i) {
            left = mid + 1;
        } else if (db_vector[mid].id > i) {
            right = mid - 1;
        }

    }

    return -1;
}

void findmap(map <int, Record>& book, vector <Record>& db_vector) {
    int i;
    cout << "Введите ID для поиска: ";
    cin >> i;
    
    sortRecords(db_vector);

    auto index = findBinary(db_vector, i);

    if (index != -1) {
        cout << "С таким ID найден пользователь с именем: " << db_vector[index].name << endl;
    } else {
        cout << "Такой пользователь не найден " << endl;
    }

}

void printStats(vector <Record>& db_vector) {
    double sumvalue = 0;
    int maxid = 0;
    int namelen = 0;

    for (size_t i = 0; i < db_vector.size(); i++) {
        if (db_vector[i].id > maxid) {
            maxid = db_vector[i].id;
        }
        if (db_vector[i].name.length() > 5) {
            namelen += 1;
        }
        sumvalue += db_vector[i].value;
    }

    cout << "Статистика: " << endl;
    cout << "Общий код доступа: " << sumvalue << endl;
    cout << "Максимальное ID: " << maxid << endl;
    cout << "Имена с общей длинной больше 5 символово: " << namelen << endl;
}

void deleteRecord(vector <Record>& db_vector, map <int, Record>& book) {
    int id;
    int index = -1;
    cout << "Введите ID для удаления записи из базы данных: ";
    cin >> id;

    if (book.find(id) == book.end()) {
        cerr << "Такого пользователя не существует, проверьте подлинность ID" << endl;
        return;
    }

    for (size_t i = 0; i < db_vector.size(); i++) {
        if (db_vector[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        db_vector.erase(db_vector.begin() + index); 
    }
    book.erase(id);
    cout << "Запись ликвидирована" << endl;
    SaveToFile(db_vector, "database.txt");
}