import numpy as np # подключаем numpy для работы с векторами
import matplotlib.pyplot as plt # подключаем matplotlib для построения графиков

L = np.genfromtxt("L.txt", delimiter=",") # Вводим в numpy массив последовательность из файла, delimiter - разделитель в файле
X = np.genfromtxt("X.txt", delimiter=",")
X1 = np.genfromtxt("X1.txt", delimiter=",")
FX = np.genfromtxt("FX.txt", delimiter=",")
FX1 = np.genfromtxt("FX1.txt", delimiter=",")
Params = np.genfromtxt("P.txt", delimiter=",")


plt.figure() # создаем пустой график
plt.plot(X1,FX1, color = 'C0', label = "f(x)") # добавляем на него график исходной функции
plt.scatter(X,FX, color = 'red') # добавляем на него график исходной функции
#label добавляет описание в легенду
plt.plot(X1,L, color = 'C1', label = 'L(x)') # теперь график многочлена Лагранжа, o добавляет точки, r красный, "-" между ними говорит, что цвет относится к графику, а не к точкам
plt.ylabel('y') # подписываем ось x
plt.xlabel('x') # подписываем ось y
plt.xlim([Params[0], Params[1]]) # рисуем график на отрезке [a,b]
plt.legend() # выводим легенду
plt.grid(True)
plt.show() # рисуем график на экране