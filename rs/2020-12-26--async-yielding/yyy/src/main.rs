use rand::Rng;

async fn foo() {
    println!("foo");
    let mut v = Vec::new();
    for i in 0..100 {
        v.push(bar(i));
    }
    for f in v {
        f.await;
    }
}

async fn my_yield() {}

async fn bar(i: i32) {
    let r = rand::thread_rng().gen_range(0..40);
    // async_std::task::sleep(std::time::Duration::from_millis(r)).await;
    for _ in 0..r {
        // std::thread::sleep(std::time::Duration::from_millis(1));
        async_std::task::sleep(std::time::Duration::from_millis(1)).await;
        // my_yield().await;
        // async_std::task::yield_now().await;
    }
    println!("{}", i);
}

fn main() {
    futures::executor::block_on(foo());
}
