#define _USE_MATH_DEFINES
#include "Kelvinlet.h"

#include <algorithm>

glm::vec3 Kelvinlet::displacementRK4(glm::vec3 position, Material material, float t) const {
  glm::vec3 p = position;
  for (int i = 0; i < 4; i++) {
    glm::vec3 v0 = displacement(p, material, t);
    glm::vec3 v1 = displacement(p + 0.5 * v0, material, t);
    glm::vec3 v2 = displacement(p + 0.5 * v1, material, t);
    glm::vec3 v3 = displacement(p + v2, material, t);

    p += (v0 + v1 * 2 + v2 * 2 + v3) / 6;
  }
  
  return p - position;
}

float Kelvinlet::approxRadius(float maxInfluence) const {
  // The distance from the center at which the force distribution goes down to maxInfluence
  float det = pow(glm::length(force) * 15 * pow(scale, 4) / (maxInfluence * 8 * M_PI), 2.0/7.0) - scale*scale;
  if (det <= 0) return 0;
  return sqrt(det);
}
