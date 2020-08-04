
#include <SFML/Graphics.hpp>
#include <vector>

struct circlePos {
  sf::Vector2f startingPos;
  sf::Vector2f currentPos;
};

circlePos positionFixer(circlePos cc) {
  if (cc.currentPos.y > 600.f)
    cc.currentPos -= { 800.f, 800.f };
  return cc;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
  window.setFramerateLimit(60);

  sf::CircleShape circleShape(40.f);
  circleShape.setFillColor(sf::Color::Green);

  std::vector<circlePos> circlePositions;

  for (float x = -800.f; x < 800.f; x += 100.f) {
    for (float y = -800.f; y < 800.f; y += 100.f) {
      circlePos ccPos;
      ccPos.currentPos = { x, y };
      ccPos.startingPos = ccPos.currentPos;
      circlePositions.push_back(ccPos);
    }
  }

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    for (const auto& cc : circlePositions) {
      circleShape.setPosition(cc.currentPos);
      window.draw(circleShape);
    }

    for (auto& cc : circlePositions) {
      cc.currentPos += sf::Vector2f(2.f, 2.f);
      cc = positionFixer(cc);
    }

    window.display();
  }

  return 0;
}