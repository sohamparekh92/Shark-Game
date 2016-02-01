#include<iostream>
#include "drawable.h"
#include "ioManager.h"
#include "aaline.h"
#include "menu.h"
#include "gamedata.h"


Menu::Menu(): Menu_WIDTH(Gamedata::getInstance().getXmlInt("view/width")), 
	      Menu_HEIGHT(Gamedata::getInstance().getXmlInt("view/height")) {}
Menu::Menu(const Menu& m): Menu_WIDTH(m.Menu_WIDTH), Menu_HEIGHT(m.Menu_HEIGHT) {}

void Menu::drawMenu( int x, int y, SDL_Surface * screen) {
  Draw_AALine(screen, x, y+Menu_HEIGHT/2, 
                     x+Menu_WIDTH,y+Menu_HEIGHT/2, 
                    Menu_HEIGHT, 0x31, 0x80, 0xff, 0xff/1.4);
 IOManager::getInstance().printMessageCenteredAt("Paused", 160);
 IOManager::getInstance().printMessageCenteredAt("Press 'P' to resume", 180);

}

void Menu::drawDeadMenu( int x, int y, SDL_Surface * screen) {
  Draw_AALine(screen, x, y+Menu_HEIGHT/2, 
                     x+Menu_WIDTH,y+Menu_HEIGHT/2, 
                    Menu_HEIGHT, 0x31, 0x80, 0xff, 0xff/1.4);
 IOManager::getInstance().printMessageCenteredAt("Game Over", 330);
 IOManager::getInstance().printMessageCenteredAt("Press 'R' to reset", 350);
 IOManager::getInstance().printMessageCenteredAt("Press 'ESC' to quit", 370);
}

void Menu::drawWinMenu( int x, int y, SDL_Surface * screen) {
  Draw_AALine(screen, x, y+Menu_HEIGHT/2, 
                     x+Menu_WIDTH,y+Menu_HEIGHT/2, 
                    Menu_HEIGHT, 0x31, 0x80, 0xff, 0xff/1.4);
 IOManager::getInstance().printMessageCenteredAt("You Win!", 330);
 IOManager::getInstance().printMessageCenteredAt("Press 'R' to restart", 350);
 IOManager::getInstance().printMessageCenteredAt("Press 'ESC' to quit", 370);
}


