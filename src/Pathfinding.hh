#ifndef PATHFINDING_H
#define PATHFINDING_H


#include <vector>
#include "Map.hh"


struct Node {
	int x;
	int y;
	Node *parent;
	bool isClosed = false;
};


class Pathfinding {
	
	public:
		static std::vector<Node> findPath(Map map, int fromX, int fromY, int toX, int toY);
	
};

#endif
