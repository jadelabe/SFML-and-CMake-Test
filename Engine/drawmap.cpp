#include "drawmap.h"


DrawMap::DrawMap(int ResX, int ResY, int TilesX, int TilesY) {

	horizontalRes = ResX, verticalRes = ResY;
	horizontalTiles = TilesX, verticalTiles = TilesY;

	//Initializa and generate an array for the map
	map = new int*[verticalTiles];
	for (int i = 0; i < verticalTiles; ++i) {
		map[i] = new int[horizontalTiles];
	}

	//Initialize and generate an array for all Vertex, VertexCircleShapes and RectangleShape
	vertexPos = new sf::Vector2f*[verticalTiles + 1];
	vertex = new sf::CircleShape*[verticalTiles + 1];
	edgesH = new sf::RectangleShape*[verticalTiles + 1];
	edgesV = new sf::RectangleShape*[verticalTiles + 1];
	for (int i = 0; i < verticalTiles + 1; i++) {
		vertexPos[i] = new sf::Vector2f[horizontalTiles + 1];
		vertex[i] = new sf::CircleShape[horizontalTiles + 1];
		edgesH[i] = new sf::RectangleShape[horizontalTiles + 1];
		edgesV[i] = new sf::RectangleShape[horizontalTiles + 1];
	}

	this->calculateDimensions();
}

void DrawMap::calculateDimensions(){
	//Calculate number of vertex and edges
	vertexNum = (verticalTiles + 1) * (horizontalTiles + 1);
	edgesNum = ((verticalTiles + 1) * horizontalTiles) + ((horizontalTiles + 1) * verticalTiles);

	//Calculate boundaries of grid tiles and knockout area
	vertexGapX = (int)round((horizontalRes * (1 - (boundLefEdge + boundRigEdge))) / horizontalTiles);
	knockoutGapX = (int)round(horizontalRes * knockoutEdge);
	vertexGapY = (int)round((verticalRes * (1 - (boundTopEdge + boundBotEdge)) / verticalTiles));
	knockoutGapY = (int)round(verticalRes * knockoutEdge);
	//For avoiding surpass boundaries
	vertexGap = std::min(vertexGapX, vertexGapY);
	knockoutGap = std::min(knockoutGapX, knockoutGapY);

	//Adjust boundaries percentiles
	boundLefEdge = (float)round((horizontalRes - (vertexGap * horizontalTiles)) / 2);
	boundLefEdge = boundLefEdge / horizontalRes;
	boundRigEdge = boundLefEdge;
	boundTopEdge = (float)round((verticalRes - (vertexGap * verticalTiles)) / 2);
	boundTopEdge = boundTopEdge /verticalRes;
	boundBotEdge = boundTopEdge;

	//Starting on the top left
	gridOrigin = sf::Vector2f(horizontalRes * boundLefEdge, verticalRes * boundTopEdge);
	knockoutOrigin = sf::Vector2f(horizontalRes * knockoutEdge, verticalRes * knockoutEdge);

	//Calculate and assign values to all the vertex coordinates
	float x = gridOrigin.x, y = gridOrigin.y;
	for (int i = 0; i < verticalTiles + 1; i++) {
		for (int j = 0; j < horizontalTiles + 1; j++) {
			vertexPos[i][j] = sf::Vector2f(x, y);
			x += vertexGap;
		}
		y += vertexGap;
		x = gridOrigin.x;
	}

	this->generateDrawables();
}

void DrawMap::generateDrawables() {
	//Generates each one of the vertex to draw
	for (int i = 0; i < verticalTiles + 1; i++) {
		for (int j = 0; j < horizontalTiles + 1; j++) {
			vertex[i][j] = sf::CircleShape(4, 4);
			vertex[i][j].setOrigin(vertex[i][j].getRadius(), vertex[i][j].getRadius());
			vertex[i][j].setPosition(vertexPos[i][j]);
			vertex[i][j].setFillColor(sf::Color(gridColR, gridColG, gridColB, 255));
		}
	}

	//Generates each one of the edges to draw
	for (int i = 0; i < verticalTiles + 1; i++) {
		for (int j = 0; j < horizontalTiles + 1; j++) {
			if (j < horizontalTiles) {
				edgesH[i][j] = sf::RectangleShape((sf::Vector2f((float)round(vertexGap), 1)));
				edgesH[i][j].setOrigin(0, edgesH[i][j].getSize().y / 2);
				edgesH[i][j].setFillColor(sf::Color(gridColR, gridColG, gridColB, 255));
				edgesH[i][j].setPosition(vertexPos[i][j]);
			}
			if (i < verticalTiles) {
				edgesV[i][j] = sf::RectangleShape((sf::Vector2f((float)round(vertexGap), 1)));
				edgesH[i][j].setOrigin(0, edgesH[i][j].getSize().y / 2);
				edgesV[i][j].setFillColor(sf::Color(gridColR, gridColG, gridColB, 255));
				edgesV[i][j].setPosition(vertexPos[i][j]);
				edgesV[i][j].rotate(90);
			}
		}
	}
}

void DrawMap::draw(sf::RenderWindow &window){
	for (int i = 0; i < verticalTiles + 1; i++) {
		for (int j = 0; j < horizontalTiles + 1; j++) {
			window.draw(vertex[i][j]);
			window.draw(edgesH[i][j]);
			window.draw(edgesV[i][j]);
		}
	}
}

int** DrawMap::generateMap(int **map){

	return map;
}

int ** DrawMap::getMap(){
	return map;
}

/*
sf::RectangleShape DrawMap::generateTile(){
	sf::RectangleShape square(sf::Vector2f(39, 39));
	square.setOrigin(-1,-1);
	square.setFillColor(sf::Color(0,0,0));
	square.setOutlineThickness(1);
	square.setOutlineColor(sf::Color(250, 150, 100));
	return square;
}
*/
