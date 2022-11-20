import numpy as np # подключаем numpy для работы с векторами
import matplotlib.pyplot as plt # подключаем matplotlib для построения графиков

L = np.genfromtxt("L.txt", delimiter=",") # Вводим в numpy массив последовательность из файла, delimiter - разделитель в файле
X = np.genfromtxt("X.txt", delimiter=",")
F = np.genfromtxt("F.txt", delimiter=",")

mesh = np.genfromtxt("mesh.txt", delimiter=",")
Fmesh = np.genfromtxt("Fmesh.txt", delimiter=",")

Params = np.genfromtxt("Params.txt", delimiter=",")


plt.figure(figsize=(16*2, 9*2)) # 16 на 9 - соотношение экрана, умножить на 2 - увеличиваю картинку
plt.plot(mesh,Fmesh, color = 'C0', label = "f(x)") # добавляем на него график исходной функции
plt.scatter(X,F, color = 'red', s = 16) # добавляем на него график исходной функции
#label добавляет описание в легенду
plt.plot(mesh,L, color = 'C1', label = 'L(x)') # теперь график многочлена Лагранжа, o добавляет точки, r красный, "-" между ними говорит, что цвет относится к графику, а не к точкам
plt.ylabel('y') # подписываем ось x
plt.xlabel('x') # подписываем ось y
plt.xlim([Params[0], Params[1]]) # рисуем график на отрезке [a,b]
plt.legend() # выводим легенду
plt.grid(True)
plt.savefig('plot.png') # сохраняем график в файл 'plot.png'
plt.show() # рисуем график на экране