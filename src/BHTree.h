#pragma once

#include "body.h"
#include "Quad.h"

class BHTree
{
private:
	Body* body;
	Quad* quad;
	BHTree* x0y0z0;
	BHTree* x0y0z1;
	BHTree* x0y1z0;
	BHTree* x0y1z1;
	BHTree* x1y0z0;
	BHTree* x1y0z1;
	BHTree* x1y1z0;
	BHTree* x1y1z1;

public:
	
	//Create and initialize a new bhtree. Initially, all nodes are null and will be filled by recursion
	//Each BHTree represents a quadrant and a body that represents all bodies inside the quadrant
	BHTree(Quad* q);

	//If all nodes of the BHTree are null, then the quadrant represents a single body and it is "external"
	bool isExternal();

	//We have to populate the tree with bodies. We start at the current tree and recursively travel through the branches
	void insert(Body* b);

	//Start at the main node of the tree. Then, recursively go each branch
	//Until either we reach an external node or we reach a node that is sufficiently
	//far away that the external nodes would not matter much.
	void updateForce(Body* b);

	//Start at the main node of the tree. Then, recursively go each branch
	void clearTree();
};

