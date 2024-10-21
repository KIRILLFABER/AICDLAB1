import csv
import sympy as sp
import numpy as np
import matplotlib.pyplot as plt
from sympy import *

FROM = 10000
TO = 100000

def reg(n, T, col):
    # Находим коэффициенты полиномиальной регрессии 2-й степени
    coefficients = np.polyfit(n, T, 2)  # 2 означает полином второй степени
    polynomial_regression = np.poly1d(coefficients)

    # Генерация значений для кривой регрессии
    x_reg = np.linspace(min(n), max(n), 100)
    y_reg = polynomial_regression(x_reg)

    # Построение кривой регрессии
    plt.plot(x_reg, y_reg, color=col)


def printGraphics(data_n, data_T, title, filename):
    plt.clf()
    # Построение графика с точками
    plt.scatter(data_n[0], data_T[0], label='Sorted')
    plt.scatter(data_n[1], data_T[1], label='Semi-Sorted')
    plt.scatter(data_n[2], data_T[2], label='Unsorted')
    plt.scatter(data_n[3], data_T[3], label='Random fill')

    reg(data_n[0], data_T[0], 'blue')
    reg(data_n[1], data_T[1], 'orange')
    reg(data_n[2], data_T[2], 'green')
    reg(data_n[3], data_T[3], 'red')

    # Добавление подписей к осям
    plt.xlabel('n')
    plt.ylabel('T(n)')

    # Заголовок графика
    plt.title(title)

    # Легенда
    plt.legend()

    # Отображение графика
    plt.savefig(filename)
    #plt.show()


    
            

def readData(n, T, sort, fill):
    n.clear()
    T.clear()
    with open("DATA.csv", "r") as r_file:
        reader = csv.DictReader(r_file, delimiter=";")
        for row in reader:
            if(row["sort"] == sort and row["fill"] == fill):
                n.append(int(row["n"]))
                T.append(float(row["T(n)"]))
    
                
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

# Графики для каждой сортировки (каждое заполнение)
def plotSort(sort, name, filename):
    clearData()  # Очищаем данные перед новой отрисовкой
    readData(n_s, T_s, sort, "S")
    readData(n_ss, T_ss, sort, "SS")
    readData(n_us, T_us, sort, "US")
    readData(n_rs, T_rs, sort, "RS")
    data_n = [n_s, n_ss, n_us, n_rs]
    data_T = [T_s, T_ss, T_us, T_rs]
    printGraphics(data_n, data_T, name, filename)




# Графики для теории
n = Symbol('n')

# Графики для каждой сортировки (все случаи на одном изображении)
# Selection Sort
title = "Selection Sort"
T_w = 5 * n ** 2 + 3 * n + 1
T_b = 3 * n ** 2 + 4 * n + 1
T_a = 4 * n ** 2 + 7 * n + 1
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\SS.png')

# Insertion Sort
title = "Insertion Sort"

T_w = 3 * n ** 2 + 7 * n + 1
T_b = 6 * n + 1
T_a = 3 * n ** 2 + 4 * n + 1
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\IS.png')
# Bubble Sort
title = "Bubble Sort"

T_w = 7 * n ** 2 - 10 * n + 5
T_b = 3 * n + 3
T_a = 5 * n ** 2 - n - 2
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\BS.png')
# Merge Sort
title = "Merge Sort"

T_w = 2 * n + log(n, 2) * (6 * n + 5)
T_b = 2 * n + log(n, 2) * (6 * n + 5)
T_a = 2 * n + log(n, 2) * (6 * n + 5) ###
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\MS.png')
# Shell Sort
title = "Shell Sort"

T_w = 5 * n ** 2 + 3 * n + 1
T_b = 3 * n ** 2 + 4 * n + 1
T_a = 3 * n ** 2 + 4 * n + 1 ###
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\SHS.png')
# Quick Sort
title = "Quick Sort"

T_w = n ** 2 + 2 * n
T_b = n + 2 * n * log(n, 2) - log(n, 2)
T_a = 3 * n ** 2 + 4 * n + 1 ###
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\QS.png')
# Heap Sort
title = "Heap Sort"
T_w = 5 * n ** 2 + 3 * n + 1
T_b = 3 * n ** 2 + 4 * n + 1
T_a = 3 * n ** 2 + 4 * n + 1 ###
plot1 = plot(T_w, (n, FROM, TO), show = False, label = "Worst case", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_b, (n, FROM, TO), show = False, label = "Best case")
plot3 = plot(T_a, (n, FROM, TO), show = False, label = "Average case")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.legend = True



plot1.save('TheorGraphics\HS.png')


# Графики для каждой сортировки (все случаи на разных изображениях)


# График всех сортировок в среднем случае
title = "Sorts (Average case)"
T_1 = 1
T_2 = 2
T_3 = 3
T_4 = 4
T_5 = 5
T_6 = 6
T_7 = 7

plot1 = plot(T_1, (n, FROM, TO), show = False, label = "Selection sort", xlabel = "n", ylabel = "T(n)", title = title)
plot2 = plot(T_2, (n, FROM, TO), show = False, label = "Insertion Sort")
plot3 = plot(T_3, (n, FROM, TO), show = False, label = "Bubble Sort")
plot4 = plot(T_4, (n, FROM, TO), show = False, label = "Merge Sort")
plot5 = plot(T_5, (n, FROM, TO), show = False, label = "Shell Sort")
plot6 = plot(T_6, (n, FROM, TO), show = False, label = "Quick Sort")
plot7 = plot(T_7, (n, FROM, TO), show = False, label = "Heap Sort")

plot1.extend(plot2)
plot1.extend(plot3)
plot1.extend(plot4)
plot1.extend(plot5)
plot1.extend(plot6)
plot1.extend(plot7)
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
plotSort("SHS", "Shell Sort", "PracGraphics\SHS.png")
plotSort("QS", "Quick Sort", "PracGraphics\QS.png")
plotSort("HS", "Heap Sort", "PracGraphics\HS.png")




    




# Графики для каждой сортировки отедльно по типу заполнения

    


        
        

        






