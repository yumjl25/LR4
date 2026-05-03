#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Winner {
    string bordaWinner;
    string condorcetWinner;
    bool condorcetFound;
};

// Подсчет очков для метода Борда
int getBordaScore(const vector<vector<string>>& votes, string candidate) {
    int n = votes[0].size();
    int total = 0;
    
    for (const auto& vote : votes) {
        for (size_t pos = 0; pos < vote.size(); pos++) {
            if (vote[pos] == candidate) {
                total += (n - 1 - pos);
            }
        }
    }
    return total;
}

// Нахождение победителя по Борда
string findBordaWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    map<string, int> scores;
    
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
    int total = votes.size();
    
    for (const auto& vote : votes) {
        int posA = -1, posB = -1;
        for (size_t i = 0; i < vote.size(); i++) {
            if (vote[i] == A) posA = i;
            if (vote[i] == B) posB = i;
        }
        if (posA < posB) winA++;
    }
    return winA > total / 2;
}

// Нахождение победителя по Кондорсе
Winner findCondorcetWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    for (const string& c : candidates) {
        bool winsAll = true;
        for (const string& other : candidates) {
            if (c == other) continue;
            if (!beats(votes, c, other)) {
                winsAll = false;
                break;
            }
        }
        if (winsAll) {
            return {c, c, true};
        }
    }
    return {"", "", false};
}

int main() {
    vector<string> candidates = {"A", "B", "C"};
    
    vector<vector<string>> votes = {
        {"A", "B", "C"},
        {"A", "B", "C"},
        {"B", "C", "A"},
        {"B", "C", "A"},
        {"C", "A", "B"}
    };
    
    cout << "Кандидаты: ";
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
    
    if (condorcetWinner.condorcetFound) {
        cout << "Победитель по Кондорсе: " << condorcetWinner.condorcetWinner << endl;
    } else {
        cout << "Победитель по Кондорсе: не найден (цикл)" << endl;
    }
    
    return 0;
}