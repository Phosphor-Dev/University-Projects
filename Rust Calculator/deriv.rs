fn main(){
    eval("5-6*18/3+2");
    //eval("10*20-9/3+20");
}


fn eval(expr: &str){
    println!("Evaluating: {}", expr);

    let mut plustok: Vec<String> = expr.split("+").map(|s| s.to_string()).collect();
    let mut minustok: Vec<String> = expr.split("-").map(|s| s.to_string()).collect();
    let mut multtok: Vec<String> = expr.split("*").map(|s| s.to_string()).collect();
    let mut divtok: Vec<String> = expr.split("/").map(|s| s.to_string()).collect();

    
    //plustok.remove(len);
    //let left = &plustok.join("+");

    let operator = if plustok.len() > 1 {
        "+"
    } else if minustok.len() > 1 {
        "-"
    } else if multtok.len() > 1 {
        "*"
    } else if divtok.len() > 1 {
        "/"
    } else {
        ""
    };

    let len = plustok.len()-1;
    let right = if plustok.len() > 1 {
        plustok[len];
    } else if minustok.len() > 1 {
        minustok[len];
    } else if multtok.len() > 1 {
        multtok[len];
    } else if divtok.len() > 1 {
        divtok[len];
    } else {
        divtok[len];
    };

    let left = if plustok.len() > 1 {
        plustok.remove(plustok.len()-1);
        &plustok.join("+")
    } else if minustok.len() > 1 {
        minustok.remove(plustok.len()-1);
        &minustok.join("+")
    } else if multtok.len() > 1 {
        multtok.remove(plustok.len()-1);
        &multtok.join("+")
    } else if divtok.len() > 1 {
        divtok.remove(plustok.len()-1);
        &divtok.join("+")
    } else {
        ""
    };

    println!("Operator: {}", operator);
    println!("Right: {}", right);
    println!("Left: {}", left);
}


    /*let v = match n % 2{ 
        0 => {
            println!("Even: {}", n);
            n - 1
        }, 
        
        _ => {
            println!("Odd: {}", n);
            n - 1
        }
    };

    if v != 0 {
        eval(v)
    }*/
