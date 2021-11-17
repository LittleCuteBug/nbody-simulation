#include "Quad.h"

Quad::Quad(double xmid, double ymid, double zmid, double length) {
	this->xmid = xmid;
	this->ymid = ymid;
	this->zmid = zmid;
	this->length = length;
}

double Quad::getLength() {
	return length;
}

bool Quad::contains(Vector position_) {
	if (position_.x > this->xmid + this->length / 2.0 || position_.x < this->xmid - this->length / 2.0)
		return false;
	if (position_.y > this->ymid + this->length / 2.0 || position_.y < this->ymid - this->length / 2.0)
		return false;
	if (position_.z > this->zmid + this->length / 2.0 || position_.z < this->zmid - this->length / 2.0)
		return false;
	return true;
}

Quad* Quad::X0Y0Z0() {
	return new Quad(
		this->xmid - this->length / 4.0,
		this->ymid - this->length / 4.0,
		this->zmid - this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X0Y0Z1() {
	return new Quad(
		this->xmid - this->length / 4.0,
		this->ymid - this->length / 4.0,
		this->zmid + this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X0Y1Z0() {
	return new Quad(
		this->xmid - this->length / 4.0,
		this->ymid + this->length / 4.0,
		this->zmid - this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X0Y1Z1() {
	return new Quad(
		this->xmid - this->length / 4.0,
		this->ymid + this->length / 4.0,
		this->zmid + this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X1Y0Z0() {
	return new Quad(
		this->xmid + this->length / 4.0,
		this->ymid - this->length / 4.0,
		this->zmid - this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X1Y0Z1() {
	return new Quad(
		this->xmid + this->length / 4.0,
		this->ymid - this->length / 4.0,
		this->zmid + this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X1Y1Z0() {
	return new Quad(
		this->xmid + this->length / 4.0,
		this->ymid + this->length / 4.0,
		this->zmid - this->length / 4.0,
		this->length / 2.0
	);
}

Quad* Quad::X1Y1Z1() {
	return new Quad(
		this->xmid + this->length / 4.0,
		this->ymid + this->length / 4.0,
		this->zmid + this->length / 4.0,
		this->length / 2.0
	);
}