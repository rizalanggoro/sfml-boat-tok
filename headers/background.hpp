#ifndef background_hpp
#define background_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Background
{
private:
  Texture textureWater;
  vector<Sprite> vectorWater;
  Sprite spriteWater;

  void init()
  {
    this->textureWater.setSmooth(true);
    this->textureWater.loadFromFile("assets/images/water/tile_0083_water10.png");
  }

public:
  Background()
  {
    this->init();
  }
  void draw(RenderWindow &window)
  {
    this->spriteWater.setTexture(this->textureWater);

    auto waterW = this->spriteWater.getGlobalBounds().width;
    auto waterH = this->spriteWater.getGlobalBounds().height;

    auto windowW = window.getSize().x;
    auto windowH = window.getSize().y;

    this->vectorWater.clear();
    for (int r = 0; r < (windowW / waterW); r++)
    {
      for (int c = 0; c < (windowH / waterH); c++)
      {
        this->spriteWater.setPosition(Vector2f(
            r * waterW, c * waterH));
        this->vectorWater.push_back(this->spriteWater);
      }
    }

    for (int a = 0; a < this->vectorWater.size(); a++)
      window.draw(this->vectorWater.at(a));
  }
};

#endif