#pragma once
#include "irrKlang\irrKlang.h"
class Audio
{
public:
	Audio();
	~Audio() {};
	void play(std::string path, bool loop, float volume);
	void stop();
private:
	irrklang::ISoundEngine *engine;
};

