
#include <swarmz.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <randmm.hpp>
#include <toml++/toml.h>
#include <fstream>

int main() {
  std::cout << "hello\n";
  try {
    auto config = toml::parse_file("config.toml");
    NiceRand randEngine(42);

    // read the boids from config.toml
    std::vector<sw::Boid> boids;
    for (const auto& bo : *config["Boids"].as_array()) {
      const auto& tabl = *bo.as_table();
      const auto& pos = *tabl["pos"].as_array();
      const auto& vel = *tabl["vel"].as_array();

      float pos1 = pos[0].as_floating_point()->get();
      float pos2 = pos[1].as_floating_point()->get();
      float pos3 = pos[2].as_floating_point()->get();
      float vel1 = vel[0].as_floating_point()->get();
      float vel2 = vel[1].as_floating_point()->get();
      float vel3 = vel[2].as_floating_point()->get();

      boids.push_back(
        sw::Boid(sw::Vec3(pos1, pos2, pos3), sw::Vec3(vel1, vel2, vel3)));
    }
    float randomnessDeviation =
      config["RandomnessDeviation"].as_floating_point()->get();

    // create and configure the swarm from config.toml
    sw::Swarm swarm(&boids);
    swarm.PerceptionRadius =
      config["PerceptionRadius"].as_floating_point()->get();
    swarm.SeparationWeight =
      config["SeparationWeight"].as_floating_point()->get();
    swarm.AlignmentWeight =
      config["AlignmentWeight"].as_floating_point()->get();
    swarm.CohesionWeight = config["CohesionWeight"].as_floating_point()->get();
    float deltaSeconds = config["DeltaSeconds"].as_floating_point()->get();

    // sfml window, view, and shape for drawing
    sf::RenderWindow window(sf::VideoMode(800, 800), "SWARMZ works!");
    window.setFramerateLimit(60);
    sf::CircleShape shape(config["ShapeRadius"].as_floating_point()->get());
    shape.setFillColor(sf::Color::Green);
    sf::View view;

    // -------------------------------------------------------------------------
    // main update and render loop
    while (window.isOpen()) {

      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }

      window.clear();

      swarm.Update(deltaSeconds);

      sf::Vector2f posMax = { 0.f, 0.f };
      sf::Vector2f posMin = { 0.f, 0.f };

      for (auto& boid : boids) {
        boid.Velocity.Z = 0.f;
        boid.Position += boid.Velocity * deltaSeconds;
        boid.Position.Z = 0.f;
        boid.Acceleration.Z = 0.f;

        //   boid.Velocity.X = randEngine.GetRealUniform(-1.f, 1.f);
        //   boid.Velocity.Y = randEngine.GetRealUniform(-1.f, 1.f);
        boid.Velocity.X = randEngine.GetRealNormal(0.f, randomnessDeviation);
        boid.Velocity.Y = randEngine.GetRealNormal(0.f, randomnessDeviation);

        posMax.x = std::max(posMax.x, boid.Position.X);
        posMax.y = std::max(posMax.y, boid.Position.Y);
        posMin.x = std::min(posMin.x, boid.Position.X);
        posMin.y = std::min(posMin.y, boid.Position.Y);

        shape.setPosition({ boid.Position.X, boid.Position.Y });
        window.draw(shape);
      }

      // keys
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        boids[0].Velocity.X -=
          config["OnKeyVelocityChange"].as_floating_point()->get();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        boids[0].Velocity.X +=
          config["OnKeyVelocityChange"].as_floating_point()->get();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        boids[0].Velocity.Y -=
          config["OnKeyVelocityChange"].as_floating_point()->get();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        boids[0].Velocity.Y +=
          config["OnKeyVelocityChange"].as_floating_point()->get();

      // view and display
      // float actualViewSize = std::max(posMax.x + posMin.x, posMax.y +
      // posMin.y); view.setSize(actualViewSize * 1.4f, actualViewSize * 1.4f);
      view.setSize(config["ViewSize"].as_floating_point()->get(),
                   config["ViewSize"].as_floating_point()->get());
      view.setCenter(boids[0].Position.X, boids[0].Position.Y);
      window.setView(view);

      std::cout << view.getCenter().x << "/" << view.getCenter().y << "\n";

      window.display();
    }
  } catch (const std::exception& e) {
    std::cerr << "\n\nException!";
    std::cerr << e.what();
  }
  std::cout << "bye\n";
  return 0;
}