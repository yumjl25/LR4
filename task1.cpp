#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

struct bisectionStep { double a, b, length; }; // левая граница, правая, длина отрезка
struct newtonStep { double x_n, x_next, diff; }; // текущее, следующее, разница
struct iterStep { double x_n, x_next, diff; }; // текущее, следующее, разница

double f(double x) { return x * log(x + 1) - 1; }
double df(double x) { return log(x + 1) + x / (x + 1); }
double phi(double x) { return 1.0 / log(x + 1); }

// Метод половинного деления
vector<bisectionStep> bisection(double a, double b, double eps) {
    vector<bisectionStep> table;
    
    while ((b - a) / 2 > eps) {
        table.push_back({a, b, b - a}); //Сохраняем текущий отрезок в таблицу. {a, b, b-a} создаёт структуру bisectionStep
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0) b = c; //Если f(a) и f(c) разных знаков, значит корень в левой половине [a, c]
        else a = c;
    }
    table.push_back({a, b, b - a}); //После цикла сохраняем последний отрезок
    return table;
}

// Метод Ньютона
vector<newtonStep> newton(double x, double eps) {
    vector<newtonStep> table;
    
    while (true) {
        double x_next = x - f(x) / df(x); //формула Ньютона
        double diff = fabs(x_next - x);
        table.push_back({x, x_next, diff});
        
        if (diff < eps) break;
        x = x_next;
    }
    return table;
}

// Метод простых итераций
vector<iterStep> simpleIteration(double x, double eps) {
    vector<iterStep> table;
    
    while (true) {
        double x_next = phi(x);
        double diff = fabs(x_next - x);
        table.push_back({x, x_next, diff});
        
        if (diff < eps) break;
        x = x_next;
    }
    return table;
}

int main() {
    cout << "Уравнение: x * ln(x+1) = 1\n";
    cout << "Точность: eps = 1e-4\n\n";
    
    cout << "Отделение корней:\n";
    cout << "f(1.2) = " << f(1.2) << " < 0\n";
    cout << "f(1.3) = " << f(1.3) << " > 0\n";
    cout << "Корень на отрезке [1.2, 1.3]\n";
    
    // Половинное деление
    vector<bisectionStep> t1 = bisection(1.2, 1.3, 1e-4);
    cout << "\nМетод половинного деления\n";
    cout << " N |      a_n      |      b_n      |    b_n - a_n\n";
    cout << "-----------------------------------------------\n";
    int n = 0;
    for (const auto& s : t1) {
        cout << " " << setw(2) << n++ << " | "
             << fixed << setprecision(8) << setw(12) << s.a << " | "
             << setw(12) << s.b << " | "
             << setw(12) << s.length << endl;
    }
    cout << "\nКорень: " << (t1.back().a + t1.back().b) / 2 << endl;
    cout << "Итераций: " << t1.size() << endl;
    
    // Ньютон
    vector<newtonStep> t2 = newton(1.5, 1e-4);
    cout << "\nМетод Ньютона\n";
    cout << " N |      x_n      |     x_{n+1}    |   |x_{n+1}-x_n|\n";
    cout << "---------------------------------------------------\n";
    n = 0;
    for (const auto& s : t2) {
        cout << " " << setw(2) << n++ << " | "
             << fixed << setprecision(8) << setw(12) << s.x_n << " | "
             << setw(12) << s.x_next << " | "
             << setw(12) << s.diff << endl;
    }
    cout << "\nКорень: " << t2.back().x_next << endl;
    cout << "Итераций: " << t2.size() << endl;
    
    // Простые итерации
    vector<iterStep> t3 = simpleIteration(1.5, 1e-4);
    cout << "\nМетод простых итераций\n";
    cout << "φ(x) = 1 / ln(x+1)\n";
    cout << " N |      x_n      |     x_{n+1}    |   |x_{n+1}-x_n|\n";
    cout << "---------------------------------------------------\n";
    n = 0;
    for (const auto& s : t3) {
        cout << " " << setw(2) << n++ << " | "
             << fixed << setprecision(8) << setw(12) << s.x_n << " | "
             << setw(12) << s.x_next << " | "
             << setw(12) << s.diff << endl;
    }
    cout << "\nКорень: " << t3.back().x_next << endl;
    cout << "Итераций: " << t3.size() << endl;
    
    return 0;
}