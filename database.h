#pragma once // замена #ifndef

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Record {
    int id;
    string name;
    double value;
};

void menu();
void SaveToFile(const vector<Record>& db_vector, const string& filename);
void LoadFromFile(vector<Record>& db_vector, map<int, Record>& book, const string& filename);
void addRecord(vector<Record>& db_vector, map<int, Record>& book);
void printAll(const vector<Record>& db_vector);
void sortRecords(vector<Record>& db_vector);
int findBinary(vector<Record>& db_vector, int i);
void findmap(map<int, Record>& book, vector<Record>& db_vector);
void printStats(vector<Record>& db_vector);
void deleteRecord(vector <Record>& db_vector, map <int, Record>& book);