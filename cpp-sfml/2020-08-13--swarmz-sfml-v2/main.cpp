
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

    // generate the boids
    std::vector<sw::Boid> boids;
    auto boidAmount = config["BoidAmount"].as_integer()->get();
    for (int64_t i = 0; i < boidAmount; i++) {
      auto r = [&]() { return randEngine.GetRealUniform(-400.f, 400.f); };
      boids.push_back(
        sw::Boid(sw::Vec3(r(), r(), r()), sw::Vec3(r(), r(), r())));
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
    shape.setFillColor(sf::Color::Red);
    sf::View view;
    view.setCenter(0.f, 0.f);
    view.setSize(800.f, 800.f);
    window.setView(view);

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

      for (auto& boid : boids) {
        boid.Velocity.Z = 0.f;
        boid.Position += boid.Velocity * deltaSeconds;
        boid.Position.Z = 0.f;
        boid.Acceleration.Z = 0.f;

        while (boid.Position.X < -400.f)
          boid.Position.X += 800.f;
        while (boid.Position.X > 400.f)
          boid.Position.X -= 800.f;

        while (boid.Position.Y < -400.f)
          boid.Position.Y += 800.f;
        while (boid.Position.Y > 400.f)
          boid.Position.Y -= 800.f;

        boid.Velocity.X += randEngine.GetRealNormal(0.f, randomnessDeviation);
        boid.Velocity.Y += randEngine.GetRealNormal(0.f, randomnessDeviation);

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
      window.display();
    }
  } catch (const std::exception& e) {
    std::cerr << "\n\nException!";
    std::cerr << e.what();
  }
  std::cout << "bye\n";
  return 0;
}