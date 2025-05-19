#ifndef ROOMCATEGORY_H
#define ROOMCATEGORY_H

#include <string>
#include <vector>
#include <sstream> // для fromString
#include <iostream> // для getServices


class RoomCategory {
    int id;
    std::string name;
    std::string description;
    std::vector<std::string> services;

public:
    static int categoryCounter; // Статический счетчик

    RoomCategory(int i, std::string name, std::string description, std::vector<std::string> services);

    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    const std::vector<std::string>& getServicesList() const; // Изменено для получения ссылки на вектор
    void printServices() const; // Переименовано из getServices для ясности

    void setServices(const std::vector<std::string>& newServices);

    std::string toString() const;
    static RoomCategory fromString(const std::string& line);
};

#endif // ROOMCATEGORY_H