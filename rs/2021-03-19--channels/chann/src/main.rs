use crossbeam::channel::{after, never, select, tick, unbounded};
use std::time::{Duration, Instant};

fn time_begin_period() {
    // https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
    unsafe {
        let p = 1u32;
        let err = winapi::um::timeapi::timeBeginPeriod(p);
        match err {
            winapi::um::mmsystem::TIMERR_NOERROR => println!("TIMERR_NOERROR"),
            winapi::um::mmsystem::TIMERR_NOCANDO => println!("TIMERR_NOCANDO"),
            _ => panic!("neither TIMERR_NOERROR nor TIMERR_NOCANDO"),
        }
    }
}

const DURATION: Duration = Duration::from_millis(1);

fn main() {
    println!("Hello, world!");
    time_begin_period();

    let timeout = after(Duration::from_millis(40));

    let mut ticker_start = Instant::now();
    let ticker = tick(DURATION);

    let mut std_sleep_start = Instant::now();
    let (std_sleep_sender, std_sleep) = unbounded::<()>();
    std::thread::spawn(move || loop {
        std::thread::sleep(DURATION);
        let _ = std_sleep_sender.send(());
    });

    let mut spin_sleep_start = Instant::now();
    let (spin_sleep_sender, spin_sleep) = unbounded::<()>();
    std::thread::spawn(move || loop {
        // spin_sleep::sleep(Duration::from_millis(1));
        let spin_sleeper = spin_sleep::SpinSleeper::new(2_000_000); // 2ms
        spin_sleeper.sleep(DURATION);
        let _ = spin_sleep_sender.send(());
    });

    loop {
        select! {
            recv(ticker) -> _ => {
                println!("elapsed in ticker: {:?}", ticker_start.elapsed());
                ticker_start = Instant::now();
            },
            recv(std_sleep) -> _ => {
                println!("elapsed in std_sleep: {:?}", std_sleep_start.elapsed());
                std_sleep_start = Instant::now();
            },
            recv(spin_sleep) -> _ => {
                println!("elapsed in spin_sleep: {:?}", spin_sleep_start.elapsed());
                spin_sleep_start = Instant::now();
            },
            recv(timeout) -> _ => break,
            recv(never::<()>()) -> _ => {},
        }
    }

    println!("Done.");
}
