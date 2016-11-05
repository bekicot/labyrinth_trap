#include "door.h"
#include "position.h"

door createDoor(position position, int width, int height, int orientation, int color) {
  door d;
  d.position    = position;
  d.width       = width;
  d.height      = height;
  d.orientation = orientation;
  d.color       = color;
  return d;
}
