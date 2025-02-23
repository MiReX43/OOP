#include <iostream>
#include <iomanip>

using namespace std;

const int N = 4; // Размерность матрицы (можно изменить в пределах 4 <= n <= 16)

// Функция заполнения матрицы змейкой
void fillarr(int arr[N][N]) {
    int num = 1;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) { // Четные строки (идем слева направо)
            for (int j = 0; j < N; j++) {
                arr[i][j] = num++;
            }
        }
        else { // Нечетные строки (идем справа налево)
            for (int j = N - 1; j >= 0; j--) {
                arr[i][j] = num++;
            }
        }
    }
}

// Функция вывода матрицы
void printArr(double arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(8) << fixed << setprecision(3) << arr[i][j] << " ";
        }
        cout << endl;
    }
}
 
// Функция вывода целочисленной матрицы
void printArrInt(int arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << arr[i][j] << " ";
        }
        cout << endl; 
    }
}

// Функция нахождения обратной матрицы методом Гаусса-Жордана
bool inverseArr(double arr[N][N], double inverse[N][N]) {
    double augmented[N][2 * N];

    // Создание расширенной матрицы (исходная | единичная)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            augmented[i][j] = arr[i][j];
            augmented[i][j + N] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < N; i++) {
        double diagElement = augmented[i][i];
        if (diagElement == 0) return false; // Матрица необратима

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

    // Копируем результат в inverse
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inverse[i][j] = augmented[i][j + N];
        }
    }

    return true;
}

// Функция умножения матриц
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
 
int main() {

    setlocale(LC_ALL, "RUS");
    int arr[N][N];
    double inverse[N][N];
    double identity[N][N];

    fillarr(arr);

    cout << "Исходная матрица:" << endl;
    printArrInt(arr);

    // Преобразуем в double
    double arrDouble[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arrDouble[i][j] = arr[i][j];

    // Находим обратную матрицу
    if (inverseArr(arrDouble, inverse)) {
        cout << "\nОбратная матрица:" << endl;
        printArr(inverse);

        // Проверяем, является ли обратная матрица корректной
        multiplyMatrices(arrDouble, inverse, identity);
        cout << "\nПроизведение исходной и обратной матрицы (должна быть единичная):" << endl;
        printArr(identity);
    }
    else {
        cout << "\nМатрица необратима (определитель равен 0)." << endl;
    }

    return 0;
}
