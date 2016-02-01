#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "player.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "explodingSprite.h"


Manager::~Manager() { 
  for (unsigned i = 0; i < sprites.size(); i++)
  delete sprites[i];
  delete h;
  for(unsigned int i=0; i<crabs.size() ; i++)
  delete crabs[i];
  for(unsigned int i=0; i<exp.size() ; i++)
  delete exp[i];
  for(unsigned int i=0; i<bullets.size() ; i++)
  delete bullets[i];
  delete b;
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world3("back3", Gamedata::getInstance().getXmlInt("back3/factor") ),
  world2("back2", Gamedata::getInstance().getXmlInt("back2/factor") ),
  world1("back1", Gamedata::getInstance().getXmlInt("back1/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
   b(new Player("shirky")),
  bullets(),
  count(0),
  h(new HUD()),
  toggleHUD(true),
  crabs(),
  bar(),
  reset(false),
  currentCrab(0),
  sound(),
  exp(),
  God(false),
  wave(0),
  pop(NULL)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit); 
  for(int i=0 ; i<10;i++)
  crabs.push_back( new Craby("craby", 0.9, 5, b) );
  for(int i=0 ; i<10;i++)
  crabs.push_back( new Craby("craby2", 0.5, 5, b) );
  for(int i=0 ; i<10;i++)
  crabs.push_back( new Craby("craby3", 0.3, 5, b) );
  pop = Mix_LoadWAV("sound/bubblepop.wav");
  viewport.setObjectToTrack(b);
}

bool Manager::checkForCollision(Drawable * t) {
  std::vector<Craby*>::const_iterator ptr = crabs.begin();
  int count = 0;
  
  while ( ptr != crabs.end() ) {
    if ( t->collidedWith(*ptr) ) 
    {
     currentCrab = count;
     return true;
    }
    ++ptr;
    ++count;
  }
  return false;
}


void Manager::draw() const {
  world3.draw();
  for (unsigned i = crabs.size()/1.5; i < crabs.size(); ++i) {
    crabs[i]->draw();
  }
  world2.draw();
  world1.draw();
  for (unsigned i = crabs.size()/3; i < crabs.size()/1.5; ++i) {
    crabs[i]->draw();
  }
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  for (unsigned i = 0; i < crabs.size()/3; ++i) {
    crabs[i]->draw();
  }
  for (unsigned i = 0; i < exp.size(); ++i) {
  exp[i]->draw();
  }
  io.printMessageCenteredAt("Soham's Game", 30);
  //io.printMessageAt("Shirky the Shark!", 1100, 700);
  io.printMessageAt("Press 'F1' to toggle HUD", 1000, 10);
  if(God)
  io.printMessageAt("God Mode: ON", 1000, 50);
  else
  io.printMessageAt("God Mode: OFF", 1000, 50);
  if(wave==0)
  io.printMessageAt("First wave!", 1100, 700);
  else if(wave==1)
  io.printMessageAt("Second wave!", 1100, 700);
  else
  io.printMessageAt("Final wave!", 1100, 700);
  for(unsigned int i=0; i<bullets.size(); i++)
  bullets[i]->draw();
  b->draw();
  if(Clock::getInstance().getSeconds()<=(h->getTime()+2))
  h->drawHUD(40, 40, screen, toggleHUD);
  bar.draw();
  clock.draw();
  viewport.draw();
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}


void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();

  for(unsigned int i=0; i<bullets.size(); i++)
   {
    if(checkForCollision(bullets[i]))
    {
     Mix_PlayChannel(-1, pop, 0);
     Sprite* temp = static_cast<Sprite*>(static_cast<Drawable*>(bullets[i]));
     exp.push_back(new ExplodingSprite(*temp));
     delete crabs[currentCrab];
     crabs.erase(crabs.begin()+currentCrab);
     delete bullets[i];
     bullets.erase(bullets.begin()+i);
    }
   }

  for(unsigned int i=0; i<bullets.size(); i++)
   {
     if(bullets[i]->hasExploded())
     {
      Mix_PlayChannel(-1, pop, 0);
      Sprite* temp = static_cast<Sprite*>(static_cast<Drawable*>(bullets[i]));
      exp.push_back(new ExplodingSprite(*temp));
      delete bullets[i];
      bullets.erase(bullets.begin()+i);
     }
   }
  for (unsigned i = 0; i < exp.size(); ++i) {
  exp[i]->update(ticks);
  }
  
  b->update(ticks);
  for(unsigned int i=0; i<bullets.size(); i++)
  bullets[i]->update(ticks);
  if(sprites.size()!=0)
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  for (unsigned int i = 0; i < crabs.size(); ++i) {
    crabs[i]->update(ticks);
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  if(checkForCollision(b)&&!God)
  bar.update(ticks);
  world3.update();
  world2.update();
  world1.update();
  viewport.update(); // always update viewport last
}



void Manager::play() {
  SDL_Event event;
  bool done = false;
  clock.start(); 
  while ( not done ) {
  if(bar.checkIfDead())
   toggleHUD= false;
  if(crabs.begin()==crabs.end()&&wave>=2)
  bar.won(); //draws a winning menu
  if(crabs.begin()==crabs.end()&&wave<2)
  {
   wave++;
   for(int i=0; i<wave*15; ++i)
       {
        crabs.push_back( new Craby("craby", 0.9, 5, b) );
        crabs.push_back( new Craby("craby2", 0.5, 5, b) );
        crabs.push_back( new Craby("craby3", 0.2, 5, b) );
       }
    
   }
  
   int button;
   count=0;
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      
      if((event.type == SDL_KEYDOWN)||(event.type == SDL_PRESSED)) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_SPACE] ) {    
           Bullet *temp = new Bullet("bubble");      
           bullets.push_back(temp);
           temp->setLoc(b->X(), b->Y(),b->getSpeed(), b->getState());
        }
        if ( keystate[SDLK_e] ) {
          b->toggleSpeed();
        }
        if ( keystate[SDLK_g] ) {
          God=!God;
        }
        if ( keystate[SDLK_h] ) {
         
        }
         if ( keystate[SDLK_r] ) {
          reset = true;
          done = true;
          Clock::getInstance().reset();
          break;
        }
        if ( keystate[SDLK_p] ) {
        //also draws a pause menu
          toggleHUD = false;
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_F3]) {
          clock.toggleSloMo();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        if (event.key.keysym.sym == SDLK_a) {
          button = 1;
          
        }
        if (keystate[SDLK_s]) {
          button = 2;
          
        }
        if (keystate[SDLK_d]) {
          button = 3;
        }
        if (keystate[SDLK_w]) {
          button= 4;
        } 
        if (keystate[SDLK_w]&&keystate[SDLK_d]) {
          button= 5;
        }
        if (keystate[SDLK_s]&&keystate[SDLK_d]) {
          button= 6;
        }
        if (keystate[SDLK_a]&&keystate[SDLK_s]) {
          button= 7;
        }
        if (keystate[SDLK_w]&&keystate[SDLK_a]) {
          button= 8;
        }
        if (keystate[SDLK_w]&&keystate[SDLK_s]) {
          button= 0;
        }
        if (keystate[SDLK_a]&&keystate[SDLK_d]) {
          button= 0;
        }
	if (keystate[SDLK_F1]) {
          if(!toggleHUD)
          toggleHUD=!toggleHUD;
          h->setTime();
        }
      }

     else if((event.type == SDL_KEYUP)||(event.type == SDL_PRESSED)) 
     {
       if (keystate[SDLK_a]) {
          button = 1;
        }
      else  if (keystate[SDLK_s]) {
          button = 2;
        }
      else  if (keystate[SDLK_d]) {
          button = 3;
        }
       else if (keystate[SDLK_w]) {
          button= 4;
        } 
       else  {
          button= 0;
        } 
     }
       b->pushKey(button);
    }
    draw();
    update();
   }
}

