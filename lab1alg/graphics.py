import csv
import numpy as np
import matplotlib.pyplot as plt
from sympy import *

# Границы для теоретических графиков
FROM = 10
TO = 30

#Размеры окна
X = 12
Y = 8


def plotTheor(T_w, T_b, T_a, n, title, filename, CX = FROM, CY = 30):

    p1 = plot(T_w, T_b, T_a, (n, FROM, TO), title = title, xlabel = "n", ylabel = "T(n)", size = (X, Y), label = ("Worst case", "Best case", "Average case"), axis_center = (CX, CY), show = False, legend = True)
    p1.save(filename)



    





def createTable():
    with open("TABLE.csv", "w") as w_file:
        names = ["Сортировка", "Заполнение", "Количество элементов", "Время сортировки(сек)"]
        writer = csv.DictWriter(w_file, delimiter = ";", lineterminator="\r", fieldnames=names)
        writer.writeheader()
        
        
        sorts = ["SS", "IS", "BS", "MS", "SHS", "SHHS", "SHPS", "QS", "HS"] # Список сортировок
        fills = ["S", "SS", "US", "RS"] # Список видов заполнения


        for sort in sorts:
            for fill in fills:
                # Запись заголовков в таблицу
                writer.writerow({"Сортировка": sort, "Заполнение": fill})
                n = []  # Список для количества элементов
                T = []  # Список для времени сортировки
                readData(n, T, sort, fill)  # Чтение данных из файла
                for i in range(len(n)):
                    writer.writerow({"Количество элементов": n[i], "Время сортировки(сек)": T[i]})
                # Добавление пустых строк для удобства чтения
                
            for i in range(5):
                    writer.writerow({"Количество элементов": ' ', "Время сортировки(сек)": ' '})
            writer.writerow({"Сортировка": "Сортировка", "Заполнение": "Заполнение", "Количество элементов" : "Количество элементов", "Время сортировки(сек)": "Время сортировки(сек)"})

        





def reg(n, T, col, index):
    # Находим коэффициенты регрессии 2-й степени
    coefficients = np.polyfit(n, T, 2)
    polynomial_regression = np.poly1d(coefficients)


    # Генерация значений для кривой регрессии
    x_reg = np.linspace(min(n), max(n), 100)
    y_reg = polynomial_regression(x_reg)

    # Построение кривой регрессии
    plt.plot(x_reg, y_reg, color=col)


    a, b, c = coefficients
    

    # Выводим уравнение в правом верхнем углу с небольшим смещением
    # Сдвигаем уравнение по вертикали с учетом порядка кривой
    plt.text(0.95,  0.95 - 0.05 * index, f"y = ({a:.2e})n^2 + ({b:.2e})n + ({c:.2e})", transform=plt.gca().transAxes,
             fontsize=10, color=col, ha='right', va='top')



def printGraphics(data_n, data_T, title, filename):
    plt.clf() # Очистка
    plt.figure(figsize=(X, Y))
    # Построение графика с точками
    plt.scatter(data_n[0], data_T[0], label='Sorted')
    plt.scatter(data_n[1], data_T[1], label='Semi-Sorted')
    plt.scatter(data_n[2], data_T[2], label='Unsorted')
    plt.scatter(data_n[3], data_T[3], label='Random fill')

    # Построение регрессионных кривых
    reg(data_n[0], data_T[0], 'blue', 0)
    reg(data_n[1], data_T[1], 'orange', 1)
    reg(data_n[2], data_T[2], 'green', 2)
    reg(data_n[3], data_T[3], 'red', 3)

    # Добавление подписей
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title(title)
    plt.legend()

    # Сохранение графика
    plt.savefig(filename)
    #plt.show()


