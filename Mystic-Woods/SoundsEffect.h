#ifndef SOUNDS_EFFECT
#define SOUNDS_EFFECT
#include "CommonFunc.h"
#include <map>


class SoundsEffect {
private:
 std::map<std::string,Mix_Chunk* > Chunks;


public:

SoundsEffect();
~SoundsEffect();
void addSound(std::string name,std::string path);
void PlaySound(std::string name);
};



#endif