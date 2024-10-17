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

// Функция для рисования точек на экране
void drawPoints(sf::RenderWindow& window, const std::vector<int>& x, const std::vector<int>& y, int maxY) {
    const float pointRadius = 3.0f;  // Радиус точек
    const int padding = 50;

    // Проходим по всем точкам
    for (size_t i = 0; i < x.size(); ++i) {
        sf::CircleShape point(pointRadius);
        point.setFillColor(sf::Color::Red);  // Цвет точки
        float scaledX = padding + (x[i] / static_cast<float>(x.back())) * (window.getSize().x - 2 * padding);
        float scaledY = window.getSize().y - padding - (y[i] / static_cast<float>(maxY)) * (window.getSize().y - 2 * padding);
        point.setPosition(scaledX - pointRadius, scaledY - pointRadius);  // Масштабируем и рисуем точку
        window.draw(point);  // Рисуем точку
    }
}

// Функция для рисования осей, делений и стрелок (только положительные значения)
void drawAxesWithTicks(sf::RenderWindow& window, int width, int height, int maxX, int maxY) {
    const int padding = 50;
    const int numTicksX = 10;  // Количество делений на оси X
    const int numTicksY = 10;  // Количество делений на оси Y

    // Ось X
    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::White),
        sf::Vertex(sf::Vector2f(width - padding, height - padding), sf::Color::White)
    };

    // Ось Y
    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(padding, height - padding), sf::Color::White),
        sf::Vertex(sf::Vector2f(padding, padding), sf::Color::White)
    };

    // Рисуем оси
    window.draw(xAxis, 2, sf::Lines);
    window.draw(yAxis, 2, sf::Lines);

    // Добавляем стрелки к осям (стрелка вправо для X и вверх для Y)
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
        std::cerr << "Ошибка: не удалось загрузить шрифт\n";
        return;
    }

    // Рисуем деления и подписи на оси X
    for (int i = 1; i <= numTicksX; i++) {
        float tickX = padding + i * (width - 2 * padding) / numTicksX;
        float valueX = i * (maxX / numTicksX);

        // Деление
        sf::Vertex tick[] = {
            sf::Vertex(sf::Vector2f(tickX, height - padding - 5), sf::Color::White),
            sf::Vertex(sf::Vector2f(tickX, height - padding + 5), sf::Color::White)
        };
        window.draw(tick, 2, sf::Lines);

        // Подпись деления
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(static_cast<int>(valueX)));
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        text.setPosition(tickX - 10, height - padding + 10);
        window.draw(text);
    }

    // Рисуем деления и подписи на оси Y
    for (int i = 1; i <= numTicksY; i++) {
        float tickY = height - padding - i * (height - 2 * padding) / numTicksY;
        float valueY = i * (maxY / numTicksY);

        // Деление
        sf::Vertex tick[] = {
            sf::Vertex(sf::Vector2f(padding - 5, tickY), sf::Color::White),
            sf::Vertex(sf::Vector2f(padding + 5, tickY), sf::Color::White)
        };
        window.draw(tick, 2, sf::Lines);

        // Подпись деления
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(static_cast<int>(valueY)));
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        text.setPosition(padding - 40, tickY - 10);
        window.draw(text);
    }

    // Подпись осей X и Y
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
        T += 2; // Сравнения
        if (min > arr[i]) {
            min = arr[i];
            min_index = i; // Запоминаем индекс минимального элемента
            T += 2;
        }
        T++; // Инкремент i
    }
    return min_index;
}

void selectionSort(std::vector<int>& arr, int& T) {
    T = 0;
    T++; // Инициализация i
    for (int i = 0; i < arr.size(); i++) {
        T++; // сравнение
        int j = findMin(arr, i, T); // Найти индекс минимального элемента
        T++; // Инициализация j
        // Обмен значений
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        T += 3; // Обмен значений
        T++; // Инкремент
    }
}

void insertionSort(std::vector<int>& arr, int& T) {
    T = 1;  // Инициализация счётчика операций
    for (int i = 1; i < arr.size(); i++) {
        int el = arr[i];  // Сохраняем текущий элемент
        T += 2;  // Операции сохранения и инициализации

        int j = i;
        while (j > 0 && arr[j - 1] > el) {
            T += 2;  // Сравнение
            arr[j] = arr[j - 1];  // Сдвиг элемента
            T += 1;  // Операция присвоения
            j--;
            T++;  // Декремент j
        }
        arr[j] = el;  // Вставка элемента
        T += 1;  // Операция присвоения
    }
}

void bubbleSort(std::vector<int>& arr, int& T) {

    bool swapped = true;
    T += 2; // Инициализация swapped и i
    for (int i = 0; i < arr.size() - 1 && swapped; i++) {
        T += 2; // Сравнение
        swapped = false;
        T += 2;
        for (int j = 0; j < arr.size() - i - 1; j++) {
            T += 2; // Сравнение
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
                T += 4;
            }
            T++; //j++
        }
        T += 2; // Последнее сравнение
        T++; // i++
    }
    T += 2; // Последнее сравнение

}


// Функция для слияния двух отсортированных массивов
std::vector<int> merge(std::vector<int> left, std::vector<int> right, int& T) {
    // Создаем массив для хранения результата с размером суммы размеров двух входящих массивов
    std::vector<int> result((left.size() + right.size()));
    T++; // Создание массива
    T += 3; // i = 0, j = 0, k = 0
    for (int i = 0, j = 0, k = 0; k < result.size(); k++) {
        T++; // Сравнение
        // Заполняем результат, выбирая меньший элемент из левого и правого массивов
        result[k] = i < left.size() && (j == right.size() || left[i] < right[j]) ? left[i++] : right[j++];
        T += 4;
        T++; // k++
        T++; // i++ or j++
    }
    T++; // Последнее сравнение
    T++; // return
    return result; // Возвращаем объединенный массив
}

// Функция сортировки слиянием
std::vector<int> mergeSort(std::vector<int> arr, int& T) {
    // Базовый случай: если массив содержит 1 или 0 элементов, он уже отсортирован
    if (arr.size() == 1) {
        T++; // return
        return arr;
    }
    T++; // Сравнение

    std::vector<int> left;  // Левый подмассив
    std::vector<int> right; // Правый подмассив
    T += 2; // Создание массивов
    // Делим массив на два подмассива
    T++; // i = 0
    for (int i = 0; i < arr.size(); i++) {
        T += 2; // Сравнения
        if (i < arr.size() / 2) {
            left.push_back(arr[i]); // Добавляем элемент в левый подмассив
            T++;
        }
        else {
            right.push_back(arr[i]); // Добавляем элемент в правый подмассив
            T++;
        }

        T++; // i++
    }
    T++; // Последнее сравение
    T++; // return
    // Рекурсивно сортируем левый и правый подмассивы, затем сливаем их
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

// Функция для печати массива
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



















    // Определяем максимальное количество операций для масштабирования
    int maxOperations = *max_element(operations.begin(), operations.end());

    // Размеры окна


    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Points on OXY Plane");
    window.setFramerateLimit(60);  // Ограничение FPS

    // Основной цикл программы
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очищаем окно (черный фон)
        window.clear(sf::Color::Black);

        // Рисуем оси с делениями и стрелками
        drawAxesWithTicks(window, WINDOW_WIDTH, WINDOW_HEIGHT, elems.back(), maxOperations);

        // Рисуем точки
        drawPoints(window, elems, operations, maxOperations);

        // Отображаем содержимое окна
        window.display();
    }


    return 0;
}

