use anymap::AnyMap;

struct World {
    stuff: AnyMap,
}

struct CommandBuffer {
    commands: Vec<Box<dyn Fn(&mut World)>>,
}

impl CommandBuffer {
    fn create<T>(&mut self, t: T)
    where
        T: 'static,
        T: Clone,
    {
        self.commands.push(Box::new(move |w: &mut World| {
            w.stuff.insert(t.clone());
            ()
        }));
    }

    fn run_on(&self, world: &mut World) {
        for c in &self.commands {
            c(world);
        }
    }
}

fn main() {
    let mut world = World {
        stuff: AnyMap::new(),
    };

    let mut cmd = CommandBuffer {
        commands: Vec::default(),
    };

    cmd.create(5);
    cmd.create(true);
    cmd.create(167.324);

    cmd.run_on(&mut world);

    //println!("{:?}", world.stuff);
    assert_eq!(world.stuff.get(), Some(&5));
    assert_eq!(world.stuff.get(), Some(&true));
    assert_eq!(world.stuff.get(), Some(&167.324));
}
