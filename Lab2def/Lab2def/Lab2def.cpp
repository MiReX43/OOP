#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

	const int ROW = 5;
	const int COL = 5;
    int plus = 0;
	int arr[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            arr[i][j] = rand() % 201 - 100;
            cout << setw(4) << arr[i][j] << " ";
            if (arr[i][j] >= 0)
            {
                plus++;
            }
        }
        cout << endl;
    }

    cout << "Кол-во неотрицательных элементов массива: " << plus << endl;
  
}