#include <iostream>
#include <new>       // Для std::bad_alloc
#include <exception> // Для наследования от std::exception
using namespace std;


// Класс пользовательского исключения
class MemoryAllocationException : public exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: не удалось выделить память!";
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    try {
        cout << "Попытка выделить большой блок памяти...\n";

        // Попытка выделить ОЧЕНЬ большой блок памяти
        size_t size = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
        int* hugeArray = new(nothrow) int[size];

        if (!hugeArray) {
            throw MemoryAllocationException(); // Генерация исключения
        }

        // Если память выделена успешно
        cout << "Память успешно выделена!" << endl;
        delete[] hugeArray;

    }
    catch (const MemoryAllocationException& e) {
        // Обработка пользовательского исключения
        cout << e.what() << endl;
    }
    catch (const bad_alloc& e) {
        // Обработка стандартного исключения bad_alloc
        cout << "std::bad_alloc: " << e.what() << endl;
    }
    catch (...) {
        // Обработка всех остальных исключений
        cout << "Произошло неизвестное исключение!" << endl;
    }

    cout << "\nПрограмма завершена корректно." << endl;
    return 0;
}
