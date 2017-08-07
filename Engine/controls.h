#ifndef Controls_H
#define Controls_H
#include <SFML/Graphics.hpp>

class Controls{

  private :
    sf::Event event;

  public :
    void handleEvents(sf::RenderWindow&);
    struct control;

};

#endif
