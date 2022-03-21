
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();

    sf::FloatRect rect_a{ 100, 100, 100, 100 };
    sf::RectangleShape rectshape_a{ { rect_a.width, rect_a.height } };
    rectshape_a.setPosition({ rect_a.left, rect_a.top });
    rectshape_a.setFillColor(sf::Color::Red);
    window.draw(rectshape_a);

    sf::FloatRect rect_mouse{
      (float)(sf::Mouse::getPosition().x - window.getPosition().x),
      (float)(sf::Mouse::getPosition().y - window.getPosition().y),
      100,
      100
    };
    sf::RectangleShape rectshape_mouse{ { rect_a.width, rect_a.height } };
    rectshape_mouse.setPosition({ rect_mouse.left, rect_mouse.top });
    rectshape_mouse.setFillColor(sf::Color::Blue);
    window.draw(rectshape_mouse);

    sf::FloatRect rect_overlap{ 100, 100, 100, 100 };
    rect_a.intersects(rect_mouse, rect_overlap);
    sf::RectangleShape rectshape_overlap{ { rect_overlap.width,
                                            rect_overlap.height } };
    rectshape_overlap.setPosition({ rect_overlap.left, rect_overlap.top });
    rectshape_overlap.setFillColor(sf::Color::Yellow);
    window.draw(rectshape_overlap);

    window.display();
  }

  return 0;
}