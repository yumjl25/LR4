#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Winner {
    string condorcetWinner; //функция findCondorcetWinner должна вернуть два значения: имя победителя и флаг.
    bool condorcetFound;
};

// Подсчет очков для метода Борда
int getBordaScore(const vector<vector<string>>& votes, string candidate) {
    int n = votes[0].size(); // количество кандидатов
    int total = 0;
    
    for (const auto& vote : votes) {
        for (size_t pos = 0; pos < vote.size(); pos++) { // каждая позиция
            if (vote[pos] == candidate) {
                total += (n - 1 - pos); // за 1 место n-1 очков, за последнее 0
            }
        }
    }
    return total;
}

// Нахождение победителя по Борда
string findBordaWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    map<string, int> scores; // словарь: кандидат - сумма очков
    
    for (const string& c : candidates) {
        scores[c] = getBordaScore(votes, c);
    }
    
    // Находим максимальный счёт
    int maxScore = scores[candidates[0]];
    for (const auto& p : scores) {
        if (p.second > maxScore) {
            maxScore = p.second;
        }
    }
    
    // Собираем всех с максимальным счётом
    vector<string> winners;
    for (const auto& p : scores) {
        if (p.second == maxScore) {
            winners.push_back(p.first);
        }
    }
    
    // Формируем результат
    if (winners.size() == 1) {
        return winners[0];
    } else {
        string result = "";
        for (size_t i = 0; i < winners.size(); i++) {
            if (i > 0) result += "/";
            result += winners[i];
        }
        return result + " (ничья)";
    }
}

// Побеждает ли A кандидата B
bool beats(const vector<vector<string>>& votes, string A, string B) {
    int winA = 0;
    int total = votes.size(); //колво избирателей
    
    for (const auto& vote : votes) { //проходим по каждому голосу
        int posA = -1, posB = -1; //позиция в голосе
        for (size_t i = 0; i < vote.size(); i++) {
            if (vote[i] == A) posA = i; //запоминаем позицию
            if (vote[i] == B) posB = i;
        }
        if (posA < posB) winA++;
    }
    return winA > total / 2; //больше чем у половины избирателей
}

// Нахождение победителя по Кондорсе
Winner findCondorcetWinner(const vector<vector<string>>& votes, const vector<string>& candidates) { //кандидат, который побеждает всех в парном сравнении
    for (const string& c : candidates) { //перебираем всех кандидатов
        bool winsAll = true; //Предполагаем, что кандидат c побеждает все
        for (const string& other : candidates) { //Перебираем всех других кандидатов (кроме самого c)
            if (c == other) continue;
            if (!beats(votes, c, other)) { //Вызываем beats, чтобы проверить, побеждает ли c кандидата other
                winsAll = false;
                break;
            }
        }
        if (winsAll) {
            return {c, true};
        }
    }
    return {"", false}; //если ни один не победил пустая структура
}

int main() {
    int numCandidates, numVoters;
    
    // Ввод кандидатов
    cout << "Введите количество кандидатов: ";
    cin >> numCandidates;
    
    vector<string> candidates(numCandidates);
    cout << "Введите имена кандидатов: ";
    for (int i = 0; i < numCandidates; i++) {
        cin >> candidates[i];
    }
    
    // Ввод голосов
    cout << "Введите количество избирателей: ";
    cin >> numVoters;
    
    vector<vector<string>> votes(numVoters, vector<string>(numCandidates));
    
    cout << "Введите голоса:" << endl;
    for (int i = 0; i < numVoters; i++) {
        cout << "Избиратель " << i+1 << ": ";
        for (int j = 0; j < numCandidates; j++) {
            cin >> votes[i][j];
        }
    }
    
    // Вывод результатов
    cout << "\nКандидаты: ";
    for (string c : candidates) cout << c << " ";
    cout << endl << endl;
    
    cout << "Голоса:" << endl;
    for (size_t i = 0; i < votes.size(); i++) {
        cout << i+1 << "-й: ";
        for (string c : votes[i]) cout << c << " ";
        cout << endl;
    }
    cout << endl;
    
    string bordaWinner = findBordaWinner(votes, candidates);
    Winner condorcetWinner = findCondorcetWinner(votes, candidates);
    
    cout << "Победитель по Борда: " << bordaWinner << endl;
    
    if (condorcetWinner.condorcetFound) { //проверяет: найден ли победитель, condorcetWinner переменная типа Winner
        cout << "Победитель по Кондорсе: " << condorcetWinner.condorcetWinner << endl; //Поле структуры Winner
    } else {
        cout << "Победитель по Кондорсе: не найден (цикл)" << endl;
    }
    
    return 0;
}