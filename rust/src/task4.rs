use std::collections::HashMap;
use std::io;

// Структура для хранения результата Кондорсе
#[derive(Debug, Clone)]
struct CondorcetResult {
    winner: String,
    found: bool,
}

// Подсчёт очков для метода Борда
fn get_borda_score(votes: &Vec<Vec<String>>, candidate: &str) -> i32 {
    let n = votes[0].len() as i32;
    let mut total = 0;
    
    for vote in votes {
        for (pos, c) in vote.iter().enumerate() {
            if c == candidate {
                total += n - 1 - pos as i32;
            }
        }
    }
    total
}

// Нахождение победителя по Борда (с учётом ничьей)
fn find_borda_winner(votes: &Vec<Vec<String>>, candidates: &Vec<String>) -> String {
    let mut scores: HashMap<String, i32> = HashMap::new();
    
    for c in candidates {
        scores.insert(c.clone(), get_borda_score(votes, c));
    }
    
    // Находим максимальный счёт
    let mut max_score = *scores.get(candidates[0].as_str()).unwrap();
    for (_, &score) in &scores {
        if score > max_score {
            max_score = score;
        }
    }
    
    // Собираем всех с максимальным счётом
    let mut winners: Vec<String> = Vec::new();
    for (c, &score) in &scores {
        if score == max_score {
            winners.push(c.clone());
        }
    }
    
    // Формируем результат
    if winners.len() == 1 {
        winners[0].clone()
    } else {
        let mut result = String::new();
        for (i, w) in winners.iter().enumerate() {
            if i > 0 {
                result.push_str("/");
            }
            result.push_str(w);
        }
        result.push_str(" (ничья)");
        result
    }
}

// Побеждает ли A кандидата B
fn beats(votes: &Vec<Vec<String>>, a: &str, b: &str) -> bool {
    let mut wins_a = 0;
    let total = votes.len();
    
    for vote in votes {
        let mut pos_a = -1;
        let mut pos_b = -1;
        for (i, c) in vote.iter().enumerate() {
            if c == a {
                pos_a = i as i32;
            }
            if c == b {
                pos_b = i as i32;
            }
        }
        if pos_a < pos_b {
            wins_a += 1;
        }
    }
    wins_a > (total / 2) as i32
}

// Нахождение победителя по Кондорсе
fn find_condorcet_winner(votes: &Vec<Vec<String>>, candidates: &Vec<String>) -> CondorcetResult {
    for c in candidates {
        let mut wins_all = true;
        for other in candidates {
            if c == other {
                continue;
            }
            if !beats(votes, c, other) {
                wins_all = false;
                break;
            }
        }
        if wins_all {
            return CondorcetResult {
                winner: c.clone(),
                found: true,
            };
        }
    }
    CondorcetResult {
        winner: String::new(),
        found: false,
    }
}

// Функция для ввода строки с консоли
fn read_line() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn main() {

    // Ввод кандидатов
    println!("Введите имена кандидатов:");
    let candidates_line = read_line();
    let candidates: Vec<String> = candidates_line.split_whitespace().map(|s| s.to_string()).collect();
    let num_candidates = candidates.len();
    
    // Ввод количества избирателей
    println!("Введите количество избирателей:");
    let num_voters: usize = read_line().parse().unwrap();
    
    // Ввод голосов
    let mut votes: Vec<Vec<String>> = Vec::new();
    println!("Введите голоса:");
    println!("Для каждого избирателя введите {} имён", num_candidates);
    
    for i in 0..num_voters {
        println!("Избиратель {}: ", i + 1);
        let vote_line = read_line();
        let vote: Vec<String> = vote_line.split_whitespace().map(|s| s.to_string()).collect();
        
        // Проверка: правильное ли количество кандидатов
        if vote.len() != num_candidates {
            println!("Ошибка: нужно ввести {} кандидатов.", num_candidates);
            let vote_line = read_line();
            let vote: Vec<String> = vote_line.split_whitespace().map(|s| s.to_string()).collect();
            votes.push(vote);
        } else {
            votes.push(vote);
        }
    }
    
    // Вывод результатов
    
    print!("Кандидаты: ");
    for c in &candidates {
        print!("{} ", c);
    }
    println!("\n");
    
    println!("Голоса:");
    for (i, vote) in votes.iter().enumerate() {
        print!("{}-й: ", i + 1);
        for c in vote {
            print!("{} ", c);
        }
        println!();
    }
    println!();
    
    let borda_winner = find_borda_winner(&votes, &candidates);
    let condorcet_result = find_condorcet_winner(&votes, &candidates);
    
    println!("Победитель по Борда: {}", borda_winner);
    
    if condorcet_result.found {
        println!("Победитель по Кондорсе: {}", condorcet_result.winner);
    } else {
        println!("Победитель по Кондорсе: не найден (цикл)");
    }
}