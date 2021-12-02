#include "BHTree.h"

BHTree::BHTree(Quad q) {
	level = 0;
	this->quad = q;
	this->body = nullptr;
	this->x0y0z0 = nullptr;
	this->x0y0z1 = nullptr;
	this->x0y1z0 = nullptr;
	this->x0y1z1 = nullptr;
	this->x1y0z0 = nullptr;
	this->x1y0z1 = nullptr;
	this->x1y1z0 = nullptr;
	this->x1y1z1 = nullptr;
}

bool BHTree::isExternal() {
	return (this->x0y0z0 == nullptr)
		&& (this->x0y0z1 == nullptr)
		&& (this->x0y1z0 == nullptr)
		&& (this->x0y1z1 == nullptr)
		&& (this->x1y0z0 == nullptr)
		&& (this->x1y0z1 == nullptr)
		&& (this->x1y1z0 == nullptr)
		&& (this->x1y1z1 == nullptr);
}


void BHTree::insert(Body* b) {
	//If there's not a body there already, put the body there.
	if (this->body == nullptr) {
		this->body = b;
		return;
	}
	//If there's already a body there, but it's not an external node
	//combine the two bodies and figure out which quadrant of the 
	//tree it should be located in. Then recursively update the nodes below it.
	if(!this->isExternal())
	{
		this->body->Add(b);

		Quad x0y0z0 = quad.X0Y0Z0();
		if (x0y0z0.contains(b->position_)) {
			if (this->x0y0z0 == nullptr) {
				this->x0y0z0 = new BHTree(x0y0z0);
				this->x0y0z0->level = level + 1;
			}
			this->x0y0z0->insert(b);
			return;
		}

		Quad x0y0z1 = quad.X0Y0Z1();
		if (x0y0z1.contains(b->position_)) {
			if (this->x0y0z1 == nullptr) {
				this->x0y0z1 = new BHTree(x0y0z1);
				this->x0y0z1->level = level + 1;
			}
			this->x0y0z1->insert(b);
			return;
		}

		Quad x0y1z0 = quad.X0Y1Z0();
		if (x0y1z0.contains(b->position_)) {
			if (this->x0y1z0 == nullptr) {
				this->x0y1z0 = new BHTree(x0y1z0);
				this->x0y1z0->level = level + 1;
			}
			this->x0y1z0->insert(b);
			return;
		}

		Quad x0y1z1 = quad.X0Y1Z1();
		if (x0y1z1.contains(b->position_)) {
			if (this->x0y1z1 == nullptr) {
				this->x0y1z1 = new BHTree(x0y1z1);
				this->x0y1z1->level = level + 1;
			}
			this->x0y1z1->insert(b);
			return;
		}

		Quad x1y0z0 = quad.X1Y0Z0();
		if (x1y0z0.contains(b->position_)) {
			if (this->x1y0z0 == nullptr) {
				this->x1y0z0 = new BHTree(x1y0z0);
				this->x1y0z0->level = level + 1;
			}
			this->x1y0z0->insert(b);
			return;
		}

		Quad x1y0z1 = quad.X1Y0Z1();
		if (x1y0z1.contains(b->position_)) {
			if (this->x1y0z1 == nullptr) {
				this->x1y0z1 = new BHTree(x1y0z1);
				this->x1y0z1->level = level + 1;
			}
			this->x1y0z1->insert(b);
			return;
		}

		Quad x1y1z0 = quad.X1Y1Z0();
		if (x1y1z0.contains(b->position_)) {
			if (this->x1y1z0 == nullptr) {
				this->x1y1z0 = new BHTree(x1y1z0);
				this->x1y1z0->level = level + 1;
			}
			this->x1y1z0->insert(b);
			return;
		}

		Quad x1y1z1 = quad.X1Y1Z1();
		if (x1y1z1.contains(b->position_)) {
			if (this->x1y1z1 == nullptr) {
				this->x1y1z1 = new BHTree(x1y1z1);
				this->x1y1z1->level = level + 1;
			}
			this->x1y1z1->insert(b);
			return;
		}
	}
	
	//If the node is external and contains another body, create BHTrees
	//where the bodies should go, update the node, and end 
	//(do not do anything recursively)
	else {
		if (Body::samePosition(body, b) || level == 50) {
			b->Add(body);
			delete body;
			body = b;
			return;
		}
		Body* c = body->copy();
		body->Add(b);
		
		Quad x0y0z0 = quad.X0Y0Z0();
		if (x0y0z0.contains(c->position_)) {
			if (this->x0y0z0 == nullptr) {
				this->x0y0z0 = new BHTree(x0y0z0);
				this->x0y0z0->level = level + 1;
			}
			this->x0y0z0->insert(c);
			this->insert(b);
			return;
		}

		Quad x0y0z1 = quad.X0Y0Z1();
		if (x0y0z1.contains(c->position_)) {
			if (this->x0y0z1 == nullptr) {
				this->x0y0z1 = new BHTree(x0y0z1);
				this->x0y0z1->level = level + 1;
			}
			this->x0y0z1->insert(c);
			this->insert(b);
			return;
		}

		Quad x0y1z0 = quad.X0Y1Z0();
		if (x0y1z0.contains(c->position_)) {
			if (this->x0y1z0 == nullptr) {
				this->x0y1z0 = new BHTree(x0y1z0);
				this->x0y1z0->level = level + 1;
			}
			this->x0y1z0->insert(c);
			this->insert(b);
			return;
		}

		Quad x0y1z1 = quad.X0Y1Z1();
		if (x0y1z1.contains(c->position_)) {
			if (this->x0y1z1 == nullptr) {
				this->x0y1z1 = new BHTree(x0y1z1);
				this->x0y1z1->level = level + 1;
			}
			this->x0y1z1->insert(c);
			this->insert(b);
			return;
		}

		Quad x1y0z0 = quad.X1Y0Z0();
		if (x1y0z0.contains(c->position_)) {
			if (this->x1y0z0 == nullptr) {
				this->x1y0z0 = new BHTree(x1y0z0);
				this->x1y0z0->level = level + 1;
			}
			this->x1y0z0->insert(c);
			this->insert(b);
			return;
		}

		Quad x1y0z1 = quad.X1Y0Z1();
		if (x1y0z1.contains(c->position_)) {
			if (this->x1y0z1 == nullptr) {
				this->x1y0z1 = new BHTree(x1y0z1);
				this->x1y0z1->level = level + 1;
			}
			this->x1y0z1->insert(c);
			this->insert(b);
			return;
		}

		Quad x1y1z0 = quad.X1Y1Z0();
		if (x1y1z0.contains(c->position_)) {
			if (this->x1y1z0 == nullptr) {
				this->x1y1z0 = new BHTree(x1y1z0);
				this->x1y1z0->level = level + 1;
			}
			this->x1y1z0->insert(c);
			this->insert(b);
			return;
		}

		Quad x1y1z1 = quad.X1Y1Z1();
		if (x1y1z1.contains(c->position_)) {
			if (this->x1y1z1 == nullptr) {
				this->x1y1z1 = new BHTree(x1y1z1);
				this->x1y1z1->level = level + 1;
			}
			this->x1y1z1->insert(c);
			this->insert(b);
			return;
		}
	}
}

