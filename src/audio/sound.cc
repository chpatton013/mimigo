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

int channels[16];
// sound in memory pointer goes here
Mix_Chunk * sounds[16];

void initSound() {

   int audio_rate = 22050;
   Uint16 audio_format = AUDIO_S16SYS;
   int audio_buffers = 4096;
   int audio_channels = 2;
   for(int i = 0; i < 16; i++) 
      channels[i] = 0;

   if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
      cout << "super bad error opening the audio" << endl;
   }
}

void playSampleWAV(string path) {
   for(int i = 0; i < 16; i++) {
      channels[i] = Mix_Playing(i);
      if(channels[i] == 0) {
         if(Mix_Playing(i) == 0) {
            Mix_FreeChunk(sounds[i]);
         }
      }
   }
   Mix_Chunk *sound = NULL; // reference to the sound in memory
   int channel = -1; // play on first available channel

   sound = Mix_LoadWAV(path.c_str());
   if(sound == NULL) {
      printf("Unable to load WAV file: %s\n", Mix_GetError());
      return;
   }

   channel = Mix_PlayChannel(-1, sound, 0);
   channels[channel] = 1;
   if(channel == -1) {
      cout << "unable to play the sound.wav" << endl;
   }

   sounds[channel] = sound;
}

void loopSampleWAV(string path) {
   Mix_Chunk *sound = NULL; // reference to the sound in memory
   int channel = -1; // play on first available channel

   sound = Mix_LoadWAV(path.c_str());
   if(sound == NULL) {
      printf("Unable to load WAV file: %s\n", Mix_GetError());
      return;
   }

   channel = Mix_PlayChannel(-1, sound, -1);
   channels[channel] = 1;
   if(channel == -1) {
      cout << "unable to play the sound.wav" << endl;
   }

   sounds[channel] = sound;
}

void playMusic(string path) {
   Mix_Music *music = NULL; // reference to the sound in memory

   music = Mix_LoadMUS(path.c_str());
   if(music == NULL) {
      printf("Unable to load music file: %s\n", Mix_GetError());
      return;
   }

   Mix_PlayMusic(music, 0);

}

void loopMusic(string path) {
   Mix_Music *music = NULL; // reference to the sound in memory

   music = Mix_LoadMUS(path.c_str());
   if(music == NULL) {
      printf("Unable to load music file: %s\n", Mix_GetError());
      return;
   }

   Mix_PlayMusic(music, -1);
}
