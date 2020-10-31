use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

// -----------------------------------------------------------------------------------------------

pub type StateQueue<SharedType> = VecDeque<Rc<RefCell<dyn State<SharedType>>>>;

pub trait State<SharedType> {
    fn run(&mut self, _: &mut StateQueue<SharedType>, _: &mut SharedType);
}

// -----------------------------------------------------------------------------------------------

pub struct Machine<SharedType> {
    queue: StateQueue<SharedType>,
    shared: SharedType,
}

impl<SharedType> Machine<SharedType> {
    pub fn new(shared: SharedType) -> Machine<SharedType> {
        Machine {
            queue: VecDeque::new(),
            shared,
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
            state
                .clone()
                .borrow_mut()
                .run(&mut self.queue, &mut self.shared);
        }
    }

    pub fn run_all(&mut self) {
        while !self.is_empty() {
            self.run_once();
        }
    }

    pub fn push(&mut self, state: Rc<RefCell<dyn State<SharedType>>>) {
        self.queue.push_front(state);
    }

    pub fn shared(&self) -> &SharedType {
        &self.shared
    }

    pub fn shared_mut(&mut self) -> &mut SharedType {
        &mut self.shared
    }
}

// -----------------------------------------------------------------------------------------------
// // // doesn't work, maybe come back to it later, maybe not

// struct StateFromFnMut {
//     closure: Box<dyn FnMut(&mut StateQueue)>,
// }
//
// impl State for StateFromFnMut {
//     fn run(&mut self, state_queue: &mut StateQueue) {
//         // self.closure(&mut state_queue);
//         (*self.closure)(&mut state_queue);
//         // ????????
//     }
// }
//
// impl Machine {
//     pub fn push_from_fnmut(&mut self, closure: Box<dyn FnMut(&mut StateQueue)>) {}
//
//     // pub fn push_from_fnonce(&mut self, closure: Fn(&mut StateQueue)) {}
// }

// -----------------------------------------------------------------------------------------------
