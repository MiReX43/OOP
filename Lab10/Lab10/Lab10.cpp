#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <cmath>
#include <algorithm>
#include <mutex>

using namespace std;

// Алгоритм Евклида для нахождения наибольшего общего делителя
int gcd(int x, int y) {
    while (x != y) {
        if (x < y) {
            y -= x;
        }
        else {
            x -= y;
        }
    }
    return x; // или y, так как x == y
}

// Функция для проверки, является ли число простым
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (gcd(n, i) != 1) {
            return false;
        }
    }
    return true;
}

// Структура для хранения данных потока
struct ThreadData {
    int start, end;
    int priority;
    vector<int> primes;
    mutex mtx;
};

// Функция для поиска простых чисел в диапазоне
void findPrimesInRange(ThreadData& data) {
    vector<int> localPrimes;
    for (int i = data.start; i <= data.end; ++i) {
        if (isPrime(i)) {
            localPrimes.push_back(i);
        }
    }

    // Защищаем доступ к общим данным с использованием мьютекса
    lock_guard<mutex> lock(data.mtx);
    data.primes.insert(data.primes.end(), localPrimes.begin(), localPrimes.end());

    // Псевдографика для визуализации потока
    cout << "Поток [" << data.start << " - " << data.end << "] с приаритетом " << data.priority << ": ";
    for (int i = 0; i < data.priority; ++i) cout << "#";
    cout << endl;
}

int main() {
    setlocale(LC_ALL,"RUS");
    int start, end, numThreads;
    cout << "Введите начало диапазона: ";
    cin >> start;
    cout << "Введите конец диапазона: ";
    cin >> end;
    cout << "Введите количество потоков: ";
    cin >> numThreads;

    // Разбиваем диапазон на части для потоков
    int rangePerThread = (end - start + 1) / numThreads;
    vector<thread> threads;
    vector<ThreadData> threadData(numThreads);
    atomic<int> priorityCounter(1);  // Переменная для управления приоритетом

    for (int i = 0; i < numThreads; ++i) {
        threadData[i].start = start + i * rangePerThread;
        threadData[i].end = (i == numThreads - 1) ? end : start + (i + 1) * rangePerThread - 1;
        threadData[i].priority = priorityCounter++; // Устанавливаем приоритет для каждого потока
        threads.push_back(thread(findPrimesInRange, ref(threadData[i])));
    }

    // Ожидаем завершения всех потоков
    for (auto& th : threads) {
        th.join();
    }

    // Собираем и выводим все найденные простые числа
    vector<int> allPrimes;
    for (const auto& data : threadData) {
        allPrimes.insert(allPrimes.end(), data.primes.begin(), data.primes.end());
    }

    // Сортируем и выводим все простые числа
    sort(allPrimes.begin(), allPrimes.end());
    cout << "Предельные числа в диапазоне [" << start << ", " << end << "]: ";
    for (int prime : allPrimes) {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}
