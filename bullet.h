#ifndef BULLET__H
#define BULLET__H
#include <string>
#include "drawable.h"
#include "collisionStrategy.h"
class Bullet : public Drawable {
public:
  Bullet(const std::string&);
  Bullet(const std::string&, const Vector2f& pos, const Vector2f& vel);
  Bullet(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  Bullet(const Bullet& s);
  virtual ~Bullet() { delete strategy; } 
  Bullet& operator=(const Bullet&);
  bool hasExploded() const { return explode; }
  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void setLoc(float , float , float, bool);
  virtual void update(Uint32 ticks);
  
  bool collidedWith(const Drawable* d) const {
    return strategy->execute(*this, *d);
  }

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Bullet*) const;
  CollisionStrategy * strategy;
  bool explode;
};
#endif
