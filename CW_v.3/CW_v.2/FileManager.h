#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream> // ��� ������� ������, ���� �����

using namespace std;
// --- ������� ������/������ ������ ---

template <typename T>
void saveToFile(const string& filename, const vector<T>& vec) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "������: �� ������� ������� ���� ��� ������: " << filename << endl;
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
        // cerr << "����������: �� ������� ������� ���� ��� ������: " << filename << ". ��������, �� ����� ������ �����." << endl;
        return; // �� ������, ���� ���� ������ ��� �� ����������
    }
    string line;
    vec.clear(); // ������� ������ ����� ���������
    while (getline(fin, line)) {
        if (line.empty()) continue; // ���������� ������ ������
        try {
            vec.push_back(T::fromString(line));
        }
        catch (const invalid_argument& ia) {
            cerr << "������ �������� ������ (invalid_argument): " << line << " � ����� " << filename << " - " << ia.what() << endl;
        }
        catch (const out_of_range& oor) {
            cerr << "������ �������� ������ (out_of_range): " << line << " � ����� " << filename << " - " << oor.what() << endl;
        }
        catch (const exception& e) {
            cerr << "����� ������ �������� ������: " << line << " � ����� " << filename << " - " << e.what() << endl;
        }
    }
    fin.close();
}

#endif // FILEMANAGER_H