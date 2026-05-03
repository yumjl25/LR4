use std::collections::HashMap;

// Структура для хранения результата Кондорсе
#[derive(Debug, Clone)]
struct CondorcetResult {
    winner: String,
    found: bool,
}

// Подсчет очков для метода Борда
fn get_borda_score(votes: &Vec<Vec<String>>, candidate: &str) -> i32 {
    let n = votes[0].len();
    let mut total = 0;
    
    for vote in votes {
        for (pos, c) in vote.iter().enumerate() {
            if c == candidate {
                total += (n - 1 - pos) as i32;
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
    let mut max_score = scores[candidates[0].as_str()];
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

fn main() {
    let candidates = vec![
        "A".to_string(),
        "B".to_string(),
        "C".to_string(),
    ];
    
    let votes = vec![
        vec!["A".to_string(), "B".to_string(), "C".to_string()],
        vec!["A".to_string(), "B".to_string(), "C".to_string()],
        vec!["B".to_string(), "C".to_string(), "A".to_string()],
        vec!["B".to_string(), "C".to_string(), "A".to_string()],
        vec!["C".to_string(), "A".to_string(), "B".to_string()],
    ];
    
    println!("Кандидаты: ");
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