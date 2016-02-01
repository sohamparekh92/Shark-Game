#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "drawable.h"
#include "collisionStrategy.h"

class Player : public Drawable {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual ~Player() { delete strategy; }
  virtual void pushKey(int);
  virtual void setMood();
  virtual void toggleSpeed();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  int getSpeed() const { return sp; }
  bool getState() const { return state; }
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  bool collidedWith(const Drawable* d) const {
    return strategy->execute(*this, *d);
  }

protected:

  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  bool state;
  int pressedKey;
  bool mood;
  int sp;
  bool speed;
  CollisionStrategy * strategy;
  void advanceFrame(Uint32 ticks);
private:
Player& operator=(const Player&);
};
#endif
