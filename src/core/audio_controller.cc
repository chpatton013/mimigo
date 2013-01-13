#include "core/audio_controller.h"

#include <stdio.h>
#include <stdlib.h>

namespace {

// The amount of audio to buffer in bytes.
static const int kAudioBuffers = 4096;

};

AudioController *AudioController::audio_controller_ = NULL;

//static
AudioController *AudioController::Instance() {
   if (!audio_controller_)
      audio_controller_ = new AudioController();
   return audio_controller_;
}

AudioController::AudioController() {
   music_ = NULL;
   Initialize();
}

AudioController::~AudioController() {
   if (music_)
      Mix_FreeMusic(music_);
   Mix_CloseAudio();
}

void AudioController::Initialize() {
   if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
       MIX_DEFAULT_CHANNELS, kAudioBuffers)) {
      fprintf(stderr, "Audio failed to load.\n");
      exit(EXIT_FAILURE);
   }
}

void AudioController::LoadSong(const char *path) {
   if (!music_)
      music_ = Mix_LoadMUS(path);
}

void AudioController::PlayMusic() {
   Mix_PlayMusic(music_, 0);
}

int AudioController::LoadSoundEffect(const char *path) {
   Mix_Chunk *effect = Mix_LoadWAV(path);
   if (!effect) {
      fprintf(stderr, "%s failed to load\n", path);
      exit(EXIT_FAILURE);
   }
   sound_effects_.push_back(effect);
   return sound_effects_.size() - 1;
}

void AudioController::PlaySoundEffect(int index, int num_repeats) {
   if (num_repeats < 0 || index < 0 || index >= int(sound_effects_.size()))
      return;
   Mix_PlayChannel(-1, sound_effects_[index], num_repeats);
}
