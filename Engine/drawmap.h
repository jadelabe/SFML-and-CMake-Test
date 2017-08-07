#ifndef DrawMap_H
#define DrawMap_H
#include <SFML/Graphics.hpp>
#include "config.h"

#include <iostream>
#include "math.h"

class DrawMap{

	public:

		DrawMap(int, int, int, int);
		void draw(sf::RenderWindow&);
		int** getMap();

	private :
		void calculateDimensions();
		void generateDrawables();

		int** generateMap(int **map);

		int horizontalTiles, verticalTiles, horizontalRes, verticalRes;
		int vertexNum, edgesNum, vertexGap, vertexGapX, vertexGapY, knockoutGap, knockoutGapX, knockoutGapY;
		int **map;

		sf::Vector2f gridOrigin, knockoutOrigin, **vertexPos;
		sf::CircleShape** vertex;
		sf::RectangleShape **edgesH, **edgesV;

		//Colors of the Grid
		int gridColR = 250, gridColG = 150, gridColB = 100;
		//Map origin boundaries percentiles
		float boundTopEdge = 0.1f, boundBotEdge = 0.1f;
		float boundLefEdge = 0.1f, boundRigEdge = 0.1f;
		float knockoutEdge = 0.07f;
};

#endif
