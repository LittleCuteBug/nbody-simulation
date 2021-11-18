#include "body.h"
#include "body_utility.h"

void Body::Draw() const {
	ofEnableAlphaBlending();
	ofSetColor(244, 107, 66);
	ofDrawSphere(position_.x, position_.y, position_.z, radius_);
}

void Body::UpdatePosition(double time_step) {
	velocity_.x += force_.x / mass_;
	velocity_.y += force_.y / mass_;
	velocity_.z += force_.z / mass_;

	position_.x += (velocity_.x * time_step);
	position_.y += (velocity_.y * time_step);
	position_.z += (velocity_.z * time_step);
}

void Body::ResetForce() {
	force_.x = 0;
	force_.y = 0;
	force_.z = 0;
}

void Body::AddForce(Body* b) {

	double dist = BodyUtility::Distance(this, b);
	double EPS = 3E4;
	double g = (b->mass_ * kG / (dist * dist * dist + EPS * EPS * EPS));
	double F = (g * this->mass_ * b->mass_) / (dist * dist * dist + EPS * EPS * EPS);

	this->force_.x += F * (b->position_.x - this->position_.x) / dist;
	this->force_.y += F * (b->position_.y - this->position_.y) / dist;
	this->force_.z += F * (b->position_.z - this->position_.z) / dist;
}

Body* Body::copy() {
	return new Body(this->position_, this->velocity_, this->mass_, this->radius_);
}