def printGraphicsAverage(data_n, data_T, title, filename):
    plt.clf() # Очистка
    plt.figure(figsize=(X, Y))
    # Построение графика с точками
    
    plt.scatter(data_n[0], data_T[0], label='Selection Sort')
    plt.scatter(data_n[1], data_T[1], label='Insertion Sort')
    plt.scatter(data_n[2], data_T[2], label='Bubble Sort')
    plt.scatter(data_n[3], data_T[3], label='Merge Sort')
    plt.scatter(data_n[4], data_T[4], label='Shell Sort')
    plt.scatter(data_n[5], data_T[5], label='Shell Sort (Hibbard)')
    plt.scatter(data_n[6], data_T[6], label='Shell Sort (Pratt)')
    plt.scatter(data_n[7], data_T[7], label='Quick Sort')
    plt.scatter(data_n[8], data_T[8], label='Heap Sort')

    # Построение регрессионных кривых
    reg(data_n[0], data_T[0], 'blue', 0)
    reg(data_n[1], data_T[1], 'orange' , 1)
    reg(data_n[2], data_T[2], 'green', 2)
    reg(data_n[3], data_T[3], 'red', 3)
    reg(data_n[4], data_T[4], 'purple', 4)
    reg(data_n[5], data_T[5], 'brown', 5)
    reg(data_n[6], data_T[6], 'pink', 6)
    reg(data_n[7], data_T[7], 'gray', 7)
    reg(data_n[8], data_T[8], 'y', 8)

    # Добавление подписей
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title(title)
    plt.legend()

    # Сохранение графика
    plt.savefig(filename)
    

    # Отдельный вывод линейных сортировок

    plt.clf() # Очистка
    

    plt.scatter(data_n[3], data_T[3], label='Merge Sort')
    plt.scatter(data_n[4], data_T[4], label='Shell Sort')
    plt.scatter(data_n[5], data_T[5], label='Shell Sort (Hibbard)')
    plt.scatter(data_n[6], data_T[6], label='Shell Sort (Pratt)')
    plt.scatter(data_n[7], data_T[7], label='Quick Sort')
    plt.scatter(data_n[8], data_T[8], label='Heap Sort')

    reg(data_n[3], data_T[3], 'blue', 0)
    reg(data_n[4], data_T[4], 'orange' , 1)
    reg(data_n[5], data_T[5], 'green', 2)
    reg(data_n[6], data_T[6], 'red', 3)
    reg(data_n[7], data_T[7], 'purple', 4)
    reg(data_n[8], data_T[8], 'brown', 5)

    # Добавление подписей
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title(title)
    plt.legend()

    # Сохранение графика
    plt.savefig("PracGraphics\ALL(LIN).png")

    # Отдельный вывод квадратичных сортировок
    plt.clf() # Очистка
    

    plt.scatter(data_n[0], data_T[0], label='Selection Sort')
    plt.scatter(data_n[1], data_T[1], label='Insertion Sort')
    plt.scatter(data_n[2], data_T[2], label='Bubble Sort')

    reg(data_n[0], data_T[0], 'blue', 0)
    reg(data_n[1], data_T[1], 'orange' , 1)
    reg(data_n[2], data_T[2], 'green', 2)
    

    # Добавление подписей
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title(title)
    plt.legend()

    # Сохранение графика
    plt.savefig("PracGraphics\ALL(S).png")
    

    

    

def readData(n, T, sort, fill):
    n.clear()  # Очистка списка n
    T.clear()  # Очистка списка T
    with open("DATA.csv", "r") as r_file:
        reader = csv.DictReader(r_file, delimiter=";")  # Чтение данных из DATA
        for row in reader:
            
            if(row["sort"] == sort and row["fill"] == fill):
                n.append(int(row["n"]))  # Количество элементов
                T.append(float(row["T(n)"]))  # Время сортировки
    
# Очистка данных           
def clearData():
    global n_s, T_s, n_ss, T_ss, n_us, T_us, n_rs, T_rs
    n_s.clear()
    T_s.clear()
    n_ss.clear()
    T_ss.clear()
    n_us.clear()
    T_us.clear()
    n_rs.clear()
    T_rs.clear()


def plotSort(sort, name, filename):
    clearData()  # Очищаем данные перед новой отрисовкой
    # Чтение данных
    readData(n_s, T_s, sort, "S")
    readData(n_ss, T_ss, sort, "SS")
    readData(n_us, T_us, sort, "US")
    readData(n_rs, T_rs, sort, "RS")
    data_n = [n_s, n_ss, n_us, n_rs]
    data_T = [T_s, T_ss, T_us, T_rs]
    # Отрисовка графика
    printGraphics(data_n, data_T, name, filename)



def plotSortAverage(filename):
    # Списки для времени и количества элементов каждой сортировки
    T_1 = [] 
    T_2 = [] 
    T_3 = []
    T_4 = [] 
    T_5 = [] 
    T_6 = []
    T_7 = []
    T_8 = [] 
    T_9 = []
    n_1 = [] 
    n_2 = [] 
    n_3 = []
    n_4 = [] 
    n_5 = [] 
    n_6 = []
    n_7 = []
    n_8 = [] 
    n_9 = []
    
    # Чтение данных
    readData(n_1, T_1, "SS", "RS")
    readData(n_2, T_2, "IS", "RS")
    readData(n_3, T_3, "BS", "RS")
    readData(n_4, T_4, "MS", "RS")
    readData(n_5, T_5, "SHS", "RS")
    readData(n_6, T_6, "SHHS", "RS")
    readData(n_7, T_7, "SHPS", "RS")
    readData(n_8, T_8, "QS", "RS")
    readData(n_9, T_9, "HS", "RS")

    data_T = [T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_8, T_9]
    data_n = [n_1, n_2, n_3, n_4, n_5, n_6, n_7, n_8, n_9]
    # Отрисовка графика
    printGraphicsAverage(data_n, data_T, "Sorts (Average case)", filename)




# Графики для теории
n = Symbol('n')

