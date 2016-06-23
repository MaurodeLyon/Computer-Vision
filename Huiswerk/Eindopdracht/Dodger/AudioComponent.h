#pragma once

class AudioComponent : public Component
{
public:
	AudioComponent(string path, bool loop, bool startOnCreate, float volume);
	~AudioComponent()
	{
		music->drop();
		delete engine;
		delete music;
	};
	irrklang::ISoundEngine* engine;
private:
	string path;
	bool loop;
	irrklang::ISound* music;
	void start();
	void stop();
};

