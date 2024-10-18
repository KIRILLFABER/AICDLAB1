#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

const int RANGE = 50000;
const int FROM = 1, TO = 1000, STEP = 100;





void selectionSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
int findMin(vector<int>& arr, int a);
void bubbleSort(vector<int>& arr);
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int> arr);
void shellSort(vector<int>& arr);
void quickSort(vector<int>& arr, int start, int end);


void selectionSort(vector<int>& arr, int& T);
void insertionSort(vector<int>& arr, int& T);
int findMin(vector<int>& arr, int a, int& T);
void bubbleSort(vector<int>& arr, int& T);
vector<int> merge(vector<int> left, vector<int> right, int& T);
vector<int> mergeSort(vector<int> arr, int& T);
void shellSort(vector<int>& arr, int& T);
void quickSort(vector<int>& arr, int start, int end, int& T);
void heapSort(vector<int>& arr, int& T);





void printArr(vector<int>& arr);
bool isSorted(vector<int>& arr);


















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

// ������� ��� ������� ���� ��������������� ��������
vector<int> merge(vector<int> left, vector<int> right) {
    // ������� ������ ��� �������� ���������� � �������� ����� �������� ���� �������� ��������
    vector<int> result((left.size() + right.size()));
    for (int i = 0, j = 0, k = 0; k < result.size(); k++) {
        // ��������� ���������, ������� ������� ������� �� ������ � ������� ��������
        result[k] = i < left.size() && (j == right.size() || left[i] < right[j]) ? left[i++] : right[j++];
    }
    return result; // ���������� ������������ ������
}

// ������� ���������� ��������
vector<int> mergeSort(vector<int> arr) {
    // ������� ������: ���� ������ �������� 1 ��� 0 ���������, �� ��� ������������
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

void shellSort(vector<int>& arr) {

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
        swap(arr[i], arr[largest]); // ������ �������

        // ���������� ����������� ���������� ���������
        heapify(arr, n, largest);
    }
}

// �������� ������� ��� ���������� ������� ������� Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();
    // ���������� max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // ���������� ��������� �� ���� �� ������
    for (int i = n - 1; i >= 0; i--) {
        // ���������� ������� ������ � �����
        swap(arr[0], arr[i]);

        // �������� heapify �� ����������� ����
        heapify(arr, i, 0);
    }
}





// ���������� ���������� ��� �������� ��������


int findMin(std::vector<int>& arr, int a, int& T) {
    int min = arr[a], min_index = a;
    T += 3; // �������������
    for (int i = a + 1; i < arr.size(); i++) {
        T += 2; // ���������
        if (min > arr[i]) {
            min = arr[i];
            min_index = i;
            T += 2;
        }
        T++; // i++
    }
    T++; // ��������� ���������
    T++; // return
    return min_index;
}

void selectionSort(std::vector<int>& arr, int& T) {
    T++; // ������������� i
    for (int i = 0; i < arr.size(); i++) {
        T++; // ���������
        int j = findMin(arr, i, T); // ����� ������ ������������ ��������
        T++; // ������������� j
        // ����� ��������
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        T += 3; // ����� ��������
        T++; // i++
    }
    T++; // ��������� ���������
}

void insertionSort(std::vector<int>& arr, int& T) {
    T++; // �������������
    for (int i = 1; i < arr.size(); i++) {
        T++; // ���������
        int el = arr[i];  // ��������� ������� �������
        T++; // �������������

        int j = i;
        T++; // ������������
        while (j > 0 && arr[j - 1] > el) {
            T += 2;  // ���������
            arr[j] = arr[j - 1];  // ����� ��������
            T += 1;  // �������� ����������
            j--;
            T++;  // j--
        }
        T++; // ��������� ���������
        arr[j] = el;  // ������� ��������
        T++;  // �������� ����������
    }
    T++; // ��������� ���������
}

void bubbleSort(std::vector<int>& arr, int& T) {

    bool swapped = true;
    T += 2; // �������������
    for (int i = 0; i < arr.size() - 1 && swapped; i++) {
        T += 2; // ���������
        swapped = false;
        T += 2;
        for (int j = 0; j < arr.size() - i - 1; j++) {
            T += 2; // ���������
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
                T += 4;
            }
            T++; //j++
        }
        T++; // ��������� ���������
        T++; // i++
    }
    T++; // ��������� ���������

}


// ������� ��� ������� ���� ��������������� ��������
std::vector<int> merge(std::vector<int> left, std::vector<int> right, int& T) {
    // ������� ������ ��� �������� ���������� � �������� ����� �������� ���� �������� ��������
    std::vector<int> result((left.size() + right.size()));
    T++; // �������� �������
    T += 3; // �������������
    for (int i = 0, j = 0, k = 0; k < result.size(); k++) {
        T++; // ���������
        // ��������� ���������, ������� ������� ������� �� ������ � ������� ��������
        result[k] = i < left.size() && (j == right.size() || left[i] < right[j]) ? left[i++] : right[j++];
        T += 4;
        T++; // k++
        T++; // i++ or j++
    }
    T++; // ��������� ���������
    T++; // return
    return result; // ���������� ������������ ������
}

// ������� ���������� ��������
std::vector<int> mergeSort(std::vector<int> arr, int& T) {
    // ������� ������: ���� ������ �������� 1 ��� 0 ���������, �� ��� ������������
    if (arr.size() == 1) {
        T++; // return
        return arr;
    }
    T++; // ���������

    std::vector<int> left;  // ����� ���������
    std::vector<int> right; // ������ ���������
    T += 2; // �������� ��������
    // ����� ������ �� ��� ����������
    T++; // �������������
    for (int i = 0; i < arr.size(); i++) {
        T += 2; // ���������
        if (i < arr.size() / 2) {
            left.push_back(arr[i]); // ��������� ������� � ����� ���������
            T++;
        }
        else {
            right.push_back(arr[i]); // ��������� ������� � ������ ���������
            T++;
        }

        T++; // i++
    }
    T++; // ��������� ��������
    T++; // return
    // ���������� ��������� ����� � ������ ����������, ����� ������� ��
    return merge(mergeSort(left, T), mergeSort(right, T), T);
}

void shellSort(vector<int>& arr, int& T) {

}

void quickSort(vector<int>& arr, int start, int end, int& T) {
    T++; // ���������
    if (end <= start) {
        T++; // return
        return;
    }
    int pivot = arr[end];
    int i = start - 1;
    T += 3;
    for (int j = start; j < end; j++) {
        T += 2; // ���������
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            T += 5;
        }
        T++; // j++
    }
    T++; // ��������� ���������
    i++;
    int tmp = arr[i];
    arr[i] = arr[end];
    arr[end] = tmp;
    int p_index = i;
    T += 5;
    quickSort(arr, start, p_index - 1, T);
    quickSort(arr, p_index + 1, end, T);


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

void sortedOtherDirFill(std::vector<int>& arr, int n) {
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
    data_file << "n; T(n)\n";
    for (int n = FROM; n < TO; n += STEP) {
        vector<int> arr;
        sortedOtherDirFill(arr, n);
        int T = 0;
        quickSort(arr, 0, arr.size() - 1, T);
        data_file << n << "; " << T << endl;
    }

    

    data_file.close();
    
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



int main() {

   
    fillDataFile();

    return 0;
}