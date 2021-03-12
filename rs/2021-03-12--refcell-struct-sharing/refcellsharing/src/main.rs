use std::cell::{Cell, RefCell};

struct Shared {
    message: String,
}

struct One<'a> {
    shared: &'a RefCell<Shared>,
}
impl<'a> One<'a> {
    fn modify_shared_thing(&mut self) {
        self.shared.borrow_mut().message += " one";
    }
}

struct Two<'a> {
    shared: &'a RefCell<Shared>,
}
impl<'a> Two<'a> {
    fn modify_shared_thing(&mut self) {
        self.shared.borrow_mut().message += " two";
    }
}

fn main() {
    let shared = RefCell::new(Shared {
        message: "main".to_string(),
    });

    let mut one = One { shared: &shared };
    let mut two = Two { shared: &shared };

    one.modify_shared_thing();
    two.modify_shared_thing();
    shared.borrow_mut().message += " main";
    one.modify_shared_thing();

    println!("{}", shared.borrow().message);
}
