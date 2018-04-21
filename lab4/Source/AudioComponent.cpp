#include "AudioComponent.h"
#include "Actor.h"
#include <SDL/SDL_Mixer.h>

IMPL_COMPONENT(AudioComponent, Component);

SoundCue::SoundCue() : mChannel(-1) {

}

SoundCue::SoundCue(int channel) : mChannel(channel) {

}

void SoundCue::Pause() {
	if (mChannel != -1) {
		Mix_Pause(mChannel);
	}
}

void SoundCue::Resume() {
	if (mChannel != -1) {
		Mix_Resume(mChannel);
	}
}

void SoundCue::Stop() {
	if (mChannel != -1) {
		Mix_HaltChannel(mChannel);
	}
}

bool SoundCue::IsPlaying() {
	int playing;

	if (mChannel != -1) {
		playing = Mix_Playing(mChannel);
	}

	if (playing == 1) {
		return true;
	}

	return false;
}

bool SoundCue::IsPaused() {
	int paused;

	if (mChannel != -1) {
		paused = Mix_Paused(mChannel);
	}

	if (paused == 1) {
		return true;
	}

	return false;
}

AudioComponent::AudioComponent(Actor& owner) : Super(owner) {

}

SoundCue AudioComponent::PlaySound(SoundPtr sound, bool looping) {
	SoundCue cue;
	Mix_Chunk* chunky = sound->GetData();

	int select;

	if (looping) {
		select = -1;
	}
	else {
		select = 0;
	}

	cue = Mix_PlayChannel(-1, chunky, select);

	return cue;
}