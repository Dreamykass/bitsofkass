pub mod machine;

#[cfg(test)]
mod tests {
    use crate::machine::{Machine, State, StateQueue};
    use std::cell::RefCell;
    use std::ops::{AddAssign, Deref};
    use std::rc::Rc;

    #[test]
    fn test_push_run() {
        let mut machine = Machine::new(());
        assert!(machine.is_empty());

        let val = Rc::new(RefCell::new(1));
        assert_eq!(*val.deref().borrow().deref(), 1);

        struct TestState {
            rc: Rc<RefCell<i32>>,
        }

        impl State<()> for TestState {
            fn run(&mut self, qq: &mut StateQueue<()>, _: &mut ()) {
                self.rc.deref().borrow_mut().add_assign(1);
                qq.pop_back();
            }
        }

        machine.push(Rc::new(RefCell::new(TestState { rc: val.clone() })));
        assert!(!machine.is_empty());
        machine.run_all();
        assert!(machine.is_empty());
        assert_eq!(*val.deref().borrow_mut(), 2);

        machine.push(Rc::new(RefCell::new(TestState { rc: val.clone() })));
        machine.push(Rc::new(RefCell::new(TestState { rc: val.clone() })));
        machine.run_all();
        assert_eq!(*val.deref().borrow_mut(), 4);
        assert!(machine.is_empty());
    }

    #[test]
    fn test_with_shared_data() {
        let mut machine = Machine::new(1);
        assert!(machine.is_empty());
        assert_eq!(*machine.borrow_shared(), 1);

        struct TestState {}

        impl State<i32> for TestState {
            fn run(&mut self, qq: &mut StateQueue<i32>, sh: &mut i32) {
                sh.add_assign(1);
                qq.pop_back();
            }
        }

        machine.push(Rc::new(RefCell::new(TestState {})));
        assert!(!machine.is_empty());
        machine.run_all();
        assert!(machine.is_empty());
        assert_eq!(*machine.borrow_shared(), 2);

        machine.push(Rc::new(RefCell::new(TestState {})));
        machine.push(Rc::new(RefCell::new(TestState {})));
        machine.run_all();
        assert_eq!(*machine.borrow_shared(), 4);
        assert!(machine.is_empty());
    }
}
