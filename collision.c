#include "collision.h"

int Collision_PointInAABB(int px, int py, int aabbx, int aabby, int aabbw, int aabbh) {
  return
    px >= aabbx &&
    px <= aabbx + aabbw &
    py >= aabby &&
    py <= aabby + aabbh;  
}