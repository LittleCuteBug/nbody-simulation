#include "body_utility.h"

double BodyUtility::Distance(Body a, Body b) {
  return sqrt(
      ((a.position_.x - b.position_.x) * (a.position_.x - b.position_.x)) +
      ((a.position_.y - b.position_.y) * (a.position_.y - b.position_.y)) +
      ((a.position_.z - b.position_.z) * (a.position_.z - b.position_.z)));
}

bool BodyUtility::inQuad(Body* body, Quad* quad) {
    return quad->contains(body->position_);
}
