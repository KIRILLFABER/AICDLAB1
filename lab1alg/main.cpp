#include <iostream>
#include <vector>

using namespace std;

const int N = 12; // ���������� ��������� � �������
const int RANGE = 50; // ������������ �������� � �������





void selectionSort(vector<int>& arr);
int findMin(vector<int>& arr, int a);
void printArr(vector<int>& arr);
void insertionSort(vector<int>& arr);
void randomSort(vector<int>& arr);
bool isSorted(vector<int>& arr);
vector<int> merge(vector<int> left, vector<int> right);
vector<int> mergeSort(vector<int> arr);
void quickSort(vector<int>& arr, int left, int right); // ������ ���������
void bubbleSort(vector<int>& arr);



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

// ������� ��� ������ �������
void printArr(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' '; // ����� i-�� ��������
    }
    cout << endl;
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


// ������� ��������� ����������
void randomSort(vector<int>& arr) {
    while (!isSorted(arr)) {
        for (int i = 0; i < arr.size(); i++) {
            // ���������� ��������� ������ ��� ������
            int index = rand() % arr.size();
            // �����
            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }

}

// ������� ��� ��������, ������������ �� ������
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
    // ���������� ������� ���������� �������
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