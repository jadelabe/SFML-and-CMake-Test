#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine/controls.h"
#include "Engine/drawmap.h"
#include "config.h"

  int main(int argc, char* argv[]){

    sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "game");
    window.setVerticalSyncEnabled(false);
    Controls *controls = new Controls;
    DrawMap *drawmap = new DrawMap(RES_X, RES_Y, 8,8);


    while (window.isOpen()){
      controls->handleEvents(window);
      window.clear(sf::Color::Black);
      drawmap->draw(window);
      window.display();
    }
    return 0;
  }
