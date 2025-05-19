#ifndef ROOMCATEGORY_H
#define ROOMCATEGORY_H

#include <string>
#include <vector>
#include <sstream> // ��� fromString
#include <iostream> // ��� getServices

using namespace std;
class RoomCategory {
    int id;
    string name;
    string description;
    vector<string> services;

public:
    static int categoryCounter; // ����������� �������

    RoomCategory(int i, string name, string description, vector<string> services);

    int getId() const;
    string getName() const;
    string getDescription() const;
    const vector<string>& getServicesList() const; // �������� ��� ��������� ������ �� ������
    void printServices() const; // ������������� �� getServices ��� �������

    void setServices(const vector<string>& newServices);

    string toString() const;
    static RoomCategory fromString(const string& line);
};

#endif // ROOMCATEGORY_H