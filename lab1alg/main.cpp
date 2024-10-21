#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

const int RANGE = 50000;
const int FROM = 10000, TO = 100000, STEP = 10000;





void selectionSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
int findMin(vector<int>& arr, int a);
void bubbleSort(vector<int>& arr);
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int> arr);
void shellSort(vector<int>& arr);
void shellSortHibb(vector<int>& arr);
void shellSortPratt(vector<int>& arr);
void quickSort(vector<int>& arr, int start, int end);


void printArr(vector<int>& arr);
bool isSorted(vector<int>& arr);


















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

void shellSort(vector<int>& arr) {
    for (int s = arr.size() / 2; s > 0; s /= 2) {
        for (int i = s; i < arr.size(); i++) {
            for (int j = i - s; j >= 0 && arr[j] > arr[j + s]; j -= s) {
                int temp = arr[j];
                arr[j] = arr[j + s];
                arr[j + s] = temp;
            }
        }
    }
}
void shellSortHibb(vector<int>& arr) {

}
void shellSortPratt(vector<int>& arr) {

}












void quickSort(vector<int>& arr, int start, int end) {
    if (end <= start) return;
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    i++;
    int tmp = arr[i];
    arr[i] = arr[end];
    arr[end] = tmp;
    int p_index = i;
    quickSort(arr, start, p_index - 1);
    quickSort(arr, p_index + 1, end);


}


void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1;  // Левый дочерний элемент
    int right = 2 * i + 2; // Правый дочерний элемент

    // Если левый дочерний элемент больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если самый большой элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]); // Меняем местами

        // Рекурсивно преобразуем затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция для сортировки массива методом Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();
    // Построение max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Извлечение элементов из кучи по одному
    for (int i = n - 1; i >= 0; i--) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // Вызываем heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}







// FILL

void randomFill(std::vector<int>& arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % RANGE);
    }
}

void sortedFill(std::vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr.push_back(i);
    }
}

void semiSortedFill(std::vector<int>& arr, int n) {
    int sorted = n * 0.9;
    int unsorted = n - sorted;
    for (int i = 0; i < sorted - 1; i++) {
        arr.push_back(i);
    }
    for (int i = unsorted; i >= 0; i--) {
        arr.push_back(i);
    }
}

void unSortedFill(std::vector<int>& arr, int n) {
    for (int i = n; i >= 0; i--) {
        arr.push_back(i);
    }
}


// DATA

void fillDataFile() {
    ofstream data_file;
    data_file.open("DATA.csv");
    if (!data_file.is_open()) {
        cout << "ERROR\n";
        return;
    }

    data_file << "sort;fill;n;T(n)\n";
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;RS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;RS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;RS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;RS;" << n << "; " << T << endl;
    }
    
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        int T = 0;
        shellSort(arr);
        data_file << "SHS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        int T = 0;
        shellSort(arr);
        data_file << "SHS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        int T = 0;
        shellSort(arr);
        data_file << "SHS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        int T = 0;
        shellSort(arr);
        data_file << "SHS;RS;" << n << "; " << T << endl;
    }
    
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, 9000);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;RS;" << n << "; " << T << endl;
    }

    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;S;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;SS;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;US;" << n << "; " << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;RS;" << n << "; " << T << endl;
    }

    

 

    

    data_file.close();
    
}




// Функция для печати массива
void printArr(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' '; // Вывод i-го элемента
    }
    cout << endl;
}

// Функция для проверки, отсортирован ли массив
bool isSorted(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}



int main() {

   
    fillDataFile();

    return 0;
}