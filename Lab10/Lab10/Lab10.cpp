#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <cmath>
#include <algorithm>
#include <mutex>

using namespace std;

// �������� ������� ��� ���������� ����������� ������ ��������
int gcd(int x, int y) {
    while (x != y) {
        if (x < y) {
            y -= x;
        }
        else {
            x -= y;
        }
    }
    return x; // ��� y, ��� ��� x == y
}

// ������� ��� ��������, �������� �� ����� �������
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (gcd(n, i) != 1) {
            return false;
        }
    }
    return true;
}

// ��������� ��� �������� ������ ������
struct ThreadData {
    int start, end;
    int priority;
    vector<int> primes;
    mutex mtx;
};

// ������� ��� ������ ������� ����� � ���������
void findPrimesInRange(ThreadData& data) {
    vector<int> localPrimes;
    for (int i = data.start; i <= data.end; ++i) {
        if (isPrime(i)) {
            localPrimes.push_back(i);
        }
    }

    // �������� ������ � ����� ������ � �������������� ��������
    lock_guard<mutex> lock(data.mtx);
    data.primes.insert(data.primes.end(), localPrimes.begin(), localPrimes.end());

    // ������������� ��� ������������ ������
    cout << "����� [" << data.start << " - " << data.end << "] � ����������� " << data.priority << ": ";
    for (int i = 0; i < data.priority; ++i) cout << "#";
    cout << endl;
}

int main() {
    setlocale(LC_ALL,"RUS");
    int start, end, numThreads;
    cout << "������� ������ ���������: ";
    cin >> start;
    cout << "������� ����� ���������: ";
    cin >> end;
    cout << "������� ���������� �������: ";
    cin >> numThreads;

    // ��������� �������� �� ����� ��� �������
    int rangePerThread = (end - start + 1) / numThreads;
    vector<thread> threads;
    vector<ThreadData> threadData(numThreads);
    atomic<int> priorityCounter(1);  // ���������� ��� ���������� �����������

    for (int i = 0; i < numThreads; ++i) {
        threadData[i].start = start + i * rangePerThread;
        threadData[i].end = (i == numThreads - 1) ? end : start + (i + 1) * rangePerThread - 1;
        threadData[i].priority = priorityCounter++; // ������������� ��������� ��� ������� ������
        threads.push_back(thread(findPrimesInRange, ref(threadData[i])));
    }

    // ������� ���������� ���� �������
    for (auto& th : threads) {
        th.join();
    }

    // �������� � ������� ��� ��������� ������� �����
    vector<int> allPrimes;
    for (const auto& data : threadData) {
        allPrimes.insert(allPrimes.end(), data.primes.begin(), data.primes.end());
    }

    // ��������� � ������� ��� ������� �����
    sort(allPrimes.begin(), allPrimes.end());
    cout << "���������� ����� � ��������� [" << start << ", " << end << "]: ";
    for (int prime : allPrimes) {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}
