#pragma once

#include<al.h>

struct SoundBuffer {
	ALuint m_BufferHndl;
	SoundBuffer(const char* a_Path);
	~SoundBuffer();
};

struct SoundSource {
	SoundBuffer m_Buffer;
	ALuint m_SourceHndl;
	SoundSource(const char* a_Path);
	~SoundSource();
};

class Sound {
private:
	SoundSource m_Source;

public:
	Sound(const char* a_Path);

	void play();
	bool isPlaying();
};