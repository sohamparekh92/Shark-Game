#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "player.h"
#include "world.h"
#include "viewport.h"
#include "HUD.h"
#include "craby.h"
#include "health.h"
#include "bullet.h"
#include "sound.h"
#include "menu.h"
#include <SDL/SDL_mixer.h>
class Manager {
public:
  Manager ();
  ~Manager ();
  bool checkReset() { return reset; }
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;
  SDL_Surface * const screen;
  World world3;
  World world2;
  World world1;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;
  Player * b;
  std::vector<Bullet *> bullets;
  int count;
  HUD * h;
  bool toggleHUD;
  std::vector<Craby*> crabs;
  Health bar;
  bool reset;
  int currentCrab;
  SDLSound sound;
  std::vector<Drawable *> exp;
  bool God;
  int wave;
  Mix_Chunk* pop; 

  bool checkForCollision(Drawable *) ;
  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};

