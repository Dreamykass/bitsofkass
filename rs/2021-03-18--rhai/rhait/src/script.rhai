

fn hello(n) {
    info("hello from rhai, adding up all numbers up to " + n);

    let sum = 0;

    for n in range(0, n) {
        sum += n;
    }

    info("sum: " + sum);
}