//Start at the main node of the tree. Then, recursively go each branch
//Until either we reach an external node or we reach a node that is sufficiently
//far away that the external nodes would not matter much.
void BHTree::updateForce(Body* b) {
	if (this->isExternal()) {
		b->AddForce(this->body);
	}
	else if (quad.getLength() / Body::distance(this->body, b) < 2) {
		b->AddForce(this->body);
	}
	else {
		if (this->x0y0z0 != nullptr) this->x0y0z0->updateForce(b);
		if (this->x0y0z1 != nullptr) this->x0y0z1->updateForce(b);
		if (this->x0y1z0 != nullptr) this->x0y1z0->updateForce(b);
		if (this->x0y1z1 != nullptr) this->x0y1z1->updateForce(b);

		if (this->x1y0z0 != nullptr) this->x1y0z0->updateForce(b);
		if (this->x1y0z1 != nullptr) this->x1y0z1->updateForce(b);
		if (this->x1y1z0 != nullptr) this->x1y1z0->updateForce(b);
		if (this->x1y1z1 != nullptr) this->x1y1z1->updateForce(b);
	}
}

BHTree::~BHTree() {
	if (this->x0y0z0 != nullptr) delete this->x0y0z0;
	if (this->x0y0z1 != nullptr) delete this->x0y0z1;
	if (this->x0y1z0 != nullptr) delete this->x0y1z0;
	if (this->x0y1z1 != nullptr) delete this->x0y1z1;

	if (this->x1y0z0 != nullptr) delete this->x1y0z0;
	if (this->x1y0z1 != nullptr) delete this->x1y0z1;
	if (this->x1y1z0 != nullptr) delete this->x1y1z0;
	if (this->x1y1z1 != nullptr) delete this->x1y1z1;

	if(this->body != nullptr)
		delete this->body;
}
