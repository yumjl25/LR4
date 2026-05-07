#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Генератор Фибоначчи с запаздыванием
vector<int> fibonacciGen(int a, int b, int m, vector<int> seed, int N, char op) {
    int maxLag = max(a, b);
    vector<int> result = seed;
    vector<int> newNumbers;
    
    for (int i = maxLag; i < N; i++) {
        int x = result[i - a];
        int y = result[i - b];
        int next;
        
        switch (op) {
            case '+':
                next = (x + y) % m;
                break;
            case '-':
                next = (x - y) % m;
                if (next < 0) next += m;
                break;
            case '*':
                next = (x * y) % m;
                break;
            case '^':
                next = (x ^ y) % m;
                break;
            default:
                next = 0;
        }
        
        result.push_back(next);
        newNumbers.push_back(next);
    }
    return newNumbers;
}

int main() {
    int a, b, m, N;
    char op;
    int seedCount;
    
    // Ввод параметров
    cout << "Введите лаг a: ";
    cin >> a;
    
    cout << "Введите лаг b: ";
    cin >> b;
    
    cout << "Введите операцию (+, -, *, ^): ";
    cin >> op;
    
    cout << "Введите модуль m: ";
    cin >> m;
    
    cout << "Введите количество начальных значений (seed): ";
    cin >> seedCount;
    
    vector<int> seed(seedCount);
    cout << "Введите " << seedCount << " начальных значений: ";
    for (int i = 0; i < seedCount; i++) {
        cin >> seed[i];
    }
    
    cout << "Введите общее количество чисел N: ";
    cin >> N;
    
    // Генерация
    vector<int> result = fibonacciGen(a, b, m, seed, N, op);
    
    // Вывод только новых чисел
    cout << "\nРезультат: ";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}