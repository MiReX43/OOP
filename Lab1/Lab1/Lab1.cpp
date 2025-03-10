#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateF(double x, double epsilon) {
    double result = 0.0;
    double term = 1.0;
    int n = 1;

    while (fabs(term) > epsilon) {
        term = pow(-1, n - 1) * n * pow(x, n - 1);
        result += term;
        n++;
    }

    return result;
}

int main() {

    setlocale(LC_ALL, "");

    int task;

    // ���� ��� ������ ������
    cout << "�������� ������:" << endl;
    cout << "1. ������ 1" << endl;
    cout << "2. ������ 2" << endl;
    cout << "3. ������ 3" << endl;
    cout << "4. ������ 4" << endl;
    cout << "������� ����� ������: ";
    cin >> task;

    switch (task) {

    case 1: {

        //Ex 1
        double a, b;
        cout << "������� �������� A: ";
        cin >> a;
        cout << "������� �������� B: ";
        cin >> b;

        double result = log((sin(a * a) + cos(b)) / (sqrt(1 + (exp(1.0) / (pow(a, 3) + 3.4 * b)))));
        cout << "���������� ��������� ������������ ��������� �� � � B: " << result << endl;

        break;

    }
    case 2: {

        //Ex 2
 
        const double epsilon = 0.001;
        
        double x1 = 0.1;
        double x2 = 0.77;
        double x3 = -0.9;

        cout << "��������� ��� x1 = 0.1: " << calculateF(x1, epsilon) << endl;
        cout << "��������� ��� x2 = 0.77: " << calculateF(x2, epsilon) << endl;
        cout << "��������� ��� x3 = -0.9: " << calculateF(x3, epsilon) << endl;

        break;

    }
    case 3: {

        //Ex 3
        int subtask;
        cout << "�������� ������� ������� 3:" << endl;
        cout << "1. ������� 3.1" << endl;
        cout << "2. ������� 3.2" << endl;
        cout << "3. ������� 3.3" << endl;
        cout << "4. ������� 3.4" << endl;
        cout << "5. ������� 3.5" << endl;
        cout << "6. ������� 3.6" << endl;
        cout << "7. ������� 3.7" << endl;
        cout << "������� ����� ���������: ";
        cin >> subtask;

        switch (subtask) {
        case 1: {
            //�� ���� ������� ��������� int main(), using namespace std;
            //Ex 3.1
            int n1;
            cout << "������� ����������� �����: ";
            cin >> n1;

            for (int i = 1; i <= n1 / 2; i++) { //������ � ���������� � � ������� �����
                if (n1 % i == 0) { //�������� ��������� 
                    cout << i << " ";
                }
            }
            cout << n1 << endl; //������� ����� n ��� �������� ������ ����
            break;

        }
        case 2: {

            //Ex 3.2

            int n2, y = 1;
            cout << "������� ����������� �����: ";
            cin >> n2;

            if (n2 % 2 != 0) { //���������� ������� ��� �������� ���������� �����
                for (int i = 1; i <= n2; i++) { //��������� ���� ��� �������� n
                    y *= i;
                }
            }
            else {
                for (int i = 2; i <= n2; i += 2) { //��������� ���� ��� ������ n
                    y *= i;
                }
            }

            cout << y << endl; //��������� �����
            break;

        }
        case 3: {

            //Ex 3.3

            int n3;
            double P = 1.0;

            cout << "������� ����� n: ";
            cin >> n3;

            for (int i = 2; i <= n3; i += 2) { // ��������� ���� ��������� ������ �������� i c ����� +2 � �������� ���������� �����
                P *= (i * 1.0) / (i + 1); // ���������� ���������� P 
            }

            for (int i = 1; i <= n3; i += 2) { // ��������� ���� ��������� �������� �������� i c ����� +2
                P *= (i + 1) * 1.0 / i;
            }

            cout << P << endl;

            break;

        }
        case 4: {

            //Ex 3.4

            //���������� ������ � ���������� ����������
            int n4;
            double c, res = 0.0;

            cout << "������� n: ";
            cin >> n4;
            cout << "������� x: ";
            cin >> c;

            //���������� �����, ��������� ���������� �������
            for (int k = 1; k <= n4; k++) {
                double r = 0.0; //��������� r ����� ������ ����� k
                for (int m = k; m <= n4; m++) {
                    r += (c + k) / (1.0 * m); //���������� ������� ��� ��������� ������������� ����������
                }
                res += r;
            }

            cout << "���������: " << res << endl;

            break;

        }
        case 5: {

            //Ex 3.5

            int i, j, n5;
            float sum1, sum2;

            cout << "n: ";
            cin >> n5;

            sum1 = 0;
            sum2 = 0;

            // ���������� ������ � ����� for:
            // 1. � ����� i ������ ���� �� 1 �� n (i <= n)
            // 2. � ����� j ������ ���� �� 1 �� i (j <= i)
            for (i = 1; i <= n5; i++) {
                for (j = 1; j <= i; j++) {
                    // � ������� 1 / (i + 2 * j) ���� �����������
                    sum1 = sum1 + (1.0 / (i + 2 * j)); // ���������� 1.0 ��� ������ ���������� � ��������� ������
                }
            }

            sum2 = sum1 + sum2;

            // ��������� �����, ����������� ���������� ��������� ��� ���������������� ������
            cout << sum2 << endl;
            break;

        }
        case 6: {

            //Ex 3.6

            float d, e, f; // ���������� ���������� ��� ���� �����
            int n = 0; // ������� ���������� �����, ������� ������ ����� �������

            cout << "a1 = ";
            cin >> e; // ��������� ���������� ��������� ������ � ����� ��� ������� �����
            cout << "a2 = ";
            cin >> f;

            // ���� ���������� 198 ����� � ���������
            for (int i = 3; i <= 200; i++) { // ��������� ���� ���������� � i = 3, ������ ��� ������ ��� ����� ��� �������
                cout << "a" << i << " = ";
                cin >> d;

                // ��������, ��� ������� ����� ������ ����������� � ����������
                if (f > e && d < f) { // ���������� �������� �������, ��� c ������ b � a ������ c
                    n++;
                }

                e = f;
                f = d;
            }

            cout << "���������� �����, ������� ������ ����� �������: " << n << endl;
            break;

        }
        case 7: {

            //Ex 3.7

            int i, j;
            float p1;

            p1 = 1;

            // ����������: ���� ������ ���� �� 1 �� 20 ��� i
            for (i = 1; i <= 20; i++) {
                // ��������� ���� �� 1 �� 20 ��� j
                for (j = 1; j <= 20; j++) {
                    // ���������� ���������� ������������� ������� ��� ������������
                    p1 = p1* (1.0 / (i + pow(j, 2))); // ���������� pow(j, 2) ��� ���������� � �������
                }
            }

            cout << p1 << endl;

            break;
        }
            
        }
        break;
    }
    case 4: {

        //Ex 4
        double h;
        cout << "������� �������� y: ";
        cin >> h;

        if (h > -2 && h < 2) {
            cout << "�������� � ���������" << endl;
        }
        else {
            cout << "�������� ��� ���������" << endl;
        }
        break;

    }

    }
}

