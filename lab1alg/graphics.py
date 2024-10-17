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
        n.append(float(row['n']))  # Преобразуем строки в числа
        T.append(float(row[' T(n)'].strip()))  # Убираем лишний пробел и преобразуем в числа


