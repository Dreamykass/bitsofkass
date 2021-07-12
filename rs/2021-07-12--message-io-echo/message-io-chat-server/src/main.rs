use message_io::network::{NetEvent, Transport};
use message_io::node;

fn main() {
    println!("Hello from the server!");
    let (handler, listener) = node::split::<()>();

    handler
        .network()
        .listen(Transport::FramedTcp, "0.0.0.0:3042")
        .unwrap();

    handler
        .network()
        .listen(Transport::Udp, "0.0.0.0:3043")
        .unwrap();

    listener.for_each(move |event| match event.network() {
        NetEvent::Connected(_, _) => unreachable!(),
        NetEvent::Accepted(_endpoint, _listener) => println!("Client connected"),
        NetEvent::Message(endpoint, data) => {
            println!("Received: {}", String::from_utf8_lossy(data));
            handler.network().send(endpoint, data);
        }
        NetEvent::Disconnected(_endpoint) => println!("Client disconnected"),
    });
}
