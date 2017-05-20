/*
	audiomanager.h nachocpol@gmail.com
*/

#pragma once

#include <memory>
#include <vector>

#include "SFML/Audio.hpp"

class AudioManager
{
public:
	~AudioManager();
	static AudioManager* GetInstance();
	void Update(float dt);
	void AddTrack(const char* path);
	void PlayMusic();
	void SetVolume(float v);

private:
	AudioManager();
	
	int mCurMusic = 0;
	std::vector<std::shared_ptr<sf::Music>> mBackgroundTracks;
};

