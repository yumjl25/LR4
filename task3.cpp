#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Генератор Фибоначчи с запаздыванием (сложение)
vector<int> fibonacciAdd(int a, int b, int m, vector<int> seed, int N) {
    int maxLag = max(a, b);
    vector<int> result = seed;
    
    for (int i = maxLag; i < N; i++) {
        int next = (result[i - a] + result[i - b]) % m;
        result.push_back(next);
    }
    return result;
}

// Генератор Фибоначчи с запаздыванием (вычитание)
vector<double> fibonacciSub(int a, int b, vector<double> seed, int N) {
    int maxLag = max(a, b);
    vector<double> result = seed;
    
    for (int i = maxLag; i < N; i++) {
        double x_prev_a = result[i - a];
        double x_prev_b = result[i - b];
        double next;
        
        if (x_prev_a >= x_prev_b) {
            next = x_prev_a - x_prev_b;
        } else {
            next = x_prev_a - x_prev_b + 1.0;
        }
        result.push_back(next);
    }
    return result;
}

// Генератор Фибоначчи с запаздыванием (умножение)
vector<int> fibonacciMul(int a, int b, int m, vector<int> seed, int N) {
    int maxLag = max(a, b);
    vector<int> result = seed;
    
    for (int i = maxLag; i < N; i++) {
        int next = (result[i - a] * result[i - b]) % m;
        result.push_back(next);
    }
    return result;
}

// Генератор Фибоначчи с запаздыванием (XOR)
vector<int> fibonacciXor(int a, int b, int m, vector<int> seed, int N) {
    int maxLag = max(a, b);
    vector<int> result = seed;
    
    for (int i = maxLag; i < N; i++) {
        int next = (result[i - a] ^ result[i - b]) % m;
        result.push_back(next);
    }
    return result;
}

int main() {
    // Пример 1: сложение
    vector<int> seed1 = {1, 4};
    vector<int> r1 = fibonacciAdd(2, 1, 16, seed1, 8);
    cout << "Сложение (a=2,b=1,m=16): ";
    for (int v : r1) cout << v << " ";
    cout << endl;
    
    // Пример 2: вычитание
    vector<double> seed2 = {5, 8, 3};
    vector<double> r2 = fibonacciSub(1, 3, seed2, 9);
    cout << "Вычитание (a=1,b=3): ";
    for (double v : r2) cout << v << " ";
    cout << endl;
    
    // Пример 3: умножение
    vector<int> seed3 = {3, 5};
    vector<int> r3 = fibonacciMul(2, 1, 100, seed3, 10);
    cout << "Умножение (a=2,b=1,m=100): ";
    for (int v : r3) cout << v << " ";
    cout << endl;
    
    // Пример 4: XOR
    vector<int> seed4 = {7, 12};
    vector<int> r4 = fibonacciXor(2, 1, 32, seed4, 10);
    cout << "XOR (a=2,b=1,m=32): ";
    for (int v : r4) cout << v << " ";
    cout << endl;
    
    return 0;
}