
#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"
//#include "clock.h"
#include "menu.h"

class Health {
public:
  Health();
  Health(int sx, int sy, int tl, int cl, 
         float t, int inc, Uint32 c, float sp);
  ~Health() { delete d; }
  void draw() const;
  void update(Uint32);
  void won() { win = true; }
  bool checkIfDead() { return isDead; }
  void reset() { currentLength = totalLength; }
private:
  SDL_Surface* screen;
  Vector2f start;
  int totalLength;
  int currentLength;
  int thick;
  int increments;
  float interval;
  int deltaTime;
  const Uint32 RED;
  const Uint32 GRAY;
  const Uint32 BLACK;
  const Uint32 color;
  bool isDead;
  bool win;
  Menu * d;

  void drawBox() const;
  Health(const Health&);
  Health& operator=(const Health&);
};

