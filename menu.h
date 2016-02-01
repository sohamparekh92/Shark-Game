#ifndef MENU_H
#define MENU_H
#include<iostream>
#include "drawable.h"
#include "ioManager.h"
#include "aaline.h"

class Menu
{
public:
Menu();
Menu(const Menu&);
virtual ~Menu() {}
void drawMenu( int x, int y, SDL_Surface * screen);
void drawDeadMenu( int x, int y, SDL_Surface * screen);
void drawWinMenu( int x, int y, SDL_Surface * screen);
private:
const int Menu_WIDTH; 
const int Menu_HEIGHT;
Menu& operator=(const Menu&);
};
#endif

