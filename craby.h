#ifndef CRABY__H
#define CRABY__H
#include <string>
#include <vector>
#include "drawable.h"
#include "player.h"
class Craby : public Drawable {
public:
  Craby(const std::string&, float, int, Player *);
  Craby(const Craby&);
  virtual ~Craby() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
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
  Player * target;

  void advanceFrame(Uint32 ticks);
private:
Craby& operator=(const Craby&);
};
#endif
