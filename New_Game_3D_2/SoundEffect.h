#pragma once



class SoundEffect
{
public:
	SoundEffect(const char *_name);
	~SoundEffect();


	void PlaySoundEffect();
	void OnePlaySoundEffect();
	void StopSoundEffect();
	void Release();

	void SetPronunciation(bool _set) { isPronunciation = _set; }

private:
	int soundEffectMusicHandle;
	int soundEffectMusicCount;
	bool isPronunciation;

};