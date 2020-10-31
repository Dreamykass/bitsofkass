pub mod machine;

#[cfg(test)]
mod tests {
    use crate::machine::{Machine, State, StateQueue};
    use std::cell::RefCell;
    use std::ops::{AddAssign, Deref};
    use std::rc::Rc;

    #[test]
    fn test_empty() {
        let mut machine = Machine::new();
        assert!(machine.is_empty());

        machine.clear();
        assert!(machine.is_empty());

        machine.run_once();
        assert!(machine.is_empty());

        machine.run_all();
        assert!(machine.is_empty());
    }

    #[test]
    fn test_push_run() {
        let mut machine = Machine::new();
        let val = Rc::new(RefCell::new(1));
        assert_eq!(*val.deref().borrow().deref(), 1);

        struct TestState {
            rc: Rc<RefCell<i32>>,
        }

        impl State for TestState {
            fn run(&mut self, qq: &mut StateQueue) {
                self.rc.deref().borrow_mut().add_assign(1);
                // *self.rc.deref().borrow_mut() += 1;
                qq.pop_back();
            }
        }

        machine.push(Rc::new(RefCell::new(TestState { rc: val.clone() })));
        machine.run_all();
        assert_eq!(*val.deref().borrow_mut(), 2);

        machine.push(Rc::new(RefCell::new(TestState { rc: val.clone() })));
        machine.push(Rc::new(RefCell::new(TestState { rc: val.clone() })));
        machine.run_all();
        assert_eq!(*val.deref().borrow_mut(), 4);

        // machine.push(Box::new(
        //     |mut val| -> VecDeque<Box<dyn State>> { VecDeque::new() } as State,
        // ))
    }
}
