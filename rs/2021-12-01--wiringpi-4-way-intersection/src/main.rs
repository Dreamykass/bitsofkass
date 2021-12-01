use std::time::Instant;
use std::{thread, time};
use wiringpi::pin::Value::{High, Low};
use wiringpi::pin::{InputPin, OutputPin, WiringPi};

struct PinSet {
    yellow: OutputPin<WiringPi>,
    green: OutputPin<WiringPi>,
    red: OutputPin<WiringPi>,
    button: InputPin<WiringPi>,
}

struct Road<'a> {
    cars_waiting: u16,
    cycles_since_green: u16,
    pins: &'a PinSet,
}

#[derive(Debug, Clone, Copy)]
enum State {
    AllRedIdle,
    AllRedEvaluatingRoads,
    Yellow { road_id: usize },
    Green { road_id: usize },
    YellowFlashing { road_id: usize },
}

fn print_world(pins: &[PinSet], roads: &[Road], state: &State) {
    println!("==========================");
    println!("state: {:?}", state);
    for (road_id, road) in roads.iter().enumerate() {
        println!(
            "road {}; waiting: {}; cycles since green: {}",
            road_id, road.cars_waiting, road.cycles_since_green
        );
    }
}

fn main() {
    let pi = wiringpi::setup();

    let pins = [
        PinSet {
            yellow: pi.output_pin(0),
            green: pi.output_pin(0),
            red: pi.output_pin(0),
            button: pi.input_pin(0),
        },
        PinSet {
            yellow: pi.output_pin(0),
            green: pi.output_pin(0),
            red: pi.output_pin(0),
            button: pi.input_pin(0),
        },
        PinSet {
            yellow: pi.output_pin(0),
            green: pi.output_pin(0),
            red: pi.output_pin(0),
            button: pi.input_pin(0),
        },
        PinSet {
            yellow: pi.output_pin(0),
            green: pi.output_pin(0),
            red: pi.output_pin(0),
            button: pi.input_pin(0),
        },
    ];

    let mut roads = [
        Road {
            cars_waiting: 0,
            cycles_since_green: 0,
            pins: &pins[0],
        },
        Road {
            cars_waiting: 0,
            cycles_since_green: 0,
            pins: &pins[1],
        },
        Road {
            cars_waiting: 0,
            cycles_since_green: 0,
            pins: &pins[2],
        },
        Road {
            cars_waiting: 0,
            cycles_since_green: 0,
            pins: &pins[3],
        },
    ];

    for p in &pins {
        p.yellow.digital_write(High);
        p.green.digital_write(High);
        p.red.digital_write(High);
    }

    thread::sleep(time::Duration::from_millis(1000));

    for p in &pins {
        p.yellow.digital_write(Low);
        p.green.digital_write(Low);
        p.red.digital_write(Low);
    }

    let mut state = State::AllRedIdle;
    let mut state_start_time = Instant::now();

    loop {
        print_world(&pins, &roads, &state);

        let mut next_state = State::AllRedIdle;
        match state {
            State::AllRedIdle => {
                // turn all red lights on
                for p in &pins {
                    p.yellow.digital_write(Low);
                    p.green.digital_write(Low);
                    p.red.digital_write(High);
                }

                // change state if enough time has passed
                if state_start_time.elapsed().as_millis() > 1000 {
                    next_state = State::AllRedEvaluatingRoads;
                    state_start_time = Instant::now();
                }
            }
            State::AllRedEvaluatingRoads => {
                // turn all red lights on
                for p in &pins {
                    p.yellow.digital_write(Low);
                    p.green.digital_write(Low);
                    p.red.digital_write(High);
                }

                let total_cars_waiting = roads.iter().map(|r| r.cars_waiting).sum::<u16>();
                if total_cars_waiting == 0 {
                    // if no cars present, go back to AllRedIdle
                    next_state = State::AllRedIdle;
                    state_start_time = Instant::now();
                    for road in &mut roads {
                        road.cycles_since_green = 0;
                    }
                } else {
                    // cars present, select road to make yellow
                    let highest_cycles_since_green = roads
                        .iter()
                        .max_by(|r1, r2| r1.cycles_since_green.cmp(&r2.cycles_since_green))
                        .unwrap()
                        .cycles_since_green;
                    let road_id_with_most_cars_and_highest_cycles = roads
                        .iter()
                        .enumerate()
                        .filter(|(_, r)| r.cycles_since_green == highest_cycles_since_green)
                        .max_by(|(_, r1), (_, r2)| r1.cars_waiting.cmp(&r2.cars_waiting))
                        .unwrap()
                        .0;
                    next_state = State::Yellow {
                        road_id: road_id_with_most_cars_and_highest_cycles,
                    };
                    state_start_time = Instant::now();
                }
            }
            State::Yellow { road_id } => {
                roads[road_id].pins.yellow.digital_write(High);
                roads[road_id].pins.green.digital_write(Low);
                roads[road_id].pins.red.digital_write(Low);
                if state_start_time.elapsed().as_millis() > 1000 {
                    next_state = State::Green { road_id };
                    state_start_time = Instant::now();
                }
            }
            State::Green { road_id } => {
                roads[road_id].pins.yellow.digital_write(Low);
                roads[road_id].pins.green.digital_write(High);
                roads[road_id].pins.red.digital_write(Low);
                if state_start_time.elapsed().as_millis() > 1000 {
                    next_state = State::YellowFlashing { road_id };
                    state_start_time = Instant::now();
                }
            }
            State::YellowFlashing { road_id } => {
                roads[road_id].pins.yellow.digital_write(High);
                roads[road_id].pins.green.digital_write(Low);
                roads[road_id].pins.red.digital_write(High);
                if state_start_time.elapsed().as_millis() > 500 {
                    next_state = State::AllRedEvaluatingRoads;
                    state_start_time = Instant::now();
                }
            }
        }
        state = next_state;

        thread::sleep(time::Duration::from_millis(100));
    }
}
