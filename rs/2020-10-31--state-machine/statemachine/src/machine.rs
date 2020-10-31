use std::cell::RefCell;
use std::collections::VecDeque;
use std::ops::Deref;
use std::rc::Rc;

// -----------------------------------------------------------------------------------------------

pub type StateQueue = VecDeque<Rc<RefCell<dyn State>>>;

pub trait State {
    fn run(&mut self, _: &mut StateQueue);
}

// -----------------------------------------------------------------------------------------------

#[derive(Default)]
pub struct Machine {
    queue: StateQueue,
}

impl Machine {
    pub fn new() -> Machine {
        Machine {
            queue: VecDeque::new(),
        }
    }

    pub fn is_empty(&self) -> bool {
        self.queue.is_empty()
    }

    pub fn clear(&mut self) {
        self.queue.clear()
    }

    pub fn run_once(&mut self) {
        if let Some(state) = self.queue.back() {
            state.clone().deref().borrow_mut().run(&mut self.queue);
        }
    }

    pub fn run_all(&mut self) {
        while !self.is_empty() {
            self.run_once();
        }
    }

    pub fn push(&mut self, state: Rc<RefCell<dyn State>>) {
        self.queue.push_front(state);
    }
}

// -----------------------------------------------------------------------------------------------

// struct StateFromFnMut {
//     closure: Box<dyn FnMut(&mut StateQueue)>,
// }
//
// impl State for StateFromFnMut {
//     fn run(&mut self, state_queue: &mut StateQueue) {
//         // self.closure(&mut state_queue);
//         (*self.closure)(&mut state_queue);
//     }
// }
//
// impl Machine {
//     pub fn push_from_fnmut(&mut self, closure: Box<dyn FnMut(&mut StateQueue)>) {}
//
//     // pub fn push_from_fnonce(&mut self, closure: Fn(&mut StateQueue)) {}
// }

// -----------------------------------------------------------------------------------------------
