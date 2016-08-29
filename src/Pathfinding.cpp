#include "Pathfinding.hh"

#include "Map.hh"
#include <vector>
#include <cstdio>


int ABS(int i) {
	if (i < 0) return i * -1;
	else return i;
}

int dist(int x1, int y1, int x2, int y2) {
	return ABS(x1 - x2) + ABS(y1 - y2);
}


std::vector<Node> Pathfinding::findPath(Map map, int fromX, int fromY, int toX, int toY) {
	// make all the nodes
	Node Nodes[map.sizeX][map.sizeY];
	
	for (int x = 0; x < map.sizeX; x++) {
		for (int y = 0; y < map.sizeY; y++) {
			Nodes[x][y].x = x - map.sizeX / 2;
			Nodes[x][y].y = y - map.sizeY / 2;
		}
	}
	
	std::vector<Node*> open;
	//std::vector<Node*> closed;
	
	//Node *currentNode = Nodes[fromX + map.sizeX / 2][fromY + map.sizeY / 2];
	int currentX = fromX + map.sizeX / 2;
	int currentY = fromY + map.sizeY / 2;
	Nodes[currentX][currentY].isClosed = true;
	
	
	while (Nodes[currentX][currentY].x != toX || Nodes[currentX][currentY].y != toY) {
		//printf("\nNew loop. Node xy:%i %i current xy: %i %i\n", Nodes[currentX][currentY].x, Nodes[currentX][currentY].y, currentX, currentY);
		// add to open list // if checks for: out of bounds, if isnt closed/open, if doesn't collide
		if (currentX < map.sizeX && !Nodes[currentX + 1][currentY].isClosed && true) { // TODO change true to collision detection
			open.push_back(&Nodes[currentX + 1][currentY]);
			Nodes[currentX + 1][currentY].parent = &Nodes[currentX][currentY];
			Nodes[currentX + 1][currentY].isClosed = true;
			printf("\nNew loop. Node xy:%i %i current xy: %i %i\n", Nodes[currentX][currentY].x, Nodes[currentX][currentY].y, currentX, currentY);
			printf("hai1: Node real xy:%i %i\n", Nodes[currentX + 1][currentY].x, Nodes[currentX + 1][currentY].y);
		}
		if (currentX > 0 && !Nodes[currentX - 1][currentY].isClosed && true) {
			open.push_back(&Nodes[currentX - 1][currentY]);
			Nodes[currentX - 1][currentY].parent = &Nodes[currentX][currentY];
			Nodes[currentX - 1][currentY].isClosed = true;
			printf("hai2: Node real xy:%i %i\n", Nodes[currentX - 1][currentY].x, Nodes[currentX - 1][currentY].y);
		}
		if (currentY < map.sizeY && !Nodes[currentX][currentY + 1].isClosed && true) {
			open.push_back(&Nodes[currentX][currentY + 1]);
			Nodes[currentX][currentY + 1].parent = &Nodes[currentX][currentY];
			Nodes[currentX][currentY + 1].isClosed = true;
			printf("hai3\n");
		}
		if (currentY > 0 && !Nodes[currentX][currentY - 1].isClosed && true) {
			open.push_back(&Nodes[currentX][currentY - 1]);
			Nodes[currentX][currentY - 1].parent = &Nodes[currentX][currentY];
			Nodes[currentX][currentY - 1].isClosed = true;
			printf("hai4\n");
		}
		
		// close, take from open list
		for (int i = 0; i < open.size(); i++) {
			if (open[i]->x == Nodes[currentX][currentY].x && open[i]->y == Nodes[currentX][currentY].y) {
				//open.erase(open.begin() + i); // 0 is terribe idea
				open.erase(open.begin() + 0);
				printf("hi from eraser\n");
			}
		}
		currentX = open[0]->x - map.sizeX / 2;
		currentY = open[0]->y - map.sizeY / 2;
		//printf("open[0]: %i %i\n", open[0]->x, open[0]->y);
		//printf("\nNew loop. Node xy:%i %i current xy: %i %i\n", Nodes[currentX][currentY].x, Nodes[currentX][currentY].y, currentX, currentY);
	}
	
	/* path found */ {
		std::vector<Node> path;
		
		Node currentNode = Nodes[currentX][currentY];
		
		while (currentNode.x != fromX || currentNode.y != fromY) {
			path.push_back(currentNode);
			currentNode = *currentNode.parent; // parent is poiner so not that cool
		}
		
		return path;
	}
}
