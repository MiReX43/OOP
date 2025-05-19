#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream> // Для отладки ошибок, если нужно


// --- Функции чтения/записи данных ---

template <typename T>
void saveToFile(const std::string& filename, const std::vector<T>& vec) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }
    for (const auto& item : vec) {
        fout << item.toString() << "\n";
    }
    fout.close();
}

template <typename T>
void loadFromFile(const std::string& filename, std::vector<T>& vec) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        // std::cerr << "Информация: Не удалось открыть файл для чтения: " << filename << ". Возможно, он будет создан позже." << std::endl;
        return; // Не ошибка, если файл просто еще не существует
    }
    std::string line;
    vec.clear(); // Очищаем вектор перед загрузкой
    while (std::getline(fin, line)) {
        if (line.empty()) continue; // Пропускаем пустые строки
        try {
            vec.push_back(T::fromString(line));
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Ошибка парсинга строки (invalid_argument): " << line << " в файле " << filename << " - " << ia.what() << std::endl;
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Ошибка парсинга строки (out_of_range): " << line << " в файле " << filename << " - " << oor.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Общая ошибка парсинга строки: " << line << " в файле " << filename << " - " << e.what() << std::endl;
        }
    }
    fin.close();
}

#endif // FILEMANAGER_H