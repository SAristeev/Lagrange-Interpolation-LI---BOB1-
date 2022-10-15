#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

double Func(double x) { // функция, которую будем интерполировать - (x-4)^4 + (x-3)^3 + (x-2)^2 + (x-1) + 1
    return pow(x-1,4) + pow(x - 3, 3) + pow(x - 2, 2) + 100 * sin(x);
}

int main(){ 
    double a = -2, b = 2; // выбираем начальные данные 
    const int N = 20; // выбираем N самостоятельно
    const int M = 1000; // допустим, что точек для проверки будет на порядок больше
    double X[N], FX[N]; // массив разбиения X[N] и значений функции в узлах сетки FX[N]
    double X1[M], FX1[M]; // массив проверочного разбиения X[N] и значений в этих узлах FX1[N]
    double L[M]; // массив значений интерполяционного многочлена
    double D[N]; // массив знаменателей D - Denominator

    srand(time(0)); // автоматическая рандомизиция

    for (int i = 0; i < N; i++) {
        X[i] = a + (b - a) * double(rand()) / (RAND_MAX); // задаем сетку
        // rand() возвращает любое число от 0 до RAND_MAX = 32767, поэтому делим на максимальное значение
        // умножаем на длину отрезка и отступаем от начальной точки
        FX[i] = Func(X[i]); // задаем массив значений
    }

    double h = (b - a) / M; // для проверки используем равномерную сетку, поэтому находим X1 пошагово
    for (int i = 0; i < M; i++) { // делаем равномерную сетку от a до b
        X1[i] = a + h * i;
        FX1[i] = Func(X1[i]);
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
            double multiplication = FX[j];
            for (int k = 0; k < N; k++) {
                if (k != j) {
                    multiplication *= (X1[i] - X[k]); // считаем произведение
                }
            }
            tmp += multiplication / D[j]; // считаем сумму
        }
        L[i] = tmp;
    }
    

    std::ofstream X1File, XFile, FXFile, FX1File, LFile, Params; // создаем файловые потоки для печати в память

    Params.open("P.txt"); // там будем хранить a и b
    XFile.open("X.txt"); // открываем каждый из файлов
    FXFile.open("FX.txt");
    X1File.open("X1.txt"); // открываем каждый из файлов
    FX1File.open("FX1.txt"); // всего у нас их будет много
    
    LFile.open("L.txt");
    
    for (int i = 0; i < N - 1; i++) { // печатаем каждый элемент до предпоследнего. После него запятую ставить не нужно
        XFile << X[i] << ", ";
    }
    XFile << X[N - 1] << std::endl; // печатаем последний элемент
    
    for (int i = 0; i < N - 1; i++) { // аналогично для массива значений
        FXFile << FX[i] << ", ";
    }
    FXFile << FX[N - 1] << std::endl;

    for (int i = 0; i < M - 1; i++) { // аналогично для массива значений
        FX1File << FX1[i] << ", ";
    }
    FX1File << FX1[M - 1] << std::endl;

    for (int i = 0; i < M - 1; i++) { // печатаем каждый элемент до предпоследнего. После него запятую ставить не нужно
        X1File << X1[i] << ", "; 
    }
    X1File << X1[M - 1] << std::endl; // печатаем последний элемент


    for (int i = 0; i < M - 1; i++) { // и для значений полинома Лагранжа
        LFile << L[i] << ", ";
    }
    LFile << L[M - 1] << std::endl;

    Params << a << ", " << b << std::endl;

    XFile.close(); // закрываем каждый файл
    X1File.close();
    FX1File.close();
    FXFile.close();
    LFile.close();
    Params.close();

    std::system("python Bob.py"); // эта команда вызывает командную строку и включает питоновскую часть задачи

    return 0;
}