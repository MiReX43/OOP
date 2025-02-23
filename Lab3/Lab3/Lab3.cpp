#include <iostream>
#include <iomanip>

using namespace std;

const int N = 4; // ����������� ������� (����� �������� � �������� 4 <= n <= 16)

// ������� ���������� ������� �������
void fillarr(int arr[N][N]) {
    int num = 1;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) { // ������ ������ (���� ����� �������)
            for (int j = 0; j < N; j++) {
                arr[i][j] = num++;
            }
        }
        else { // �������� ������ (���� ������ ������)
            for (int j = N - 1; j >= 0; j--) {
                arr[i][j] = num++;
            }
        }
    }
}

// ������� ������ �������
void printArr(double arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(8) << fixed << setprecision(3) << arr[i][j] << " ";
        }
        cout << endl;
    }
}
 
// ������� ������ ������������� �������
void printArrInt(int arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << arr[i][j] << " ";
        }
        cout << endl; 
    }
}

// ������� ���������� �������� ������� ������� ������-�������
bool inverseArr(double arr[N][N], double inverse[N][N]) {
    double augmented[N][2 * N];

    // �������� ����������� ������� (�������� | ���������)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            augmented[i][j] = arr[i][j];
            augmented[i][j + N] = (i == j) ? 1.0 : 0.0;
        }
    }

    // ������ ��� ������ ������
    for (int i = 0; i < N; i++) {
        double diagElement = augmented[i][i];
        if (diagElement == 0) return false; // ������� ����������

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

    // �������� ��������� � inverse
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inverse[i][j] = augmented[i][j + N];
        }
    }

    return true;
}

// ������� ��������� ������
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

    cout << "�������� �������:" << endl;
    printArrInt(arr);

    // ����������� � double
    double arrDouble[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arrDouble[i][j] = arr[i][j];

    // ������� �������� �������
    if (inverseArr(arrDouble, inverse)) {
        cout << "\n�������� �������:" << endl;
        printArr(inverse);

        // ���������, �������� �� �������� ������� ����������
        multiplyMatrices(arrDouble, inverse, identity);
        cout << "\n������������ �������� � �������� ������� (������ ���� ���������):" << endl;
        printArr(identity);
    }
    else {
        cout << "\n������� ���������� (������������ ����� 0)." << endl;
    }

    return 0;
}
