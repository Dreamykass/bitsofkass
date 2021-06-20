
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <sstream>

// usage like std::lerp
sf::Color color_lerp(sf::Color a, sf::Color b, float t) {
  return { static_cast<uint8_t>(std::lerp(a.r, b.r, t)),
           static_cast<uint8_t>(std::lerp(a.g, b.g, t)),
           static_cast<uint8_t>(std::lerp(a.b, b.b, t)) };
}

// a - top-left, b - top-right
// c - bottom-right, d - bottom-left
// uv - ([0.0, 1.0], [0.0, 1.0])
sf::Color bilinear_interp(sf::Color a,
                          sf::Color b,
                          sf::Color c,
                          sf::Color d,
                          sf::Vector2f uv) {
  sf::Color c_top = color_lerp(a, b, uv.x);
  sf::Color c_bot = color_lerp(c, d, uv.x);
  sf::Color c_uv = color_lerp(c_bot, c_top, 1.0f - uv.y);
  return c_uv;
}

int main() {
  const int w_size = 400;
  sf::RenderWindow window(sf::VideoMode(w_size, w_size), "SFML works!");
  window.setFramerateLimit(30);

  sf::Color color = { 0, 255, 0 };

  sf::Vector2f mouse_pos = { 0.f, 0.f };

  while (window.isOpen()) {
    for (sf::Event event; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::MouseMoved) {
        mouse_pos.x = static_cast<float>(event.mouseMove.x) / w_size;
        mouse_pos.y = static_cast<float>(event.mouseMove.y) / w_size;
      }
    }

    window.setSize({ w_size, w_size });

    std::array<sf::Vertex, 4> vertices = {
      sf::Vertex{ { 0.0f, 0.0f }, { 255, 255, 255 } }, // top-left white
      sf::Vertex{ { w_size, 0.0f }, color },           // top-right color
      sf::Vertex{ { 0.0f, w_size }, { 0, 0, 0 } },     // bottom-left black
      sf::Vertex{ { w_size, w_size }, { 0, 0, 0 } }    // bottom-right black
    };

    window.clear();
    window.draw(vertices.data(), 4, sf::PrimitiveType::TriangleStrip);
    window.display();

    sf::Color c_under_mouse = bilinear_interp(vertices[0].color,
                                              vertices[1].color,
                                              vertices[3].color,
                                              vertices[2].color,
                                              mouse_pos);
    auto new_title = std::stringstream()
                     << "rgb: (" << static_cast<int>(c_under_mouse.r) << ", "
                     << static_cast<int>(c_under_mouse.g) << ", "
                     << static_cast<int>(c_under_mouse.b) << "); "
                     << "mouse pos: (" << mouse_pos.x << ", " << mouse_pos.y
                     << ")";
    window.setTitle(new_title.str());
  }

  return 0;
}