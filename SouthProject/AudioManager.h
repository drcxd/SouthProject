#ifndef __AudioManager__
#define __AudioManager__

#include <map>
#include <string>
#include <iostream>

#include <SDL_mixer.h>

class AudioManager
{
public:

	static AudioManager *Instance()
	{
		if (s_pInstance == 0)
			s_pInstance = new AudioManager();
		return s_pInstance;
	}

	bool load(const std::string fileName, const std::string id);
	void clear(const std::string id);
	void play(const std::string id);
	void stop() const;

private:

	AudioManager() {}
	~AudioManager();

	static AudioManager *s_pInstance;

	std::map<std::string, Mix_Music *> m_musicMap;

};

typedef AudioManager TheAudioManager;
#endif

