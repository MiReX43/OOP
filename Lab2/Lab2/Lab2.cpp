#include <iostream>

using namespace std;

int main() {

	setlocale(LC_ALL,"RUS");

	const int N = 10;

	//Ex3

	int array[N];

	cout << "Введите " << N << " элементов массива:" << endl;
	for (int i = 0; i < N; i++) {
		cin >> array[i];
	}

	for (int i = 0; i < N - 1; i++) 
	{
		for (int j = 0; j < N - 1 - i; j++) 
		{
			if (array[j] > array[j + 1]) 
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}

	cout << "Отсортированный массив: ";
	for (int i = 0; i < N; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	//Ex2


	const int ROW = 6;
	const int COL = 5;

	int matrix[ROW][COL];
	int res[COL];

	cout << "Введите элементы массива 6x5" << endl;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cin >> matrix[i][j];
		}
	}

	cout << "Исходный масиив: \n";
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	for (int j = 0; j < COL; j++)
	{
		res[j] = 0;
		for (int i = 0; i < ROW; i++)
		{
			if (matrix[i][j] % 2 == 0)
			{
				res[j] = matrix[i][j];
				break;
			}
		}
	}

	cout << "Одномерный массив: ";
	for (int j = 0; j < COL; j++)
	{
		cout << res[j] << "";
	}
	cout << endl;

	//Ex1

	int arr[N];

	srand(time(0));
	
	cout << "Массив: ";
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % 201 - 100;
		cout << arr[i] << " ";
	}

	cout << endl;

	int min = arr[0];
	for (int i = 1; i < N; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	cout << "Минимальный элемент: " << min << endl;

	int sum = 0;

	for (int i = 0; i < N; i++)
	{
		sum += arr[i];
	}
	cout << "Сумма элемнтов массива: " << sum << endl;

	cout << "Положительные элеменыт: ";
	for (int i = 0; i < N; i++)
	{
		if (arr[i] > 0)
		{
			cout << arr[i] << " ";
		}
	}
	cout << endl;
}