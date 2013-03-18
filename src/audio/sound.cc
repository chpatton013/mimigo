#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <streambuf>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "sound.h"

using namespace std;

// 16 possible sound channels
Mix_Chunk* sounds[16];

void audioError(const char* action) {
   fprintf(stderr, "Unable to %s audio file: %s\n", action, Mix_GetError());
}
void playError() {
   audioError("play");
}
void loadError() {
   audioError("load");
}

void cleanChannels() {
   for (int ndx = 0; ndx < 16; ndx++) {
      if (sounds[ndx] != NULL && Mix_Playing(ndx) == 0) {
         Mix_FreeChunk(sounds[ndx]);
         sounds[ndx] = NULL;
      }
   }
}

void initSound() {
   for (int ndx = 0; ndx < 16; ++ndx) {
      sounds[ndx] = NULL;
   }

   int rate = 22050;
   Uint16 format = AUDIO_S16SYS;
   int channels = 2;
   int buffers = 4096;

   if (Mix_OpenAudio(rate, format, channels, buffers)) {
      loadError();
   }
}

void playSampleWAV(string path) {
   cleanChannels();

   Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
   if (sound == NULL) {
      loadError();
      return;
   }

   int channel = Mix_PlayChannel(-1, sound, 0);
   if (channel < 0) {
      playError();
   }

   sounds[channel] = sound;
}

void loopSampleWAV(string path) {
   Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
   if (sound == NULL) {
      loadError();
      return;
   }

   int channel = Mix_PlayChannel(-1, sound, -1);
   if (channel < 0) {
      playError();
   }

   sounds[channel] = sound;
}

void playMusic(string path) {
   Mix_Music* music = Mix_LoadMUS(path.c_str());

   if (music == NULL) {
      loadError();
   } else {
      Mix_PlayMusic(music, 0);
   }
}

void loopMusic(string path) {
   Mix_Music* music = Mix_LoadMUS(path.c_str());

   if (music == NULL) {
      loadError();
   } else {
      Mix_PlayMusic(music, -1);
   }
}
