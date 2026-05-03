
#[derive(Debug, Clone, Copy)]
struct BisectionStep {
    a: f64,
    b: f64,
    length: f64,
}

#[derive(Debug, Clone, Copy)]
struct NewtonStep {
    x_n: f64,
    x_next: f64,
    diff: f64,
}

#[derive(Debug, Clone, Copy)]
struct IterStep {
    x_n: f64,
    x_next: f64,
    diff: f64,
}

fn f(x: f64) -> f64 {
    x * (x + 1.0).ln() - 1.0
}

fn df(x: f64) -> f64 {
    (x + 1.0).ln() + x / (x + 1.0)
}

fn phi(x: f64) -> f64 {
    1.0 / (x + 1.0).ln()
}

fn bisection(a: f64, b: f64, eps: f64) -> Vec<BisectionStep> {
    let mut table = Vec::new();
    let mut a = a;
    let mut b = b;
    
    while (b - a) / 2.0 > eps {
        table.push(BisectionStep { a, b, length: b - a });
        
        let c = (a + b) / 2.0;
        if f(a) * f(c) < 0.0 {
            b = c;
        } else {
            a = c;
        }
    }
    table.push(BisectionStep { a, b, length: b - a });
    
    table
}

fn newton(mut x: f64, eps: f64) -> Vec<NewtonStep> {
    let mut table = Vec::new();
    
    loop {
        let x_next = x - f(x) / df(x);
        let diff = (x_next - x).abs();
        
        table.push(NewtonStep { x_n: x, x_next, diff });
        
        if diff < eps {
            break;
        }
        x = x_next;
    }
    
    table
}

fn simple_iteration(mut x: f64, eps: f64) -> Vec<IterStep> {
    let mut table = Vec::new();
    
    loop {
        let x_next = phi(x);
        let diff = (x_next - x).abs();
        
        table.push(IterStep { x_n: x, x_next, diff });
        
        if diff < eps {
            break;
        }
        x = x_next;
    }
    
    table
}

fn main() {
    println!("Уравнение: x * ln(x+1) = 1");
    println!("Точность: eps = 1e-4\n");
    
    // Отделение корней
    println!("Отделение корней:");
    println!("f(1.2) = {:.6} < 0", f(1.2));
    println!("f(1.3) = {:.6} > 0", f(1.3));
    println!("=> Корень на отрезке [1.2, 1.3]\n");
    
    // Метод половинного деления
    let table1 = bisection(1.2, 1.3, 1e-4);
    
    println!("Метод половинного деления");
    println!(" N |      a_n      |      b_n      |    b_n - a_n");
    println!("-----------------------------------------------");
    
    for (i, step) in table1.iter().enumerate() {
        println!(" {:2} | {:12.8} | {:12.8} | {:12.8}",
                 i, step.a, step.b, step.length);
    }
    
    let root1 = (table1.last().unwrap().a + table1.last().unwrap().b) / 2.0;
    println!("\nКорень: {:.8}", root1);
    println!("Итераций: {}\n", table1.len());
    
    // Метод Ньютона
    let table2 = newton(1.5, 1e-4);
    
    println!("Метод Ньютона");
    println!(" N |      x_n      |     x_{{n+1}}    |   |x_{{n+1}}-x_n|");
    println!("---------------------------------------------------");
    
    for (i, step) in table2.iter().enumerate() {
        println!(" {:2} | {:12.8} | {:12.8} | {:12.8}",
                 i, step.x_n, step.x_next, step.diff);
    }
    
    println!("\nКорень: {:.8}", table2.last().unwrap().x_next);
    println!("Итераций: {}\n", table2.len());
    
    // Метод простых итераций
    let table3 = simple_iteration(1.5, 1e-4);
    
    println!("Метод простых итераций");
    println!("φ(x) = 1 / ln(x+1)");
    println!(" N |      x_n      |     x_{{n+1}}    |   |x_{{n+1}}-x_n|");
    println!("---------------------------------------------------");
    
    for (i, step) in table3.iter().enumerate() {
        println!(" {:2} | {:12.8} | {:12.8} | {:12.8}",
                 i, step.x_n, step.x_next, step.diff);
    }
    
    println!("\nКорень: {:.8}", table3.last().unwrap().x_next);
    println!("Итераций: {}", table3.len());
}