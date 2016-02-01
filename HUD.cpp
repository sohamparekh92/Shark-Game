#include<iostream>
#include "drawable.h"
#include "ioManager.h"
#include "aaline.h"
#include "HUD.h"


HUD::HUD(): HUD_WIDTH(290), HUD_HEIGHT(240), time(Clock::getInstance().getSeconds()) {}
HUD::HUD(const HUD& h): HUD_WIDTH(h.HUD_WIDTH), HUD_HEIGHT(h.HUD_HEIGHT), time(h.time) {}


void HUD::drawHUD( int x, int y, SDL_Surface * screen, bool t) {
  if(!t) return;
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, 
                     x+HUD_WIDTH,y+HUD_HEIGHT/2, 
                    HUD_HEIGHT, 0x31, 0xf1, 0xff, 0xff/5);
 IOManager::getInstance().printMessageValueAt("fps: ", Clock::getInstance().getFps(), 60, 50);
 IOManager::getInstance().printMessageValueAt("time: ", Clock::getInstance().getSeconds(), 60, 70);
 IOManager::getInstance().printMessageAt("use A S D W to move", 60, 100);
 IOManager::getInstance().printMessageAt("LEFT DOWN", 60, 120);
 IOManager::getInstance().printMessageAt("RIGHT UP", 60, 140);
 IOManager::getInstance().printMessageAt("Press 'P' to pause", 60, 170);
 IOManager::getInstance().printMessageAt("Press 'ESC' to Quit", 60, 200);
 IOManager::getInstance().printMessageAt("Press 'E' to switch Speed", 60, 230);
}




