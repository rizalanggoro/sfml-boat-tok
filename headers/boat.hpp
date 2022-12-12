#ifndef boat_hpp
#define boat_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Boat
{
private:
  vector<Texture> vectorBoatFrame;
  vector<Texture> vectorCannonFrame;

  vector<Sprite> vectorFire;

  Sprite spriteBoat1;
  Sprite spriteCannon1;

  Texture textureFire{};

  Clock clock, clockCannon;

  int boatFrameInterval;
  int cannonFrameInterval;

  int boatFrameDelay = 150;
  int cannonDelay = 200;

  int currBoatFrameIn = 0;
  int currCannonFrameIn = 0;

  int fireSpeed = 10;
  int boatSpeed = 5;

  bool isShooting = false;

  void init()
  {
    // load boat 1
    for (int a = 1; a <= 4; a++)
    {
      Texture frame{};
      auto fileName = "assets/images/Boat1_water_animation_color1/Boat1_water_frame" + to_string(a) + ".png";
      frame.loadFromFile(fileName);
      this->vectorBoatFrame.push_back(frame);
    }

    // load cannon 1
    for (int a = 1; a <= 4; a++)
    {
      Texture frame{};
      auto fileName = "assets/images/Cannon3_color1/Cannon3_color1_" + to_string(a) + ".png";
      frame.loadFromFile(fileName);
      this->vectorCannonFrame.push_back(frame);
    }

    // load fire
    {
      this->textureFire.loadFromFile("assets/images/Fire2/Fire2_2.png");
    }
  }

public:
  Boat()
  {
    this->init();
  }

  void loop()
  {
    this->boatFrameInterval = this->clock.getElapsedTime().asMilliseconds();
    this->cannonFrameInterval = this->clockCannon.getElapsedTime().asMilliseconds();
  }

  void right()
  {
    this->spriteBoat1.move(Vector2f(5, 0));
    this->spriteCannon1.move(Vector2f(5, 0));
  }

  void left()
  {
    this->spriteBoat1.move(Vector2f(-5, 0));
    this->spriteCannon1.move(Vector2f(-5, 0));
  }

  void up()
  {
    this->spriteBoat1.move(Vector2f(0, -5));
    this->spriteCannon1.move(Vector2f(0, -5));
  }

  void down()
  {
    this->spriteBoat1.move(Vector2f(0, 5));
    this->spriteCannon1.move(Vector2f(0, 5));
  }

  void fire() { this->isShooting = true; }

  void draw(RenderWindow &window)
  {
    this->spriteBoat1.setTexture(this->vectorBoatFrame.at(this->currBoatFrameIn));

    this->spriteCannon1.setTexture(this->vectorCannonFrame.at(this->currCannonFrameIn));

    auto boatPos = this->spriteBoat1.getPosition();

    auto boatW = this->spriteBoat1.getGlobalBounds().width;
    auto boatH = this->spriteBoat1.getGlobalBounds().height;

    auto cannonW = this->spriteCannon1.getGlobalBounds().width;
    auto cannonH = this->spriteCannon1.getGlobalBounds().height;

    auto cannonPos = Vector2f(boatPos.x + (boatW - cannonW) / 2,
                              boatPos.y + (boatH - cannonH) / 2);

    this->spriteCannon1.setPosition(cannonPos);

    if (this->isShooting)
    {
      auto delay = this->cannonDelay /
                   this->vectorCannonFrame.size();
      if (this->cannonFrameInterval >= delay)
      {
        if (this->currCannonFrameIn < this->vectorCannonFrame.size() - 1)
          this->currCannonFrameIn++;
        else
        {
          this->currCannonFrameIn = 0;
          this->isShooting = false;

          Sprite spriteFire{};
          spriteFire.setTexture(this->textureFire);

          auto fireW = spriteFire.getGlobalBounds().width;
          auto fireH = spriteFire.getGlobalBounds().height;

          spriteFire.setPosition(
              Vector2f(
                  boatPos.x + cannonW, boatPos.y + (boatH - fireH) / 2));

          this->vectorFire.push_back(spriteFire);
        }
        this->clockCannon.restart();
      }
    }

    if (this->boatFrameInterval >= this->boatFrameDelay)
    {
      if (this->currBoatFrameIn < this->vectorBoatFrame.size() - 1)
        this->currBoatFrameIn++;
      else
        this->currBoatFrameIn = 0;
      this->clock.restart();
    }

    // auto scale = Vector2f(2, 2);
    // this->spriteBoat1.setScale(scale);
    // this->spriteCannon1.setScale(scale);

    window.draw(this->spriteBoat1);
    window.draw(this->spriteCannon1);

    // draw sprite fire
    for (int a = 0; a < this->vectorFire.size(); a++)
    {
      window.draw(this->vectorFire.at(a));
      this->vectorFire.at(a).move(Vector2f(this->fireSpeed, 0));
      if (this->vectorFire.at(a).getPosition().x >= window.getSize().x)
        this->vectorFire.erase(this->vectorFire.begin() + a);
    }
  }
};

#endif