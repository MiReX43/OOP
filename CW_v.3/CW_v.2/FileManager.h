#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream> // Для отладки ошибок, если нужно

using namespace std;
// --- Функции чтения/записи данных ---

template <typename T>
void saveToFile(const string& filename, const vector<T>& vec) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для записи: " << filename << endl;
        return;
    }
    for (const auto& item : vec) {
        fout << item.toString() << "\n";
    }
    fout.close();
}

template <typename T>
void loadFromFile(const string& filename, vector<T>& vec) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        // cerr << "Информация: Не удалось открыть файл для чтения: " << filename << ". Возможно, он будет создан позже." << endl;
        return; // Не ошибка, если файл просто еще не существует
    }
    string line;
    vec.clear(); // Очищаем вектор перед загрузкой
    while (getline(fin, line)) {
        if (line.empty()) continue; // Пропускаем пустые строки
        try {
            vec.push_back(T::fromString(line));
        }
        catch (const invalid_argument& ia) {
            cerr << "Ошибка парсинга строки (invalid_argument): " << line << " в файле " << filename << " - " << ia.what() << endl;
        }
        catch (const out_of_range& oor) {
            cerr << "Ошибка парсинга строки (out_of_range): " << line << " в файле " << filename << " - " << oor.what() << endl;
        }
        catch (const exception& e) {
            cerr << "Общая ошибка парсинга строки: " << line << " в файле " << filename << " - " << e.what() << endl;
        }
    }
    fin.close();
}

#endif // FILEMANAGER_H