#include <iostream>
#include <vector>

using namespace std;

const int N = 12; // Количество элементов в массиве
const int RANGE = 50; // Максимальное значение в массиве





void selectionSort(vector<int>& arr);
int findMin(vector<int>& arr, int a);
void printArr(vector<int>& arr);
void insertionSort(vector<int>& arr);
void randomSort(vector<int>& arr);
bool isSorted(vector<int>& arr);
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int> arr);
void quickSort(vector<int>& arr, int left, int right); // Убрать аргументы
void bubbleSort(vector<int>& arr);



// Функция для слияния двух отсортированных массивов
vector<int> merge(vector<int> left, vector<int> right) {
    // Создаем массив для хранения результата с размером суммы размеров двух входящих массивов
    vector<int> result((left.size() + right.size()));
    for (int i = 0, j = 0, k = 0; k < result.size(); k++) {
        // Заполняем результат, выбирая меньший элемент из левого и правого массивов
        result[k] = i < left.size() && (j == right.size() || left[i] < right[j]) ? left[i++] : right[j++];
    }
    return result; // Возвращаем объединенный массив
}

// Функция сортировки слиянием
vector<int> mergeSort(vector<int> arr) {
    // Базовый случай: если массив содержит 1 или 0 элементов, он уже отсортирован
    if (arr.size() == 1) return arr;

    vector<int> left;  // Левый подмассив
    vector<int> right; // Правый подмассив
    // Делим массив на два подмассива
    for (int i = 0; i < arr.size(); i++) {
        if (i < arr.size() / 2)
            left.push_back(arr[i]); // Добавляем элемент в левый подмассив
        else
            right.push_back(arr[i]); // Добавляем элемент в правый подмассив
    }

    // Рекурсивно сортируем левый и правый подмассивы, затем сливаем их
    return merge(mergeSort(left), mergeSort(right));
}








// Функция сортировки выбором
void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int j = findMin(arr, i); // Найти индекс минимального элемента
        // Обмен значений
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int findMin(vector<int>& arr, int a) {
    int min = arr[a], min_index = a;
    for (int i = a + 1; i < arr.size(); i++) {
        if (min > arr[i]) {
            min = arr[i];
            min_index = i; // Запоминаем индекс минимального элемента
        }
    }
    return min_index;
}

// Функция для печати массива
void printArr(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' '; // Вывод i-го элемента
    }
    cout << endl;
}


// Функция сортировки вставками
void insertionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int el = arr[i]; // Сохраняем текущий элемент
        // Сдвигаем элементы, которые больше текущего
        for (int j = i; j > 0 && arr[j - 1] > el; j--) {
            arr[j] = arr[j - 1];
            arr[j - 1] = el; // Вставляем текущий элемент на правильную позицию

        }
    }
}


// Функция случайной соритровки
void randomSort(vector<int>& arr) {
    while (!isSorted(arr)) {
        for (int i = 0; i < arr.size(); i++) {
            // Генерируем случайный индекс для обмена
            int index = rand() % arr.size();
            // Обмен
            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }

}

// Функция для проверки, отсортирован ли массив
bool isSorted(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left > right) return;
    int p = arr[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while (arr[i] < p) i++;
        while (arr[j] > p) j--;
        if (i <= j) {
            int tmp = arr[i];
            arr[i++] = arr[j];
            arr[j--] = tmp;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);



}

void bubbleSort(vector<int>& arr) {
   
    bool swapped = true;
    for (int i = 0; i < arr.size() - 1 && swapped; i++) {
        swapped = false;
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
    }
    
}


int main() {
    vector<int> arr;
    // Заполнение массива случайными числами
    for (int i = 0; i < N; i++) {
        arr.push_back(rand() % RANGE);
    }
    cout << "ARRAY:\n";
    printArr(arr);
    bubbleSort(arr);
    cout << "\n\n\nARRAY AFTER SORT:\n";
    printArr(arr);
    if (isSorted(arr)) cout << "KAIF" << endl;


    return 0;
}