# Графики для каждой сортировки (все случаи на одном изображении)
# Selection Sort
title = "Selection Sort"
T_w = 5 * n ** 2 + 3 * n + 1
T_b = 3 * n ** 2 + 4 * n + 1
T_a = 4 * n ** 2 + 7 * n + 1

plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\SS.png')




# plot1.save('TheorGraphics\SS.png')

# Insertion Sort
title = "Insertion Sort"

T_w = 3 * n ** 2 + 7 * n + 1
T_b = 6 * n + 1
T_a = 3 * n ** 2 + 4 * n + 1
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\IS.png')


# Bubble Sort
title = "Bubble Sort"

T_w = 7 * n ** 2 - 10 * n + 5
T_b = 3 * n + 3
T_a = 5 * n ** 2 - n - 2
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\BS.png')


# Merge Sort
title = "Merge Sort"

T_w = 2 * n + log(n, 2) * (6 * n + 5)
T_b = 2 * n + log(n, 2) * (6 * n + 5)
T_a = 2 * n + log(n, 2) * (6 * n + 5) 
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\MS.png', CY = 200)
# Shell Sort
title = "Shell Sort"

T_w = n ** 2
T_b = n ** 1.667
T_a = n ** 1.5
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\SHS.png')



# Shell Sort (Hibbard)
title = "Shell Sort (Hibbard)"

T_w = n ** 2
T_b = n * log(n, 2)
T_a = n ** 1.25
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\SHHS.png', CY = 10)
# Shell Sort (Pratt)
title = "Shell Sort (Pratt)"

T_w = n * log(2, n) ** 2
T_b = n
T_a = n * log(2, n) ** 2
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\SHPS.png', CY = 0)

# Quick Sort
title = "Quick Sort"

T_w = n ** 2 + 2 * n
T_b = n + 2 * n * log(n, 2) - log(n, 2)
T_a = 3 * n + 3 * n * log(n, 3) + 2

plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\QS.png')
# Heap Sort
title = "Heap Sort"
T_w = n * log(n, 2)
T_b = n * log(n, 2)
T_a = n * log(n, 2)
plotTheor(T_w, T_b, T_a, n, title, 'TheorGraphics\HS.png')



# График всех сортировок в среднем случае
title = "Sorts (Average case)"
T_1 = 4 * n ** 2 + 7 * n + 1
T_2 = 3 * n ** 2 + 4 * n + 1
T_3 = 5 * n ** 2 - n - 2
T_4 = 2 * n + log(n, 2) * (6 * n + 5) ###
T_5 = n ** 1.5
T_6 = n ** 1.25
T_7 = n * log(2, n) ** 2
T_8 = 3 * n + 3 * n * log(n, 3) + 2
T_9 = n * log(n, 2)

plot1 = plot(T_1, (n, FROM, TO), show = False, label = "Selection sort", xlabel = "n", ylabel = "T(n)", title = title, axis_center = (FROM, 0), size = (X, Y))
plot2 = plot(T_2, (n, FROM, TO), show = False, label = "Insertion Sort")
plot3 = plot(T_3, (n, FROM, TO), show = False, label = "Bubble Sort")
plot4 = plot(T_4, (n, FROM, TO), show = False, label = "Merge Sort")
plot5 = plot(T_5, (n, FROM, TO), show = False, label = "Shell Sort")
plot6 = plot(T_6, (n, FROM, TO), show = False, label = "Shell Sort (Hibbard)")
plot7 = plot(T_7, (n, FROM, TO), show = False, label = "Shell Sort (Pratt)")
plot8 = plot(T_8, (n, FROM, TO), show = False, label = "Quick Sort")
plot9 = plot(T_9, (n, FROM, TO), show = False, label = "Heap Sort")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.extend(plot4)
plot1.extend(plot5)
plot1.extend(plot6)
plot1.extend(plot7)
plot1.extend(plot8)
plot1.extend(plot9)
plot1.legend = True



plot1.save('TheorGraphics\ALL.png')


# Графики для практики



# Графики для каждой сортировки (каждое заполнение)
n_s = []
T_s = []
n_ss = []
T_ss = []
n_us = []
T_us = []
n_rs = []
T_rs = []

plotSort("SS", "Selection Sort", "PracGraphics\SS.png")
plotSort("IS", "Insertion Sort", "PracGraphics\IS.png")
plotSort("BS", "Bubble Sort", "PracGraphics\BS.png")
plotSort("MS", "Merge Sort", "PracGraphics\MS.png")
plotSort("SHHS", "Shell Sort (Hibbard)", "PracGraphics\SHHS.png")
plotSort("SHPS", "Shell Sort (Pratt)", "PracGraphics\SHPS.png")
plotSort("SHS", "Shell Sort", "PracGraphics\SHS.png")
plotSort("QS", "Quick Sort", "PracGraphics\QS.png")
plotSort("HS", "Heap Sort", "PracGraphics\HS.png")
plotSortAverage("PracGraphics\ALL.png")

createTable() # Создание более удобной таблицы для прочтения
    








        





