#include "stdafx.h"
#include "AudioComponent.h"

AudioComponent::AudioComponent(string path, bool loop, bool startOnPlay, float vol)
{
	engine = irrklang::createIrrKlangDevice();
	this->path = path;
	this->loop = loop;
	if (!engine) return;
	if (startOnPlay)
		music = engine->play2D(path.c_str(), loop, false, true);
	music->setVolume(vol);
}

void AudioComponent::start()
{
	music = engine->play2D(path.c_str(), loop, false, true);
}

void AudioComponent::stop()
{
	music->stop();
}
