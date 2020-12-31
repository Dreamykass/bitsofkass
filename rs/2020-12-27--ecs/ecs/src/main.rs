use legion::*;

#[derive(Clone, Copy, Debug, PartialEq)]
struct Position {
    x: f32,
    y: f32,
}
#[derive(Clone, Copy, Debug, PartialEq)]
struct Velocity {
    dx: f32,
    dy: f32,
}

#[derive(Clone, Debug, PartialEq)]
struct Graphic {
    b: Box<i32>,
}

fn main() {
    let mut world = World::default();

    let e1: Entity = world.push((Position { x: 0.0, y: 0.0 }, Velocity { dx: 3.0, dy: 7.0 }));
    let e2: Entity = world.push((
        Position { x: 76.0, y: 34.0 },
        Velocity { dx: 76.0, dy: 33.0 },
    ));
    let e3: Entity = world.push((Position { x: 0.0, y: 0.0 }, Graphic { b: Box::new(42) }));

    println!("\n--------------------------------- entry");
    if let Some(entry) = world.entry(e3) {
        println!(
            "{:?} has {:?}",
            e3,
            entry.archetype().layout().component_types()
        );
    }

    println!("\n--------------------------------- position query");
    let mut query = <&Position>::query();
    for position in query.iter(&world) {
        println!("{:?}", position);
    }

    println!("\n--------------------------------- position+velocity mut query");
    let mut query = <(&Velocity, &mut Position)>::query();
    for (velocity, position) in query.iter_mut(&mut world) {
        position.x += velocity.dx;
        position.y += velocity.dy;
    }

    println!("\n--------------------------------- position query");
    let mut query = <&Position>::query();
    for position in query.iter(&world) {
        println!("{:?}", position);
    }

    println!("\n--------------------------------- graphics query");
    let mut query = <&Graphic>::query();
    for graphic in query.iter(&world) {
        println!("{:?}", graphic);
    }
}
