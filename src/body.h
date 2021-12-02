#ifndef body_h
#define body_h

#include "constants.h"
#include "ofMain.h"
#include "Quad.h"

#include <math.h>
#include <stdio.h>

/*
  Class for a body in the simulation that tracks the position, velocity, mass,
  and radius. Also carries the relevant functions for drawing the body in the
  simulation, as well as updating the body.
*/
class Body {
 public:
  Vector position_;
  Vector velocity_;
  Vector force_;
  double mass_;
  double radius_;

  Body(Vector p, Vector v, double m, double r) {
    position_ = p;
    velocity_ = v;
    mass_ = m;
    radius_ = r;
    force_ = Vector(0, 0, 0);
  }

  /* Will draw the body in the OpenFrameworks application. */
  void Draw() const;

  /*
    Update the position of the body by modeling the body movement with the
    given time step.
   */
  void UpdatePosition(double time_step);

  // set the force to 0 for the next iteration
  void ResetForce();

  // compute the net force acting between the body a and b, and
  // add to the net force acting on a
  void AddForce(Body *b);

  Body* copy();

  static double distance(Body *a, Body *b) {
      return (
          sqrt(
              (a->position_.x - b->position_.x) * (a->position_.x - b->position_.x) +
              (a->position_.y - b->position_.y) * (a->position_.y - b->position_.y) +
              (a->position_.z - b->position_.z) * (a->position_.z - b->position_.z)
          ));
  }
  void Add(Body* b) {
      position_ = (position_ * mass_ + b->position_ * b->mass_) / (mass_ + b->mass_);
      velocity_ = (velocity_ * mass_ + b->velocity_ * b->mass_) / (mass_ + b->mass_);
      mass_ += b->mass_;
      radius_ += b->radius_;
  }
  static Body* mergeBody(Body* a, Body* b) {
      return new Body(
          (a->position_ * a->mass_ + b->position_ * b->mass_) / (a->mass_ + b->mass_),
          (a->velocity_ * a->mass_ + b->velocity_ * b->mass_) / (a->mass_ + b->mass_),
          a->mass_ + b->mass_,
          a->radius_ + b->radius_);
  }

  static bool samePosition(Body *a, Body *b) {
      return distance(a, b) < 20;
  }
};

#endif /* body_h */
