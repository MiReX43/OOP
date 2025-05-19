#ifndef ROOMCATEGORY_H
#define ROOMCATEGORY_H

#include <string>
#include <vector>
#include <sstream> // для fromString
#include <iostream> // для getServices

using namespace std;
class RoomCategory {
    int id;
    string name;
    string description;
    vector<string> services;

public:
    static int categoryCounter; // Статический счетчик

    RoomCategory(int i, string name, string description, vector<string> services);

    int getId() const;
    string getName() const;
    string getDescription() const;
    const vector<string>& getServicesList() const; // Изменено для получения ссылки на вектор
    void printServices() const; // Переименовано из getServices для ясности

    void setServices(const vector<string>& newServices);

    string toString() const;
    static RoomCategory fromString(const string& line);
};

#endif // ROOMCATEGORY_H