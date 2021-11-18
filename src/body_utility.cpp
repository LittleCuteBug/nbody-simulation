#include "body_utility.h"

double BodyUtility::Distance(Body* a, Body* b) {
    double sum = ((a->position_.x - b->position_.x) * (a->position_.x - b->position_.x)) +
        ((a->position_.y - b->position_.y) * (a->position_.y - b->position_.y)) +
        ((a->position_.z - b->position_.z) * (a->position_.z - b->position_.z));
  return sqrt(max(sum, 0.0));
}

bool BodyUtility::inQuad(Body* body, Quad* quad) {
    return quad->contains(body->position_);
}
