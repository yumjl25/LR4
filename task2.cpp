#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

using namespace std;

random_device rd;
ranlux24_base gen(rd());

// Задание 1
vector<int> createArray(int size, int minVal, int maxVal) { //возвращает vector<int>, принимает размер массива и диапазон случайных чисел
    vector<int> arr(size);
    uniform_int_distribution<> dist(minVal, maxVal); //Создаёт равномерное распределение целых чисел от minVal до maxVal
    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen); //генерирует случайное число в заданном диапазоне с помощью генератора
    }
    return arr;
}

// Задание 2
vector<int> getEvenAfterOdd(const vector<int>& arr) {
    vector<int> result;
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] % 2 == 0 && arr[i-1] % 2 != 0) {
            result.push_back(arr[i]);
        }
    }
    return result;
}

int getSum(const vector<int>& arr) { //функция возвращает сумму элементов массива
    int sum = 0;
    for (int val : arr) {
        sum += val;
    }
    return sum;
}

// Задание 3
vector<int> getLocalMins(const vector<int>& arr) {
    vector<int> result;
    for (size_t i = 1; i < arr.size() - 1; i++) {
        if (arr[i] < arr[i-1] && arr[i] < arr[i+1]) { //ищем локальные минимумы
            result.push_back(arr[i]);
        }
    }
    return result;
}

// Задание 4
vector<int> sortEvensAscOddsDesc(const vector<int>& arr) {
    vector<int> chet, nechet;
    
    for (int val : arr) { //добавляем в векторы четные и нечетные элементы соответственно
        if (val % 2 == 0) {
            chet.push_back(val);
        } else {
            nechet.push_back(val);
        }
    }
    
    sort(chet.begin(), chet.end()); //сортировка
    sort(nechet.begin(), nechet.end(), greater<int>()); //от большего к меньшему
    
    vector<int> result;
    for (int val : chet) result.push_back(val);
    for (int val : nechet) result.push_back(val);
    
    return result;
}

// Задание 5
int getMostFrequent(const vector<int>& arr) {
    map<int, int> freq;
    for (int val : arr) { //Ключ: само число (int), значение: сколько раз встречается (int)
        freq[val]++;
    }
    
    int most = arr[0];
    int maxFreq = 0;
    for (auto p : freq) { //ищем самое частовстречающееся
        if (p.second > maxFreq) {
            maxFreq = p.second;
            most = p.first;
        }
    }
    return most; //возвращаем самое частое число
}

vector<int> getGreaterThan(const vector<int>& arr, int threshold) {
    vector<int> result;
    for (int val : arr) {
        if (val > threshold) {
            result.push_back(val); //если элемент больше порога добавляем в результат
        }
    }
    return result;
}

// функция для вывода
string toString(const vector<int>& arr) { //превращает вектор в строку
    string s = "";
    for (int val : arr) {
        s += to_string(val) + " ";
    }
    return s;
}

int main() {
    // Задание 1
    vector<int> arr1 = createArray(15, 0, 100);
    
    // Задание 2
    vector<int> evenAfterOdd = getEvenAfterOdd(arr1);
    int sumEvenAfterOdd = getSum(evenAfterOdd);
    
    // Задание 3
    vector<int> localMins = getLocalMins(arr1);
    
    // Задание 4
    vector<int> sortedArr = sortEvensAscOddsDesc(arr1);
    
    // Задание 5
    vector<int> arr2 = createArray(15, 100, 120);
    int mostFrequent = getMostFrequent(arr2);
    vector<int> greaterThan = getGreaterThan(arr2, mostFrequent);
    
    // ВЫВОД
    cout << "Массив 1: " << toString(arr1) << endl;
    cout << "Четные после нечетных: " << toString(evenAfterOdd) << endl;
    cout << "Сумма: " << sumEvenAfterOdd << endl;
    cout << "Локальные минимумы: " << toString(localMins) << endl;
    cout << "Отсортированный (чет нечет): " << toString(sortedArr) << endl;
    cout << "Массив 2: " << toString(arr2) << endl;
    cout << "Самый частый элемент: " << mostFrequent << endl;
    cout << "Элементы больше " << mostFrequent << ": " << toString(greaterThan) << endl;
    
    return 0;
}