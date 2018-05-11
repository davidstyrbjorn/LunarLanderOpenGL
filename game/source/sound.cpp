#include"../include/sound.h"

#include"../include/sound_load.h"

Sound::Sound(const char * a_Path) : m_Source(a_Path)
{
	
}

void Sound::play()
{
	alSourcePlay(m_Source.m_SourceHndl);
}

SoundBuffer::SoundBuffer(const char* a_Path) 
{
	alGenBuffers(1, &m_BufferHndl);
	int size, chan, sample_rate, bps, format;
	void *data = loadWAV(a_Path, chan, sample_rate, bps, size, format);
	alBufferData(m_BufferHndl, format, data, size, sample_rate);
	if (alGetError() != AL_NO_ERROR) {
		std::cout << "Error: SoundBuffer::SoundBuffer()\n";
	}
}

SoundSource::SoundSource(const char * a_Path) : m_Buffer(a_Path)
{
	// Create source
	alGenSources(1, &m_SourceHndl);
	alSourcef(m_SourceHndl, AL_PITCH, 1);
	alSourcef(m_SourceHndl, AL_GAIN, 1);
	alSource3f(m_SourceHndl, AL_POSITION, 0, 0, 0);
	alSource3f(m_SourceHndl, AL_VELOCITY, 0, 0, 0);
	alSourcei(m_SourceHndl, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		std::cout << "Error: SoundSource::SoundSource()\n";
	}
	
	// Attatch buffer to source
	alSourcei(m_SourceHndl, AL_BUFFER, m_Buffer.m_BufferHndl);
}