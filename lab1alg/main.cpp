#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

const int RANGE = 30000; // ������������ �������� �������� ��� ���������� ����������
const int FROM = 20000, TO = 120000, STEP = 10000; // 




// ��������� �������
void selectionSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
int findMin(vector<int>& arr, int a);
void bubbleSort(vector<int>& arr);
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int> arr);
void shellSort(vector<int>& arr);
void shellSortHibb(vector<int>& arr);
void shellSortPratt(vector<int>& arr);
int partition(vector<int>& arr, int low, int high);
void quickSort(vector<int>& arr, int low, int high);
void heapify(vector<int>& arr, int n, int i);
void heapSort(vector<int>& arr);


void printArr(vector<int>& arr);
bool isSorted(vector<int>& arr);
void checkSorts();


// SORTS


// ������� ���������� �������
void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int j = findMin(arr, i); // ����� ������ ������������ ��������
        // ����� ��������
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

// ������� ��� ���������� ������������ ��������
int findMin(vector<int>& arr, int a) {
    int min = arr[a], min_index = a;
    for (int i = a + 1; i < arr.size(); i++) {
        if (min > arr[i]) {
            min = arr[i];
            min_index = i; // ���������� ������ ������������ ��������
        }
    }
    return min_index;
}

// ������� ���������� ���������
void insertionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int el = arr[i]; // ��������� ������� �������
        // �������� ��������, ������� ������ ��������
        for (int j = i; j > 0 && arr[j - 1] > el; j--) {
            arr[j] = arr[j - 1];
            arr[j - 1] = el; // ��������� ������� ������� �� ���������� �������

        }
    }
}


// ������� ���������� ���������
void bubbleSort(vector<int>& arr) {

    bool swapped = true; // ���� ��� ������������ ������������
    for (int i = 0; i < arr.size() - 1 && swapped; i++) {
        swapped = false;
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // ����� ��������
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
    }

}

// ������� ��� ������� ���� ��������������� ��������
vector<int> merge(vector<int> left, vector<int> right) {
    // ������ ��� ������� �����������
    vector<int> result((left.size() + right.size()));
    for (int i = 0, j = 0, k = 0; k < result.size(); k++) {
        // ���������� �������
        result[k] = i < left.size() && (j == right.size() || left[i] < right[j]) ? left[i++] : right[j++];
    }
    return result;
}

// ������� ���������� ��������
vector<int> mergeSort(vector<int> arr) {
    // ������� ������: ���� ������ �������� 1 �������, �� ��� ������������
    if (arr.size() == 1) return arr;

    vector<int> left;  // ����� ���������
    vector<int> right; // ������ ���������
    // ����� ������ �� ��� ����������
    for (int i = 0; i < arr.size(); i++) {
        if (i < arr.size() / 2)
            left.push_back(arr[i]); // ��������� ������� � ����� ���������
        else
            right.push_back(arr[i]); // ��������� ������� � ������ ���������
    }

    // ���������� ��������� ����� � ������ ����������, ����� ������� ��
    return merge(mergeSort(left), mergeSort(right));
}

// ������� ���������� �����
void shellSort(vector<int>& arr) {
     
    for (int s = arr.size() / 2; s > 0; s /= 2) { // ���� �� ����� s
        for (int i = s; i < arr.size(); ++i) {
            // ���������� ������� ������� � ����������, ������������ �� ���������� s
            for (int j = i - s; j >= 0 && arr[j] > arr[j + s]; j -= s) {
                // ����� ��������
                int temp = arr[j];
                arr[j] = arr[j + s];
                arr[j + s] = temp;
            }
        }
    }
}


void shellSortHibb(vector<int>& arr) {
    int i, j, k, increment, temp;
    int val;
    // ���������� ���������� ����
    val = (int)log((float)arr.size() + 1) / log((float)2);
    increment = pow((float)2, val) - 1;
    while (increment > 0)
    {
        for (i = 0; i < increment; i++)
        {
            for (j = 0; j < arr.size(); j += increment)
            {
                temp = arr[j];
                for (k = j - increment; k >= 0 && temp < arr[k]; k -= increment)
                {
                    arr[k + increment] = arr[k]; // �������� �������� ������
                }
                arr[k + increment] = temp; // ��������� ������� temp � ���������� �����
            }
        }
        val--; // ��������� val ��� ���������� ����

        // ���������� ������ �������� ����
        if (increment != 1)
            increment = pow((float)2, val) - 1;
        else
            increment = 0;
    }
}

void shellSortPratt(vector<int>& arr) {
    vector<int> gaps;
    int size = arr.size();

    // ��������� ������������������ ������
    for (int i = 1; i < size; i *= 2)
    {
        for (int j = i; j < size; j *= 3)
        {
            gaps.push_back(j);
        }
    }

    // ���������� ����� �� ��������
    insertionSort(gaps);

    // ���������� ������� �� ������� ����
    for (int gap : gaps)
    {
        for (int i = gap; i < size; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

}











// ������� ��� ��������� ������� �� ��� �����
int partition(vector<int>& arr, int low, int high) {

    int pivot = arr[high]; // ���������� ������� ������� ��� ��������� ������� �������

    
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {

        
        if (arr[j] <= pivot) {
            i++; // ����������� ������ �������� ��������
            // ����� ��������
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            
        }
    }
    // ������ ������� ������� ������� � ��������� �� ������� i + 1
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return (i + 1); // ���������� ������ �������� ��������
}

// ������� ������� ����������
void quickSort(vector<int>& arr, int low, int high) {

    if (low < high) {
        
        int pi = partition(arr, low, high); // ���������� ������� �������� ��������
        quickSort(arr, low, pi - 1); // ������� ���������� ��� ��������� �� ��������
        quickSort(arr, pi + 1, high); // ������� ���������� ��� ��������� ����� ��������
    }
}



void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // �������������� ���������� ������� ��� ������
    int left = 2 * i + 1;  // ����� �������� �������
    int right = 2 * i + 2; // ������ �������� �������

    // ���� ����� �������� ������� ������ �����
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // ���� ����� ������� ������� �� ������
    if (largest != i) {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        

        // ���������� ����������� ���������� ���������
        heapify(arr, n, largest);
    }
}

// ������� ������������� ����������
void heapSort(vector<int>& arr) {
    int n = arr.size();
    // ���������� max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // ���������� ��������� �� ���� �� ������
    for (int i = n - 1; i >= 0; i--) {
        // ���������� ������� ������ � �����
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        // �������� heapify �� ����������� ����
        heapify(arr, i, 0);
    }
}







// FILL


// ������� ���������� ������� ���������� �������
void randomFill(std::vector<int>& arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % RANGE);
    }
}

