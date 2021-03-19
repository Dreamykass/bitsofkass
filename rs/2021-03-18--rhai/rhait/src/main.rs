use rhai::{Engine, EvalAltResult, RegisterFn};

fn logger_fn(
    writer: &mut dyn std::io::Write,
    now: &mut flexi_logger::DeferredNow,
    record: &flexi_logger::Record,
) -> Result<(), std::io::Error> {
    write!(
        writer,
        "[{}] [{}] [{}:{}] [{}] - {}",
        now.now().format("%H:%M:%S%.6f"),
        record.module_path().unwrap_or("<unnamed>"),
        record.file().unwrap_or("<unnamed>"),
        record.line().unwrap_or(0),
        record.level(),
        &record.args()
    )
}

mod logging_fns {
    use log::*;

    pub fn info(msg: &str) {
        info!("rhai says: {}", msg);
    }
}

fn main() -> Result<(), Box<EvalAltResult>> {
    flexi_logger::Logger::with_str("debug")
        .format(logger_fn)
        .start()
        .unwrap();
    log::info!("logging from rust");

    let mut engine = Engine::new();

    engine.register_fn("info", logging_fns::info);

    let ast = engine.compile_file("src/script.rhai".into())?;
    let mut scope = rhai::Scope::new();

    // engine.eval_ast(&ast)?;
    engine.call_fn(&mut scope, &ast, "hello", (6i64,))?;

    Ok(())
}
