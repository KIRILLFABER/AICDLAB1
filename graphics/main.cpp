#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

const int RANGE = 50000;
const int FROM = 1, TO = 1000, STEP = 1;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// SFML

// ������� ��� ��������� ����� �� ������
void drawPoints(sf::RenderWindow& window, const std::vector<int>& x, const std::vector<int>& y, int maxY) {
    const float pointRadius = 3.0f;  // ������ �����
    const int padding = 50;

    // �������� �� ���� ������
    for (size_t i = 0; i < x.size(); ++i) {
        sf::CircleShape point(pointRadius);
        point.setFillColor(sf::Color::Red);  // ���� �����
        float scaledX = padding + (x[i] / static_cast<float>(x.back())) * (window.getSize().x - 2 * padding);
        float scaledY = window.getSize().y - padding - (y[i] / static_cast<float>(maxY)) * (window.getSize().y - 2 * padding);
        point.setPosition(scaledX - pointRadius, scaledY - pointRadius);  // ������������ � ������ �����
        window.draw(point);  // ������ �����
    }
}

// ������� ��� ��������� ����, ������� � ������� (������ ������������� ��������)
void drawAxesWithTicks(sf::RenderWindow& window, int width, int height, int maxX, int maxY) {
    const int padding = 50;
    const int numTicksX = 10;  // ���������� ������� �� ��� X
    const int numTicksY = 10;  // ���������� ������� �� ��� Y

    // ��� X
    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::White),
        sf::Vertex(sf::Vector2f(width - padding, height - padding), sf::Color::White)
    };

    // ��� Y
    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::White),
        sf::Vertex(sf::Vector2f(padding, padding), sf::Color::White)
    };

    // ������ ���
    window.draw(xAxis, 2, sf::Lines);
    window.draw(yAxis, 2, sf::Lines);

    // ��������� ������� � ���� (������� ������ ��� X � ����� ��� Y)
    sf::Vertex xArrow[] = {
        sf::Vertex(sf::Vector2f(width - padding - 10, height - padding - 5), sf::Color::White),
        sf::Vertex(sf::Vector2f(width - padding, height - padding), sf::Color::White),
        sf::Vertex(sf::Vector2f(width - padding - 10, height - padding + 5), sf::Color::White)
    };
    window.draw(xArrow, 3, sf::TrianglesStrip);

    sf::Vertex yArrow[] = {
        sf::Vertex(sf::Vector2f(padding - 5, padding + 10), sf::Color::White),
        sf::Vertex(sf::Vector2f(padding, padding), sf::Color::White),
        sf::Vertex(sf::Vector2f(padding + 5, padding + 10), sf::Color::White)
    };
    window.draw(yArrow, 3, sf::TrianglesStrip);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "������: �� ������� ��������� �����\n";
        return;
    }

    // ������ ������� � ������� �� ��� X
    for (int i = 1; i <= numTicksX; i++) {
        float tickX = padding + i * (width - 2 * padding) / numTicksX;
        float valueX = i * (maxX / numTicksX);

        // �������
        sf::Vertex tick[] = {
            sf::Vertex(sf::Vector2f(tickX, height - padding - 5), sf::Color::White),
            sf::Vertex(sf::Vector2f(tickX, height - padding + 5), sf::Color::White)
        };
        window.draw(tick, 2, sf::Lines);

        // ������� �������
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(static_cast<int>(valueX)));
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        text.setPosition(tickX - 10, height - padding + 10);
        window.draw(text);
    }

    // ������ ������� � ������� �� ��� Y
    for (int i = 1; i <= numTicksY; i++) {
        float tickY = height - padding - i * (height - 2 * padding) / numTicksY;
        float valueY = i * (maxY / numTicksY);

        // �������
        sf::Vertex tick[] = {
            sf::Vertex(sf::Vector2f(padding - 5, tickY), sf::Color::White),
            sf::Vertex(sf::Vector2f(padding + 5, tickY), sf::Color::White)
        };
        window.draw(tick, 2, sf::Lines);

        // ������� �������
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(static_cast<int>(valueY)));
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        text.setPosition(padding - 40, tickY - 10);
        window.draw(text);
    }

    // ������� ���� X � Y
    sf::Text xLabel("n", font, 15);
    xLabel.setFillColor(sf::Color::White);
    xLabel.setPosition(width - 30, height - 40);
    window.draw(xLabel);

    sf::Text yLabel("T(n)", font, 15);
    yLabel.setFillColor(sf::Color::White);
    yLabel.setPosition(20, 10);
    window.draw(yLabel);
}


// SORT

