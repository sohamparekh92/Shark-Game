#include<iostream>
#include "drawable.h"
#include "ioManager.h"
#include "aaline.h"
#include "clock.h"
class HUD
{
public:
HUD();
HUD(const HUD&);
~HUD() {}
void setTime() { time = Clock::getInstance().getSeconds(); }
unsigned int getTime() { return time; }
void drawHUD( int x, int y, SDL_Surface * screen, bool);
private:
const int HUD_WIDTH; 
const int HUD_HEIGHT;
unsigned int time;
HUD& operator=(const HUD&);
};


