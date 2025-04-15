#include <iostream>
#include <fstream>
#include <regex>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    string fileName;
    cout << "Введите имя файла с кодом C++ (например: code.cpp): ";
    cin >> fileName;

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Регулярное выражение для поиска for-циклов
    regex forRegex(R"(for\s*\(.*?\)\s*\{?)");

    smatch matches;
    auto start = code.cbegin();
    auto end = code.cend();

    int count = 0;
    cout << "\nНайденные циклы for:\n";
    while (regex_search(start, end, matches, forRegex)) {
        cout << ++count << ") " << matches[0] << endl;
        start = matches.suffix().first;
    }

    if (count == 0) {
        cout << "Циклы for не найдены." << endl;
    }
    else {
        cout << "\nВсего найдено " << count << " цикл(ов) for." << endl;
    }

    return 0;
}
