#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream> // ��� ������� ������, ���� �����


// --- ������� ������/������ ������ ---

template <typename T>
void saveToFile(const std::string& filename, const std::vector<T>& vec) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "������: �� ������� ������� ���� ��� ������: " << filename << std::endl;
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
        // std::cerr << "����������: �� ������� ������� ���� ��� ������: " << filename << ". ��������, �� ����� ������ �����." << std::endl;
        return; // �� ������, ���� ���� ������ ��� �� ����������
    }
    std::string line;
    vec.clear(); // ������� ������ ����� ���������
    while (std::getline(fin, line)) {
        if (line.empty()) continue; // ���������� ������ ������
        try {
            vec.push_back(T::fromString(line));
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "������ �������� ������ (invalid_argument): " << line << " � ����� " << filename << " - " << ia.what() << std::endl;
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "������ �������� ������ (out_of_range): " << line << " � ����� " << filename << " - " << oor.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "����� ������ �������� ������: " << line << " � ����� " << filename << " - " << e.what() << std::endl;
        }
    }
    fin.close();
}

#endif // FILEMANAGER_H