use serde::{Deserialize, Serialize};
use std::mem::size_of;

#[allow(clippy::large_enum_variant)]
#[derive(Deserialize, Serialize)]
enum Foo {
    SmallBool(bool),
    MediumVector(Vec<i64>),
    BigArray([i64; 32]),
}

fn main() {
    println!("size_of::<Foo>(): {}", size_of::<Foo>());

    println!(
        "SmallBool: {}",
        bincode::serialize(&Foo::SmallBool(true)).unwrap().len()
    );

    println!(
        "MediumVector, empty: {}",
        bincode::serialize(&Foo::MediumVector(Vec::new()))
            .unwrap()
            .len()
    );

    println!(
        "MediumVector, 4 ints: {}",
        bincode::serialize(&Foo::MediumVector(vec![1, 2, 3, 4]))
            .unwrap()
            .len()
    );

    println!(
        "MediumVector, 16 ints: {}",
        bincode::serialize(&Foo::MediumVector(vec![
            1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4
        ]))
        .unwrap()
        .len()
    );

    println!(
        "MediumVector, 32 ints: {}",
        bincode::serialize(&Foo::MediumVector(vec![
            1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1,
            2, 3, 4
        ]))
        .unwrap()
        .len()
    );

    println!(
        "BigArray: {}",
        bincode::serialize(&Foo::BigArray([4; 32])).unwrap().len()
    );
}
