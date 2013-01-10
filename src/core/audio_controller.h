#ifndef _AUDIO_CONTROLLER_H_
#define _AUDIO_CONTROLLER_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>

class AudioController {
  public:
   static AudioController* Instance(void);

   // TODO: Make a playlist type functionality.
   // Loads a song into the buffer.
   void LoadSong(const char *path);
   // Starts the song currently loaded playing.
   void PlayMusic(void);

   // Loads and returns a sound effect of .WAV format.
   int LoadSoundEffect(const char *path);
   // Plays a given sound effect. Repeats num_repeats times.
   void PlaySoundEffect(int index, int num_repeats);

  private:
   AudioController();
   virtual ~AudioController();

   void Initialize(void);

   static AudioController *audio_controller_;
   Mix_Music *music_;
   std::vector<Mix_Chunk *> sound_effects_;
};

#endif
