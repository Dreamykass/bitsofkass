#include <SFML/Graphics.hpp>
#include <filesystem> // C++17 required
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  window.setFramerateLimit(60);

  sf::VertexArray vertex_array;
  vertex_array.setPrimitiveType(sf::PrimitiveType::Quads);
  vertex_array.resize(4);

  // play around with these:
  vertex_array[0].position = { 0, 0 };
  vertex_array[1].position = { 0, 200 };
  vertex_array[2].position = { 100, 100 };
  vertex_array[3].position = { 100, 0 };

  // and these:
  vertex_array[0].texCoords = { 0, 0 };
  vertex_array[1].texCoords = { 0, 100 };
  vertex_array[2].texCoords = { 100, 100 };
  vertex_array[3].texCoords = { 100, 0 };

  sf::Texture texture;
  if (!std::filesystem::exists("texture.png")) {
    std::cout << "texture.png doesn't exist\n";
    std::cout << "current dir: " << std::filesystem::current_path() << "\n";
  }
  if (!texture.loadFromFile("texture.png")) {
    std::cout << "couldn't load texture.png";
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(vertex_array, &texture);
    window.display();
  }

  return 0;
}