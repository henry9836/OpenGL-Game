#pragma once
#include <iostream>
#include <fmod.hpp>

class AudioSystem {
public:

	bool AudioInit();
	void Play(int track);
	void Tick();

	enum Tracks {
		FIREBACK,
		BABYBACK,
		SPEECH
	};

	FMOD::System* audioSystem;
	FMOD::Sound* fireBackTrack;
	FMOD::Sound* babyBackTrack;
	FMOD::Sound* speechTrack;

};