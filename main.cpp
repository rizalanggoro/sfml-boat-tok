#include <SFML/Graphics.hpp>
#include <iostream>

#include "headers/boat.hpp"
#include "headers/background.hpp"

using namespace sf;
using namespace std;

int main()
{
  RenderWindow window(VideoMode(1280, 720), "Boat TOK", Style::Default);

  window.setFramerateLimit(60);

  // create a new boat
  Boat boat{};
  Background background{};

  while (window.isOpen())
  {
    boat.loop();

    Event event{};
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
        window.close();
    }

    if (Keyboard::isKeyPressed(Keyboard::Space))
      boat.fire();

    if (Keyboard::isKeyPressed(Keyboard::Right))
      boat.right();

    if (Keyboard::isKeyPressed(Keyboard::Left))
      boat.left();

    if (Keyboard::isKeyPressed(Keyboard::Up))
      boat.up();

    if (Keyboard::isKeyPressed(Keyboard::Down))
      boat.down();

    window.clear(Color::White);

    background.draw(window);
    boat.draw(window);

    window.display();
  }

  return 0;
}