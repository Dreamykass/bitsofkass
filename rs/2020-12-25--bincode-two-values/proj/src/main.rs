use serde::Deserialize;
use serde::Serialize;

#[derive(Serialize, Deserialize, Debug)]
enum PacketType {
    One = 0,
    Two = 1,
}

#[derive(Serialize, Deserialize, Debug)]
struct One(i32);
#[derive(Serialize, Deserialize, Debug)]
struct Two([i32; 4]);

fn main() {
    let mut v1 = Vec::<u8>::new();
    bincode::serialize_into(&mut v1, &PacketType::One).unwrap();
    bincode::serialize_into(&mut v1, &One(5)).unwrap();
    dbg!(&v1);

    let mut v2 = Vec::<u8>::new();
    bincode::serialize_into(&mut v2, &PacketType::Two).unwrap();
    bincode::serialize_into(&mut v2, &Two([32; 4])).unwrap();
    dbg!(&v2);

    let t1 = bincode::deserialize_from::<&[u8], PacketType>(&v1[0..4]).unwrap();
    let one = bincode::deserialize_from::<&[u8], One>(&v1[4..]).unwrap();
    dbg!(t1);
    dbg!(one);
    drop(v1);

    let t2 = bincode::deserialize_from::<&[u8], PacketType>(&v2[0..4]).unwrap();
    let two = bincode::deserialize_from::<&[u8], Two>(&v2[4..]).unwrap();
    dbg!(t2);
    dbg!(two);
    drop(v2);
}
