#pragma once
#include "irrKlang\irrKlang.h"
class Audio
{
public:
	Audio();
	~Audio() {};
	void play(std::string, bool, float);
	void stop();
private:
	irrklang::ISoundEngine *engine;
};

