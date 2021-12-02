use cursive::views::*;

fn main() {
    let mut siv = cursive::default();

    let left_layout = {
        Panel::new(
            LinearLayout::vertical()
                .child(Button::new("Quit", |s| s.quit()))
                .child(Button::new("Quit", |s| s.quit())),
        )
    };

    let right_layout = {
        Panel::new(
            LinearLayout::vertical()
                .child(TextView::new("Hello world!"))
                .child(TextView::new("Hello world!")),
        )
    };

    let linear_layout = LinearLayout::horizontal()
        .child(left_layout)
        .child(right_layout);

    siv.add_layer(linear_layout);

    siv.run();
}
