#include "craby.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "SDL/SDL_rotozoom.h"
#include <cmath>

int getRandomFactor()
{
 int number = Gamedata::getInstance().getRandInRange(50,1000);
 return number;
}


void Craby::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
         
   if (timeSinceLastFrame > frameInterval) {
     currentFrame = (currentFrame+1) % (numberOfFrames); 
		timeSinceLastFrame = 0;  
  }
}

Craby::Craby( const std::string& name, float scale, int l, Player * p) :
  Drawable(name.substr(0,l), 
           Vector2f(Gamedata::getInstance().getXmlInt(name.substr(0,l)+"/startLoc/x")+Gamedata::getInstance().getRandInRange(1, 2000), 
                    Gamedata::getInstance().getXmlInt(name.substr(0,l)+"/startLoc/y")+Gamedata::getInstance().getRandInRange(1, 800)), 
           Vector2f(Gamedata::getInstance().getXmlInt(name.substr(0,l)+"/speedX")*scale*Gamedata::getInstance().getRandInRange(1,12),
                    Gamedata::getInstance().getXmlInt(name.substr(0,l)+"/speedY")*scale*Gamedata::getInstance().getRandInRange(1,10))
           ),
  frames( FrameFactory::getInstance().getZoomedFrames(name, scale, l)),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name.substr(0,l)+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name.substr(0,l)+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()*scale),
  frameHeight(frames[0]->getHeight()*scale), 
  state(true),
  target(p)
 { }

Craby::Craby(const Craby& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ), 
  state(s.state),
  target(s.target)
  { }



void Craby::draw() const { 
  //double zoom = 1.0;
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void Craby::update(Uint32 ticks) { 
  advanceFrame(ticks);
  float x=(target->X()-X());
  float y=(target->Y()-Y());
  float length = sqrt(x*x+y*y);
  
  velocityX(target->getSpeed()*0.01*Gamedata::getInstance().getRandInRange(1, 10)*(x/length));
  
  velocityY(target->getSpeed()*0.01*Gamedata::getInstance().getRandInRange(1, 4)*(y/length));
  
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
