#include "frameFactory.h"
#include "extractSurface.h"
#include "ioManager.h"
#include "vector2f.h"
#include "SDL/SDL_rotozoom.h"
FrameFactory::FrameFactory() : 
  gdata( Gamedata::getInstance() ), 
  surfaces(),
  multiSurfaces(),
  frames(),
  multiFrames()

{}

FrameFactory::~FrameFactory() 
{
  
  std::map<std::string, std::vector<SDL_Surface*> >::iterator s1 = multiSurfaces.begin();
  while (s1!= multiSurfaces.end()) 
  {
    for (unsigned int i=0;i<s1->second.size();i++)
    SDL_FreeSurface(s1->second[i]);
    s1++;
  }
  std::map<std::string, SDL_Surface*>::iterator srfT = surfaces.begin();
  while (srfT!=surfaces.end()) 
  {
    SDL_FreeSurface(srfT->second);
    srfT++;
  }
  std::map<std::string, std::vector<Frame*> >::iterator fx = multiFrames.begin();
  while (fx!=multiFrames.end())
  {
    for (unsigned int i=0;i<fx->second.size();i++) 
     delete fx->second[i];
     fx++;
  }
  std::map<std::string, Frame*>::iterator iterf = frames.begin();
  while (iterf!=frames.end()) 
  {
    delete iterf->second;
    iterf++;
  }
 
}

FrameFactory& FrameFactory::getInstance() {    
  static FrameFactory factory;
  return factory;
}

Frame* FrameFactory::getFrame(const std::string& name) {
  
  std::map<std::string, Frame*>::const_iterator check=frames.find(name); 
  if (check==frames.end()) 
  {
   SDL_Surface * const surface =
    IOManager::getInstance().loadAndSet(
        gdata.getXmlStr(name+"/file"),
        gdata.getXmlBool(name+"/transparency"));
   surfaces[name] = surface;
   Frame * const frame =new Frame(name, surface);
   frames[name] = frame;
   return frame;
  }
  else return check->second;
}


std::vector<Frame*> FrameFactory::getFrames(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Frame*> >::const_iterator 
    pos = multiFrames.find(name); 
  if ( pos != multiFrames.end() ) {
    return pos->second;
  }

  // It wasn't in the map, so we have to make the vector of Frames:
  SDL_Surface* surface = IOManager::
     getInstance().loadAndSet(gdata.getXmlStr(name+"/file"), true);
  unsigned numberOfFrames = gdata.getXmlInt(name+"/frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Surface*> surfaces;
  frames.reserve(numberOfFrames);
  Uint16 srcX = gdata.getXmlInt(name+"/srcX");
  Uint16 srcY = gdata.getXmlInt(name+"/srcY");
  Uint16 width = gdata.getXmlInt(name+"/width");
  Uint16 height = gdata.getXmlInt(name+"/height");

  SDL_Surface* surf;
  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * width + srcX;
   surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, srcY); 
    surfaces.push_back( surf );
    frames.push_back( new Frame(name, surf) );
  }
  SDL_FreeSurface(surface);
  multiSurfaces[name] = surfaces;
  multiFrames[name] = frames;
  return frames;
}

std::vector<Frame*> FrameFactory::getZoomedFrames(const std::string& name, float z, int lth) {
  std::map<std::string, std::vector<Frame*> >::const_iterator 
    pos = multiFrames.find(name); 
  if ( pos != multiFrames.end() ) {
    return pos->second;
  }
  SDL_Surface* surface = IOManager::
     getInstance().loadAndSet(gdata.getXmlStr(name.substr(0,lth)+"/file"), true);
  unsigned numberOfFrames = gdata.getXmlInt(name.substr(0,lth)+"/frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Surface*> surfaces;
  frames.reserve(numberOfFrames);
  Uint16 srcX = gdata.getXmlInt(name.substr(0,lth)+"/srcX");
  Uint16 srcY = gdata.getXmlInt(name.substr(0,lth)+"/srcY");
  Uint16 width = gdata.getXmlInt(name.substr(0,lth)+"/width");
  Uint16 height = gdata.getXmlInt(name.substr(0,lth)+"/height");
  SDL_Surface * surf;
  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * width + srcX;
  surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, srcY);
     SDL_Surface * surf1 = zoomSurface(surf, z, z, SMOOTHING_ON);
    surfaces.push_back(surf1);
    frames.push_back( new Frame(name, lth, surf1 ) );
  SDL_FreeSurface(surf);
  }
  SDL_FreeSurface(surface);
  multiSurfaces[name] = surfaces;
  multiFrames[name] = frames;
  return frames;
}
