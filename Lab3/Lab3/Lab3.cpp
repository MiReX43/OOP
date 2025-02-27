#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int N = 5; // Размерность матрицы

// Заполнение змейкой
void fillarr(int arr[N][N]) {
    int num = 0;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < N; j++) {
                arr[i][j] = num++;
            }
        }
        else {
            for (int j = N - 1; j >= 0; j--) {
                arr[i][j] = num++;
            }
        }
    }
}

// Вывод double-матрицы
void printArr(double arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(12) << fixed << setprecision(6) << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// Вывод int-матрицы
void printArrInt(int arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << arr[i][j] << " ";
        }
        cout << endl;
    }
}

// Проверка детерминанта (через разложение Гаусса)
double determinant(double arr[N][N]) {
    double temp[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = arr[i][j];

    double det = 1.0;
    for (int i = 0; i < N; i++) {
        if (fabs(temp[i][i]) < 1e-9) return 0; // Если диагональный элемент ≈ 0, то det = 0
        det *= temp[i][i];
        for (int j = i + 1; j < N; j++) {
            double factor = temp[j][i] / temp[i][i];
            for (int k = i; k < N; k++) {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }
    return det;
}

// Обратная матрица (Гаусс-Жордан)
bool inverseArr(double arr[N][N], double inverse[N][N]) {
    double augmented[N][2 * N];

    // Создание расширенной матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            augmented[i][j] = arr[i][j];
            augmented[i][j + N] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Прямой ход
    for (int i = 0; i < N; i++) {
        double diagElement = augmented[i][i];
        if (fabs(diagElement) < 1e-9) return false;

        for (int j = 0; j < 2 * N; j++) {
            augmented[i][j] /= diagElement;
        }

        for (int k = 0; k < N; k++) {
            if (k != i) {
                double factor = augmented[k][i];
                for (int j = 0; j < 2 * N; j++) {
                    augmented[k][j] -= factor * augmented[i][j];
                }
            }
        }
    }

    // Записываем обратную часть
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverse[i][j] = augmented[i][j + N];

    return true;
}

// Умножение матриц
void multiplyMatrices(double A[N][N], double B[N][N], double result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Округление почти единичной матрицы
void roundIdentity(double arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(arr[i][j]) < 1e-6) arr[i][j] = 0; // Убираем шум
            if (fabs(arr[i][j] - 1) < 1e-6) arr[i][j] = 1; // Округляем к 1
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int arr[N][N];
    double inverse[N][N], identity[N][N];

    fillarr(arr);

    cout << "Исходная матрица:\n";
    printArrInt(arr);

    // Конвертируем в double
    double arrDouble[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arrDouble[i][j] = arr[i][j];

    // Проверка детерминанта
    double det = determinant(arrDouble);
    if (fabs(det) < 1e-9) {
        cout << "\nМатрица необратима (определитель = 0)." << endl;
        return 0;
    }

    // Нахождение обратной матрицы
    if (inverseArr(arrDouble, inverse)) {
        cout << "\nОбратная матрица:\n";
        printArr(inverse);

        // Проверяем обратность
        multiplyMatrices(arrDouble, inverse, identity);
        roundIdentity(identity);
        cout << "\nПроизведение исходной и обратной матрицы (= единичная):\n";
        printArr(identity);
    }
    else {
        cout << "\nОшибка: не удалось найти обратную матрицу!" << endl;
    }

    return 0;
}
