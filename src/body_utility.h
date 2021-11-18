#ifndef body_utility_h
#define body_utility_h

#include "body.h"
#include "ofMain.h"
#include "Quad.h"

#include <math.h>
#include <stdio.h>

/*
  Class for a body interaction functions in the simulation. This includes
  distance, velocity interaction, conservation of momentum, collision handling,
  and collision detection.
*/
class BodyUtility {
 public:
  /*
    Will return the magnitude of the distance between the two given bodies (a)
    and (b) in the 3D space.
   */
  static double Distance(Body* a, Body* b);

  static bool inQuad(Body* body, Quad* quad);

};

#endif /* body_utility_hpp */
