
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <filesystem>
#include <optional>

// ================================= boring math starts here, fun stuff later

float dist(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

struct Point {
  int x, y;
};

struct Line {
  Point p1, p2;
};

bool onLine(Line l1, Point p) { // check whether p is on the line or not
  if (p.x <= std::max(l1.p1.x, l1.p2.x) && p.x <= std::min(l1.p1.x, l1.p2.x) &&
      (p.y <= std::max(l1.p1.y, l1.p2.y) && p.y <= std::min(l1.p1.y, l1.p2.y)))
    return true;

  return false;
}

int direction(Point a, Point b, Point c) {
  int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
  if (val == 0)
    return 0; // colinear
  else if (val < 0)
    return 2; // anti-clockwise direction
  return 1;   // clockwise direction
}

bool isIntersect(Line l1, Line l2) {
  // four direction for two lines and points of other line
  int dir1 = direction(l1.p1, l1.p2, l2.p1);
  int dir2 = direction(l1.p1, l1.p2, l2.p2);
  int dir3 = direction(l2.p1, l2.p2, l1.p1);
  int dir4 = direction(l2.p1, l2.p2, l1.p2);

  if (dir1 != dir2 && dir3 != dir4)
    return true; // they are intersecting

  if (dir1 == 0 && onLine(l1, l2.p1)) // when p2 of line2 are on the line1
    return true;

  if (dir2 == 0 && onLine(l1, l2.p2)) // when p1 of line2 are on the line1
    return true;

  if (dir3 == 0 && onLine(l2, l1.p1)) // when p2 of line1 are on the line2
    return true;

  if (dir4 == 0 && onLine(l2, l1.p2)) // when p1 of line1 are on the line2
    return true;

  return false;
}

// ========================================== boring math ends, fun stuff begins

constexpr int window_x = 600;
constexpr int window_y = 600;

struct Light {
  int x;
  int y;
  float radius;
  float r;
  float g;
  float b;
};

int main() {
  std::srand(42);

  sf::RenderWindow window(sf::VideoMode(window_x, window_y), "SFML works!");
  window.setFramerateLimit(30);

  sf::VertexArray pixels(sf::Points, window_x * window_y);

  for (auto x = 0; x < window_x; x++) {
    for (auto y = 0; y < window_y; y++) {
      pixels[window_x * x + y].position = sf::Vector2f(x, y);
    }
  }

  auto light_under_mouse = 0;
  std::vector<Light> lights;
  lights.push_back(Light{ 200, 200, 100.f, 255, 10, 10 });
  lights.push_back(Light{ 200, 200, 200.f, 255, 255, 255 });
  lights.push_back(Light{ 300, 500, 200.f, 100, 255, 60 });
  lights.push_back(Light{ 400, 300, 200.f, 4, 255, 255 });

  std::vector<Line> walls;
  walls.push_back(Line{ { 0, 0 }, { 100, 200 } });
  walls.push_back(Line{ { std::rand() % window_x, std::rand() % window_y },
                        { std::rand() % window_x, std::rand() % window_y } });
  walls.push_back(Line{ { 444, 444 }, { 222, 555 } });
  walls.push_back(Line{ { std::rand() % window_x, std::rand() % window_y },
                        { std::rand() % window_x, std::rand() % window_y } });
  walls.push_back(Line{ { std::rand() % window_x, std::rand() % window_y },
                        { std::rand() % window_x, std::rand() % window_y } });

  sf::VertexArray wall_verts(sf::Lines, 0);
  for (auto wall : walls) {
    wall_verts.append(sf::Vertex{});
    auto& v = wall_verts[wall_verts.getVertexCount() - 1];
    v.position = sf::Vector2f(wall.p1.x, wall.p1.y);
    v.color = sf::Color(255, 0, 0);

    wall_verts.append(sf::Vertex{});
    auto& v2 = wall_verts[wall_verts.getVertexCount() - 1];
    v2.position = sf::Vector2f(wall.p2.x, wall.p2.y);
    v2.color = sf::Color(255, 0, 0);
  }

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyReleased)
        light_under_mouse =
          light_under_mouse < lights.size() - 1 ? light_under_mouse + 1 : 0;
    }

    lights[light_under_mouse].x = sf::Mouse::getPosition(window).x;
    lights[light_under_mouse].y = sf::Mouse::getPosition(window).y;

    window.clear();

    for (auto x = 0; x < window_x; x++) {
      for (auto y = 0; y < window_y; y++) {
        auto& pixel = pixels[window_x * x + y].color;
        pixel = sf::Color(0, 0, 0);

        // auto intensity = 0.f;
        auto r = 0.f;
        auto g = 0.f;
        auto b = 0.f;

        for (auto light : lights) {
          auto d = dist(light.x, light.y, x, y);
          if (d < light.radius) {
            auto intersects_through_any = false;
            for (auto wall : walls) {
              if (isIntersect(wall, { { light.x, light.y }, { x, y } })) {
                intersects_through_any = true;
              }
            }
            if (!intersects_through_any) {
              // intensity += (d / light.radius) * 255 * -1;
              r +=
                (((light.radius - d) / light.radius) * (light.r / 255) * 255);
              g +=
                (((light.radius - d) / light.radius) * (light.g / 255) * 255);
              b +=
                (((light.radius - d) / light.radius) * (light.b / 255) * 255);
              // 0 += 50 / 200
            }
          }
        }
        // pixel = sf::Color(r, g, b);
        pixel = sf::Color(std::clamp(r, 0.f, 255.f),
                          std::clamp(g, 0.f, 255.f),
                          std::clamp(b, 0.f, 255.f));
      }
    }

    window.draw(pixels);
    window.draw(wall_verts);
    window.display();
  }

  return 0;
}