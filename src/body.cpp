#include "body.h"
void Body::Draw() const {
	ofEnableAlphaBlending();
	ofSetColor(244, 107, 66);
	ofDrawSphere(position_.x, position_.y, position_.z, radius_);
}

void Body::UpdatePosition(double time_step) {
	velocity_.x += force_.x * time_step;
	velocity_.y += force_.y * time_step;
	velocity_.z += force_.z * time_step;

	position_.x += (velocity_.x * time_step);
	position_.y += (velocity_.y * time_step);
	position_.z += (velocity_.z * time_step);
}

void Body::ResetForce() {
	force_.x = 0;
	force_.y = 0;
	force_.z = 0;
}

void Body::AddForce(Body* body) {

	double dx = body->position_.x - position_.x;
	double dy = body->position_.y - position_.y;
	double dz = body->position_.z - position_.z;
	double EPS = 1E3;
	double dist = max(EPS, sqrt(dx * dx + dy * dy + dz * dz));

	double f = body->mass_ * kG / (dist * dist * dist);

	force_.x += f * dx;
	force_.y += f * dy;
	force_.z += f * dz;
}

Body* Body::copy() {
	return new Body(this->position_, this->velocity_, this->mass_, this->radius_);
}