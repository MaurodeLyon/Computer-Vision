#include "stdafx.h"
#include "Audio.h"


Audio::Audio()
{
	engine = irrklang::createIrrKlangDevice();
	if (!engine)
		return;
}

void Audio::play(string path, bool loop, float vol)
{
	irrklang::ISound* music = engine->play2D(path.c_str(), loop, false, true);
	
	music->setVolume(vol);
}

void Audio::stop()
{
	engine->stopAllSounds();
}