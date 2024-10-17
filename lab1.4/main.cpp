#include <iostream>
#include <vector>

using namespace std;


void printArr(vector<int>& arr);
void shellSort(vector<int>& arr);

void shellSort(vector<int>& arr) {
	
	for (int d = arr.size() / 2; d > 1; d /= 2)
	{
		for (int i = 0; i < d; i++) {
			if (arr[i] > arr[i + d]) {
				int tmp = arr[i];
				arr[i] = arr[i + d];
				arr[i + d] = tmp;
			}
		}
	}
	
	
	
	
}

// Функция для печати массива
void printArr(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << ' '; // Вывод i-го элемента
	}
	cout << endl; // Печатаем переход на новую строку
}


int main() {
	vector<int> arr = { 2, 4, 8, 5, 1, 3, 7 };
	shellSort(arr);
	printArr(arr);


}