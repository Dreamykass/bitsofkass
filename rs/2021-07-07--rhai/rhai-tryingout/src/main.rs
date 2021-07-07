use std::cell::RefCell;
use std::ops::Deref;
use std::rc::Rc;

struct NonClone {
    value: i64,
}

fn main() {
    println!("rust says hello");
    let nc_main = Rc::new(RefCell::new(NonClone { value: 7 }));

    let mut engine = rhai::Engine::new();

    {
        engine.register_fn("say", |d: rhai::Dynamic| {
            println!("rhai says {}", d.to_string())
        });

        let nc = nc_main.clone();
        engine.register_fn("nc_get", move || -> i64 { nc.deref().borrow().value });

        let nc = nc_main.clone();
        engine.register_fn("nc_put", move |i: i64| nc.deref().borrow_mut().value = i);
    }

    let ast = engine.compile(include_str!("main.rhai")).unwrap();
    engine.eval_ast::<()>(&ast).unwrap();

    println!("rust says value is {}", nc_main.deref().borrow().value);
    println!("rust says bye");
}
