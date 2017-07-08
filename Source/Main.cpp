#include "stdafx.h"
#include "Line.h"
#include <windows.h>

const int order = 5;

//Basic node
struct node{
	//default constructor
	node() : bod(sf::CircleShape(10.0f)){ bod.setOrigin(5.0f, 5.0f); };

	//Initialize children during tree population
	node(int x, int y) : bod(sf::CircleShape(10.0f)) { bod.setOutlineColor(sf::Color::White); bod.setOutlineThickness(1.0);  bod.setFillColor(sf::Color::Transparent); bod.setPosition(x, y); };

	//graphical representation of the node
	sf::CircleShape bod;


	node *children[2];
};

//populate the tree
void populateTree(int n, node &parent){
	if (n > 0){
		parent.children[0] = new node(parent.bod.getPosition().x + (pow((3 - ((float)order - n)), 2) / 0.05f), (-50 * n) + (50 * (order + 2)));
		parent.children[1] = new node(parent.bod.getPosition().x - (pow((3 - ((float)order - n)), 2) / 0.05f), (-50 * n) + (50 * (order + 2)));
		
		populateTree(n - 1, *parent.children[0]);
		populateTree(n - 1, *parent.children[1]);	
	}
}

//draw the tree
void drawTree(int n, node &parent, sf::RenderWindow *window){
	if (n > 0){
		window->draw(parent.bod);
		drawTree(n - 1, *parent.children[0], window);
		drawTree(n - 1, *parent.children[1], window);	
	}
}

int _tmain(int argc, _TCHAR* argv[]){

	int width = 800, height = 600;
	sf::RenderWindow window(sf::VideoMode(width, height), "Binary Tree");

	sf::Time timer;
	sf::Clock clock;

	node root;
	root.bod.setPosition(400, 50);
	populateTree(order, root);


	while (window.isOpen()){
		sf::Event evnt;
		while (window.pollEvent(evnt)){
			if (evnt.type == sf::Event::Closed){
				window.close();
			}
		}
		window.clear();

		drawTree(order, root, &window);

		window.display();

		timer += clock.restart();
	}

	return 0;
}