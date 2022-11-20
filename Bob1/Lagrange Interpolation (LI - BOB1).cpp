#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

double f(double x) { // функция, которую будем интерполировать - (x-4)^4 + (x-3)^3 + (x-2)^2 + (x-1) + 1
    return pow(x-1,4) + pow(x - 3, 3) + pow(x - 2, 2) + 100 * sin(x);
}

int main(){ 
    double a = -2, b = 2; // выбираем начальные данные 
    const int N = 20; // выбираем N самостоятельно
    const int M = 1000; // допустим, что точек для проверки будет на порядок больше
    double X[N], F[N]; // массив разбиения X[N] и значений функции в узлах сетки FX[N]
    double mesh[M]; // массив проверочного разбиения X[N] и значений в этих узлах FX1[N]
    double L[M]; // массив значений интерполяционного многочлена
    double D[N]; // массив знаменателей D - Denominator

    srand(time(0)); // автоматическая рандомизиция

    for (int i = 0; i < N; i++) {
        X[i] = a + (b - a) * double(rand()) / (RAND_MAX); // задаем сетку
        // rand() возвращает любое число от 0 до RAND_MAX = 32767, поэтому делим на максимальное значение
        // умножаем на длину отрезка и отступаем от начальной точки
        F[i] = f(X[i]); // задаем массив значений
    }

    double h = (b - a) / M; // для проверки используем равномерную сетку, поэтому находим X1 пошагово
    for (int i = 0; i < M; i++) { // делаем равномерную сетку от a до b
        mesh[i] = a + h * i;
    }
    // для каждого FX[i] в сумме по i знаменатель фиксирован
    // таких знаменателей как раз N
    for (int i = 0; i < N; i++) {
        D[i] = 1;
        for (int k = 0; k < N; k++) {
            if (k != i) {
                D[i] *= (X[i] - X[k]); // считаем произведение
            }
        }
    }


    for (int i = 0; i < M; i++) {
        double tmp = 0; // вычисляем элемент из суммы в многочлене Лагранжа
        for (int j = 0; j < N; j++) {
            double multiplication = F[j];
            for (int k = 0; k < N; k++) {
                if (k != j) {
                    multiplication *= (mesh[i] - X[k]); // считаем произведение
                }
            }
            tmp += multiplication / D[j]; // считаем сумму
        }
        L[i] = tmp;
    }
    
    std::ofstream Params;
    Params.open("Params.txt"); // там будем хранить a и b
    Params << a << ", " << b << std::endl;
    Params.close();


    
    std::ofstream XFile, FFile; // создаем файловые потоки для печати в память
    
    XFile.open("X.txt"); // открываем каждый из файлов
    FFile.open("F.txt");
    
    for (int i = 0; i < N - 1; i++)  // печатаем каждый элемент до предпоследнего. После него запятую ставить не нужно
    {
        XFile << X[i] << ", ";
        FFile << F[i] << ", ";
    }

    XFile << X[N - 1] << std::endl; // печатаем последний элемент
    FFile << F[N - 1] << std::endl;
    XFile.close(); // закрываем каждый файл
    FFile.close();

    

    std::ofstream meshFile, FmeshFile, LFile;
    meshFile.open("mesh.txt"); // открываем каждый из файлов
    FmeshFile.open("Fmesh.txt"); // всего у нас их будет много
    LFile.open("L.txt");

    for (int i = 0; i < M - 1; i++) // аналогично для массива значений
    { 
        meshFile << mesh[i] << ", ";
        FmeshFile << f(mesh[i]) << ", ";
        LFile << L[i] << ", ";
    }

    FmeshFile << f(mesh[M - 1]) << std::endl;
    meshFile << mesh[M - 1] << std::endl; // печатаем последний элемент
    LFile << L[M - 1] << std::endl;
 
    meshFile.close();
    FmeshFile.close();
    LFile.close();


    std::system("python plot.py"); // эта команда вызывает командную строку и включает питоновскую часть задачи
    std::system("del /s /q Params.txt X.txt F.txt L.txt mesh.txt Fmesh.txt"); // удаление лишних файлов
    return 0;
}