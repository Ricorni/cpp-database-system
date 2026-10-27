#include "database.h"

//Итоговая работа по процедурному программированию на с++ для перехода на ООП на с++
//Задание: Написать систему управления базой данных.

int main() {
    setlocale(LC_ALL, "ru");

    vector <Record> db_vector;
    map <int, Record> book;

    LoadFromFile(db_vector, book, "database.txt"); 

    int choice = 0;

    while (choice != 7) {
        menu();
        cin >> choice;

        switch(choice) {
            case 1: {
                addRecord(db_vector, book);
                break;
            }
            case 2: {
                sortRecords(db_vector);
                printAll(db_vector);
                break;
            }
            case 3: {
                findmap(book, db_vector);
                break;
            }
            case 4: {
                printStats(db_vector);
                break;
            }
            case 5: {
                SaveToFile(db_vector, "database.txt");
                break;
            }
            case 6: {
                deleteRecord(db_vector, book);
                break;
            }
            case 7: {
                SaveToFile(db_vector, "database.txt");
                cout << "Выход " << endl;
                break;
            }
            default: {
                cout << "Не то тыкнул, меняй" << endl;
                break;
            }
        }
    }

    return 0;
}