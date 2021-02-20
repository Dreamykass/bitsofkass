fn get_string() -> String {
    let mut out = "".to_string();
    std::io::stdin().read_line(&mut out).unwrap();
    out
}

fn main() {
    println!("\n\nHello, world!");
    let (sock, addr) = stunclient::just_give_me_the_udp_socket_and_its_external_address();
    println!("Our address: {}", addr);

    println!("Other address > ");
    let other_addr = get_string().trim().to_string();
    println!("[{}]", other_addr);

    println!("Sender (s) or receiver (r) >");
    let sender_or_receiver = get_string();

    // sock.connect(other_addr).unwrap();

    if sender_or_receiver.starts_with("s") {
        println!("sending!");
        loop {
            // sock.connect(&other_addr).unwrap();
            // sock.send(b"hello").unwrap();
            sock.send_to(b"hello", &other_addr).unwrap();
            println!("sent...");
            std::thread::sleep(std::time::Duration::from_millis(10));
        }
    } else {
        println!("receiving!");
        loop {
            // sock.connect(&other_addr).unwrap();
            let mut buffer = [0u8; 32];
            // sock.recv(&mut buffer).unwrap();
            sock.recv_from(&mut buffer).unwrap();
            println!("{:?}", buffer);
            println!("received..?");
        }
    }
}
