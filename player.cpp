#include "player.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "ioManager.h"


void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
         
	if (timeSinceLastFrame > frameInterval) {
     if(state == true)
    {
      if(mood==true)
      {
       currentFrame = (currentFrame)%2; 
		timeSinceLastFrame = 0;
      }
      else
      {
       currentFrame = (currentFrame+1)%2; 
		timeSinceLastFrame = 0;
      }
    
    }
   else
    {
       

      if(mood==true)
      {
       currentFrame = (numberOfFrames/2)+ (currentFrame)%2; 
		timeSinceLastFrame = 0;
      }
      else
      {
       currentFrame = (numberOfFrames/2)+ (currentFrame)%2; 
		timeSinceLastFrame = 0;
      }
    }
  }
}

void Player::pushKey(int key)
{
 pressedKey = key;
}

Player::Player( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ), 
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()), 
  state(true),
  pressedKey(0), 
  mood(true),
  sp(Gamedata::getInstance().getXmlInt(name+"/speedS")),
  speed(true),
  
  strategy(new PerPixelCollisionStrategy)
{
  
 }

Player::Player(const Player& s) :
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ), state(s.state),
  pressedKey(s.pressedKey),
  mood(s.mood),
  sp(s.sp),
  speed(s.speed),
  strategy(s.strategy)
  { }

void Player::setMood() //will be implemented in the final phase
{
 mood=!mood;
}

void Player::toggleSpeed()
{
 speed=!speed;
 if(speed) sp=sp*1.5;
 else sp = sp/1.5;
}



void Player::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if(speed) IOManager::getInstance().printMessageAt("Speed: HIGH", 1000, 30);
  else IOManager::getInstance().printMessageAt("Speed: LOW", 1000, 30);
  frames[currentFrame]->draw(x, y);
}

void Player::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Vector2f incr;
  if (pressedKey==1) {
    state = false;
    velocityX(-sp);
    velocityY(0);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
  if (pressedKey==2) {
    velocityX(0);
    velocityY(sp);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
  if (pressedKey==3) {
    state = true;
    velocityX(sp);
    velocityY(0);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
  if (pressedKey==4) {
    velocityX(0);
    velocityY(-sp);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
   if (pressedKey==5) {
    state = true;
    velocityX(sp);
    velocityY(-sp);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    
  }
   if (pressedKey==6) {
    state = true;
    velocityX(sp);
    velocityY(sp);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
   if (pressedKey==7) {
    state = false;
    velocityX(-sp);
    velocityY(sp);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
   if (pressedKey==8) {
    state = false;
   velocityX(-sp);
   velocityY(-sp);
    incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  }
 if (pressedKey==0) {
   velocityX(0.99*velocityX());
   velocityY(0.99*velocityX());
   incr = getVelocity() * static_cast<float>(ticks) * 0.00;
  }
   setPosition(getPosition() + incr);
    
}
