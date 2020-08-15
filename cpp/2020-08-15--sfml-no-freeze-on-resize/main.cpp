
#include <iostream>
#include <SFML/Graphics.hpp>

#include <thread>
#include <future>
#include <atomic>
#include <chrono>

void renderer_f(sf::RenderWindow& window, std::mutex& window_mutex) {

  auto init_lock = std::unique_lock(window_mutex);
  window.setActive(true);

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  window.setActive(false);
  init_lock.unlock();

  while (true) {
    auto lock = std::unique_lock(window_mutex);
    window.setActive(true);

    {
      window.clear();

      window.draw(shape);
      if (shape.getPosition().x < static_cast<float>(window.getSize().x))
        shape.move({ 10.f, 10.f });
      else
        shape.setPosition({ -100.f, -100.f });

      window.display();
    }

    if (!window.isOpen())
      break;

    window.setActive(false);
    lock.unlock();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(8ms);
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  window.setFramerateLimit(60);

  window.setActive(false);
  std::mutex window_mutex;

  auto renderer = std::async(
    std::launch::async, renderer_f, std::ref(window), std::ref(window_mutex));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        auto lock = std::unique_lock(window_mutex);
        window.close();

      } else if (event.type == sf::Event::Resized) {
        auto new_view = window.getDefaultView();
        new_view.setSize(static_cast<sf::Vector2f>(window.getSize()));
        window.setView(new_view);
      }
    }
  }

  renderer.get();
  auto lock = std::unique_lock(window_mutex);
  return 0;
}