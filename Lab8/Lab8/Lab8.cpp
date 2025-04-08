#include <iostream>
#include <new>       // ��� std::bad_alloc
#include <exception> // ��� ������������ �� std::exception
using namespace std;


// ����� ����������������� ����������
class MemoryAllocationException : public exception {
public:
    const char* what() const noexcept override {
        return "������: �� ������� �������� ������!";
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    try {
        cout << "������� �������� ������� ���� ������...\n";

        // ������� �������� ����� ������� ���� ������
        size_t size = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
        int* hugeArray = new(nothrow) int[size];

        if (!hugeArray) {
            throw MemoryAllocationException(); // ��������� ����������
        }

        // ���� ������ �������� �������
        cout << "������ ������� ��������!" << endl;
        delete[] hugeArray;

    }
    catch (const MemoryAllocationException& e) {
        // ��������� ����������������� ����������
        cout << e.what() << endl;
    }
    catch (const bad_alloc& e) {
        // ��������� ������������ ���������� bad_alloc
        cout << "std::bad_alloc: " << e.what() << endl;
    }
    catch (...) {
        // ��������� ���� ��������� ����������
        cout << "��������� ����������� ����������!" << endl;
    }

    cout << "\n��������� ��������� ���������." << endl;
    return 0;
}