// ������� ���������� ���������������� �������
void sortedFill(std::vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr.push_back(i);
    }
}

// ������� ���������� ����� ���������������� ������� (90/10)
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

// ������� ���������� ���������������� ������� � �������� �������
void unSortedFill(std::vector<int>& arr, int n) {
    for (int i = n; i > 0; i--) {
        arr.push_back(i);
    }
}


// DATA


// ������� ��� ���������� ����� � �������
void fillDataFile() {
    // �������� ����� � ��� �������� 
    ofstream data_file; 
    data_file.open("DATA.csv"); 
    // �������� ����� �� ��������
    if (!data_file.is_open()) {
        cout << "ERROR\n";
        return;
    }
    // ���������� ����� �������
    data_file << "sort;fill;n;T(n)\n";

    // ���������� �������

    // SELECTION SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        selectionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SS;RS;" << n << ";" << T << endl;
    }

    // INSERTION SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        insertionSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "IS;RS;" << n << ";" << T << endl;
    }

    // BUBBLE SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "BS;RS;" << n << ";" << T << endl;
    }

    // MERGE SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "MS;RS;" << n << ";" << T << endl;
    }

    // SHELL SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHS;RS;" << n << ";" << T << endl;
    }

    // SHELL SORT (HIBBARD)

    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortHibb(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHHS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortHibb(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHHS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortHibb(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHHS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortHibb(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHHS;RS;" << n << ";" << T << endl;
    }

    // SHELL SORT (PRATT)

    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortPratt(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHPS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortPratt(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHPS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortPratt(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHPS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        shellSortPratt(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "SHPS;RS;" << n << ";" << T << endl;
    }

    // QUICK SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "QS;RS;" << n << ";" << T << endl;
    }

    // HEAP SORT
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;S;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        semiSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;SS;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        unSortedFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;US;" << n << ";" << T << endl;
    }
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        randomFill(arr, n);
        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float> duration = end - start;
        float T = duration.count();
        data_file << "HS;RS;" << n << ";" << T << endl;
    }

    
    data_file.close(); // �������� �����
    
}




// ������� ��� ������ �������
void printArr(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' '; // ����� i-�� ��������
    }
    cout << endl;
}

// ������� ��� ��������, ������������ �� ������
bool isSorted(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

// ������� ��� �������� ���� ����������
void checkSorts() {
    int size = 10000;
    vector<int> arr;

    
    randomFill(arr, size);
    // Sellection Sort
    vector<int> selectionArr = arr; 
    selectionSort(selectionArr);
    cout << "Selection Sort: " << (isSorted(selectionArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << selectionArr.size() << endl;

    // Insertion Sort
    vector<int> insertionArr = arr; 
    insertionSort(insertionArr);
    cout << "Insertion Sort: " << (isSorted(insertionArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << insertionArr.size() << endl;

    // Bubble Sort
    vector<int> bubbleArr = arr; 
    bubbleSort(bubbleArr);
    cout << "Bubble Sort: " << (isSorted(bubbleArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << bubbleArr.size() << endl;

    // Merge Sort
    vector<int> mergeArr = arr; 
    mergeArr = mergeSort(mergeArr);
    cout << "Merge Sort: " << (isSorted(mergeArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << mergeArr.size() << endl;

    // Shell Sort
    vector<int> shellArr = arr; 
    shellSort(shellArr);
    cout << "Shell Sort: " << (isSorted(shellArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << shellArr.size() << endl;

    // Shell Sort (Hibbard)
    vector<int> shellHibbArr = arr; 
    shellSortHibb(shellHibbArr);
    cout << "Shell Sort Hibbard: " << (isSorted(shellHibbArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << shellHibbArr.size() << endl;

    // Shell Sort (Pratt)
    vector<int> shellPrattArr = arr; 
    shellSortPratt(shellPrattArr);
    cout << "Shell Sort Pratt: " << (isSorted(shellPrattArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << shellPrattArr.size() << endl;

    // Quick Sort
    vector<int> quickArr = arr; 
    quickSort(quickArr, 0, quickArr.size() - 1);
    cout << "Quick Sort: " << (isSorted(quickArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << quickArr.size() << endl;

    // Heap Sort
    vector<int> heapArr = arr; 
    heapSort(heapArr);
    cout << "Heap Sort: " << (isSorted(heapArr) ? "Sorted" : "Not sorted")
        << ", Size: " << arr.size() << " -> " << heapArr.size() << endl;
}



int main() {
    
    //checkSorts();
   
    fillDataFile();

    return 0;
}