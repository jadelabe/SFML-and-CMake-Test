#include "controls.h"
#include<iostream>

using namespace std;

void Controls::handleEvents(sf::RenderWindow& window){

  while (window.pollEvent(event)){

    if(event.type == sf::Event::TextEntered){
      cout << "Pressed: " << static_cast<char>(event.text.unicode) << endl;
    }
    else if (event.type == sf::Event::Resized){
      cout << "new width: " << event.size.width << endl;
      cout << "new height: " << event.size.height << endl;
    }
    else if (event.type == sf::Event::Closed){
      cout << "Closing Window" << endl;
      window.close();
    }
  }
}
