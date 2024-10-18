import csv
import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

n = []
T = []



# Чтение данных из CSV файла
with open("DATA.csv", "r") as f:
    reader = csv.DictReader(f, delimiter=';')
    for row in reader:
        
        n.append(int(row['n']))
        T.append(int(row[' T(n)']))

        
# Построение графика с точками
plt.scatter(n, T, label='Точки данных')

# Находим коэффициенты полиномиальной регрессии 2-й степени
coefficients = np.polyfit(n, T, 2)  # 2 означает полином второй степени
polynomial_regression = np.poly1d(coefficients)

# Генерация значений для кривой регрессии
x_reg = np.linspace(min(n), max(n), 100)
y_reg = polynomial_regression(x_reg)

# Построение кривой регрессии
plt.plot(x_reg, y_reg, color='red', label='Полиномиальная регрессия (2-й степени)')

# Добавление подписей к осям
plt.xlabel('n')
plt.ylabel('T(n)')

# Заголовок графика
plt.title('График с полиномиальной регрессией')

# Легенда
plt.legend()

# Отображение графика
plt.show()


print(n)
print(T)


