use crossbeam::channel::{after, never, select, tick, unbounded};
use std::time::{Duration, Instant};

fn main() {
    println!("Hello, world!");

    let timeout = after(Duration::from_millis(100));

    let ticker_start = Instant::now();
    let ticker = tick(Duration::from_millis(16));

    let std_sleep_start = Instant::now();
    let (std_sleep_sender, std_sleep) = unbounded::<()>();
    std::thread::spawn(move || loop {
        std::thread::sleep(Duration::from_millis(16));
        std_sleep_sender.send(()).unwrap();
    });

    let spin_sleep_start = Instant::now();
    let (spin_sleep_sender, spin_sleep) = unbounded::<()>();
    std::thread::spawn(move || loop {
        spin_sleep::sleep(Duration::from_millis(16));
        spin_sleep_sender.send(()).unwrap();
    });

    loop {
        select! {
            recv(ticker) -> _ => println!("elapsed in ticker: {:?}", ticker_start.elapsed()),
            recv(std_sleep) -> _ => println!("elapsed in std_sleep: {:?}", std_sleep_start.elapsed()),
            recv(spin_sleep) -> _ => println!("elapsed in spin_sleep: {:?}", spin_sleep_start.elapsed()),
            recv(timeout) -> _ => break,
            recv(never::<()>()) -> _ => {},
        }
    }

    println!("Done.");
}