int findMin(std::vector<int>& arr, int a, int& T) {
    int min = arr[a], min_index = a;
    T += 3;
    for (int i = a + 1; i < arr.size(); i++) {
        T += 2; // ���������
        if (min > arr[i]) {
            min = arr[i];
            min_index = i; // ���������� ������ ������������ ��������
            T += 2;
        }
        T++; // ��������� i
    }
    return min_index;
}

void selectionSort(std::vector<int>& arr, int& T) {
    T = 0;
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
        T++; // ���������
    }
}

void insertionSort(std::vector<int>& arr, int& T) {
    T = 1;  // ������������� �������� ��������
    for (int i = 1; i < arr.size(); i++) {
        int el = arr[i];  // ��������� ������� �������
        T += 2;  // �������� ���������� � �������������

        int j = i;
        while (j > 0 && arr[j - 1] > el) {
            T += 2;  // ���������
            arr[j] = arr[j - 1];  // ����� ��������
            T += 1;  // �������� ����������
            j--;
            T++;  // ��������� j
        }
        arr[j] = el;  // ������� ��������
        T += 1;  // �������� ����������
    }
}

void bubbleSort(std::vector<int>& arr, int& T) {

    bool swapped = true;
    T += 2; // ������������� swapped � i
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
        T += 2; // ��������� ���������
        T++; // i++
    }
    T += 2; // ��������� ���������

}


// ������� ��� ������� ���� ��������������� ��������
std::vector<int> merge(std::vector<int> left, std::vector<int> right, int& T) {
    // ������� ������ ��� �������� ���������� � �������� ����� �������� ���� �������� ��������
    std::vector<int> result((left.size() + right.size()));
    T++; // �������� �������
    T += 3; // i = 0, j = 0, k = 0
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
    T++; // i = 0
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


// FILL



void randomFill(std::vector<int>& arr, int n) {
    srand(time(0));
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

// ������� ��� ������ �������
void printArr(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {

        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {


    std::vector<int> elems;
    std::vector<int> operations;
    printf("Select a sort:\n1 - Seletion Sort\n2 - Insertion Sort\n3 - Bubble Sort\n4 - Merge Sort\n5 - Shell Sort\n6 - Heap Sort\nSort: ");
    int sort;
    std::cin >> sort;
    printf("Select the filling:\n1 - Sorted\n2 - Semi-Sorted\n3 - Sorted on other direction\n4 - Random fill\nFill: ");
    int fill;
    std::cin >> fill;
    switch (sort) {
    case 1:
        switch (fill) {
        case 1:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedFill(arr, n);
                int T = 0;
                selectionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 2:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                semiSortedFill(arr, n);
                int T = 0;
                selectionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 3:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedOtherDirFill(arr, n);
                int T = 0;
                selectionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 4:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                randomFill(arr, n);
                int T = 0;
                selectionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        }
        break;
    case 2:
        switch (fill) {
        case 1:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedFill(arr, n);
                int T = 0;
                insertionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 2:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                semiSortedFill(arr, n);
                int T = 0;
                insertionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 3:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedOtherDirFill(arr, n);
                int T = 0;
                insertionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 4:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                randomFill(arr, n);
                int T = 0;
                insertionSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        }
        break;
    case 3:
        switch (fill) {
        case 1:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedFill(arr, n);
                int T = 0;
                bubbleSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 2:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                semiSortedFill(arr, n);
                int T = 0;
                bubbleSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 3:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedOtherDirFill(arr, n);
                int T = 0;
                bubbleSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 4:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                randomFill(arr, n);
                int T = 0;
                bubbleSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        }
        break;
    case 4:
        switch (fill) {
        case 1:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedFill(arr, n);
                int T = 0;
                arr = mergeSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 2:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                semiSortedFill(arr, n);
                int T = 0;
                arr = mergeSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 3:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                sortedOtherDirFill(arr, n);
                int T = 0;
                arr = mergeSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        case 4:
            for (int n = FROM; n <= TO; n += STEP) {
                std::vector<int> arr;
                randomFill(arr, n);
                int T = 0;
                arr = mergeSort(arr, T);
                elems.push_back(n);
                operations.push_back(T);
            }
            break;
        }
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        return -1;
        break;
    }



















    // ���������� ������������ ���������� �������� ��� ���������������
    int maxOperations = *max_element(operations.begin(), operations.end());

    // ������� ����


    // ������� ����
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Points on OXY Plane");
    window.setFramerateLimit(60);  // ����������� FPS

    // �������� ���� ���������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ������� ���� (������ ���)
        window.clear(sf::Color::Black);

        // ������ ��� � ��������� � ���������
        drawAxesWithTicks(window, WINDOW_WIDTH, WINDOW_HEIGHT, elems.back(), maxOperations);

        // ������ �����
        drawPoints(window, elems, operations, maxOperations);

        // ���������� ���������� ����
        window.display();
    }


    return 0;
}

