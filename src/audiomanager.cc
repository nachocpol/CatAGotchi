#include "audiomanager.h"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

AudioManager * AudioManager::GetInstance()
{
	static AudioManager sAudioManagerInst;
	return &sAudioManagerInst;
}

void AudioManager::Update(float dt)
{
	auto curStatus = mBackgroundTracks[mCurMusic]->getStatus();
	if (curStatus == sf::SoundSource::Status::Stopped)
	{
		mCurMusic++;
		if (mCurMusic > mBackgroundTracks.size() - 1)
		{
			mCurMusic = 0;
		}
		PlayMusic();
	}
}

void AudioManager::AddTrack(const char * path)
{
	std::shared_ptr<sf::Music> track = std::shared_ptr<sf::Music>(new sf::Music());
	track->setLoop(false);
	if (!track->openFromFile(path))
	{
		printf("ERROR: Could not add track.\n");
		return;
	}
	mBackgroundTracks.push_back(std::move(track));
}

void AudioManager::PlayMusic()
{
	mBackgroundTracks[mCurMusic]->play();
}

void AudioManager::SetVolume(float v)
{
	v = std::min(100.0f, v);
	v = std::max(0.0f, v);
	for each(auto ele in mBackgroundTracks)
	{
		ele->setVolume(v);
	}
}
