#include "BHTree.h"
#include "body_utility.h"

BHTree::BHTree(Quad* q) {
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
		this->body->AddForce(*b);

		Quad* x0y0z0 = this->quad->X0Y0Z0();
		if (BodyUtility::inQuad(b, x0y0z0)) {
			if (this->x0y0z0 == nullptr) {
				this->x0y0z0 = new BHTree(x0y0z0);
			}
			this->x0y0z0->insert(b);
			return;
		}

		Quad* x0y0z1 = this->quad->X0Y0Z1();
		if (BodyUtility::inQuad(b, x0y0z1)) {
			if (this->x0y0z1 == nullptr) {
				this->x0y0z1 = new BHTree(x0y0z1);
			}
			this->x0y0z1->insert(b);
			return;
		}

		Quad* x0y1z0 = this->quad->X0Y1Z0();
		if (BodyUtility::inQuad(b, x0y1z0)) {
			if (this->x0y1z0 == nullptr) {
				this->x0y1z0 = new BHTree(x0y1z0);
			}
			this->x0y1z0->insert(b);
			return;
		}

		Quad* x0y1z1 = this->quad->X0Y1Z1();
		if (BodyUtility::inQuad(b, x0y1z1)) {
			if (this->x0y1z1 == nullptr) {
				this->x0y1z1 = new BHTree(x0y1z1);
			}
			this->x0y1z1->insert(b);
			return;
		}

		Quad* x1y0z0 = this->quad->X1Y0Z0();
		if (BodyUtility::inQuad(b, x1y0z0)) {
			if (this->x1y0z0 == nullptr) {
				this->x1y0z0 = new BHTree(x1y0z0);
			}
			this->x1y0z0->insert(b);
			return;
		}

		Quad* x1y0z1 = this->quad->X1Y0Z1();
		if (BodyUtility::inQuad(b, x1y0z1)) {
			if (this->x1y0z1 == nullptr) {
				this->x1y0z1 = new BHTree(x1y0z1);
			}
			this->x1y0z1->insert(b);
			return;
		}

		Quad* x1y1z0 = this->quad->X1Y1Z0();
		if (BodyUtility::inQuad(b, x1y1z0)) {
			if (this->x1y1z0 == nullptr) {
				this->x1y1z0 = new BHTree(x1y1z0);
			}
			this->x1y1z0->insert(b);
			return;
		}

		Quad* x1y1z1 = this->quad->X1Y1Z1();
		if (BodyUtility::inQuad(b, x1y1z1)) {
			if (this->x1y1z1 == nullptr) {
				this->x1y1z1 = new BHTree(x1y1z1);
			}
			this->x1y1z1->insert(b);
			return;
		}
	}
	
	//If the node is external and contains another body, create BHTrees
	//where the bodies should go, update the node, and end 
	//(do not do anything recursively)
	else {
		Body* c = this->body;
		Quad* x0y0z0 = this->quad->X0Y0Z0();
		if (BodyUtility::inQuad(c, x0y0z0)) {
			if (this->x0y0z0 == nullptr) {
				this->x0y0z0 = new BHTree(x0y0z0);
			}
			else {
				delete x0y0z0;
			}
			this->x0y0z0->insert(c);
			this->insert(b);
			return;
		}

		Quad* x0y0z1 = this->quad->X0Y0Z1();
		if (BodyUtility::inQuad(c, x0y0z1)) {
			if (this->x0y0z1 == nullptr) {
				this->x0y0z1 = new BHTree(x0y0z1);
			}
			else {
				delete x0y0z1;
			}
			this->x0y0z1->insert(c);
			this->insert(b);
			return;
		}

		Quad* x0y1z0 = this->quad->X0Y1Z0();
		if (BodyUtility::inQuad(c, x0y1z0)) {
			if (this->x0y1z0 == nullptr) {
				this->x0y1z0 = new BHTree(x0y1z0);
			}
			else {
				delete x0y1z0;
			}
			this->x0y1z0->insert(c);
			this->insert(b);
			return;
		}

		Quad* x0y1z1 = this->quad->X0Y1Z1();
		if (BodyUtility::inQuad(c, x0y1z1)) {
			if (this->x0y1z1 == nullptr) {
				this->x0y1z1 = new BHTree(x0y1z1);
			}
			else {
				delete x0y1z1;
			}
			this->x0y1z1->insert(c);
			this->insert(b);
			return;
		}

		Quad* x1y0z0 = this->quad->X1Y0Z0();
		if (BodyUtility::inQuad(c, x1y0z0)) {
			if (this->x1y0z0 == nullptr) {
				this->x1y0z0 = new BHTree(x1y0z0);
			}
			else {
				delete x1y0z0;
			}
			this->x1y0z0->insert(c);
			this->insert(b);
			return;
		}

		Quad* x1y0z1 = this->quad->X1Y0Z1();
		if (BodyUtility::inQuad(c, x1y0z1)) {
			if (this->x1y0z1 == nullptr) {
				this->x1y0z1 = new BHTree(x1y0z1);
			}
			else {
				delete x1y0z1;
			}
			this->x1y0z1->insert(c);
			this->insert(b);
			return;
		}

		Quad* x1y1z0 = this->quad->X1Y1Z0();
		if (BodyUtility::inQuad(c, x1y1z0)) {
			if (this->x1y1z0 == nullptr) {
				this->x1y1z0 = new BHTree(x1y1z0);
			}
			else {
				delete x1y1z0;
			}
			this->x1y1z0->insert(c);
			this->insert(b);
			return;
		}

		Quad* x1y1z1 = this->quad->X1Y1Z1();
		if (BodyUtility::inQuad(c, x1y1z1)) {
			if (this->x1y1z1 == nullptr) {
				this->x1y1z1 = new BHTree(x1y1z1);
			}
			else {
				delete x1y1z1;
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
		if (this->body != b) {
			b->AddForce(*this->body);
		}
	}
	else if (this->quad->getLength() / BodyUtility::Distance(*this->body, *b) < 2) {
		b->AddForce(*this->body);
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

void BHTree::clearTree() {
	if (this->x0y0z0 != nullptr) this->x0y0z0->clearTree();
	if (this->x0y0z1 != nullptr) this->x0y0z1->clearTree();
	if (this->x0y1z0 != nullptr) this->x0y1z0->clearTree();
	if (this->x0y1z1 != nullptr) this->x0y1z1->clearTree();

	if (this->x1y0z0 != nullptr) this->x1y0z0->clearTree();
	if (this->x1y0z1 != nullptr) this->x1y0z1->clearTree();
	if (this->x1y1z0 != nullptr) this->x1y1z0->clearTree();
	if (this->x1y1z1 != nullptr) this->x1y1z1->clearTree();

	if(this->body != nullptr)
		delete this->body;
	if (this->quad != nullptr)
		delete this->quad;
	delete this;
}
