#include <iostream>
#include <fstream>
#include <regex>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    string fileName;
    cout << "������� ��� ����� � ����� C++ (��������: code.cpp): ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "�� ������� ������� ����!" << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // ���������� ��������� ��� ������ for-������
    regex forRegex(R"(for\s*\(.*?\)\s*\{?)");

    smatch matches;
    auto start = code.cbegin();
    auto end = code.cend();

    int count = 0;
    cout << "\n��������� ����� for:\n";
    while (regex_search(start, end, matches, forRegex)) {
        cout << ++count << ") " << matches[0] << endl;
        start = matches.suffix().first;
    }

    if (count == 0) {
        cout << "����� for �� �������." << endl;
    }
    else {
        cout << "\n����� ������� " << count << " ����(��) for." << endl;
    }

    return 0;
}
