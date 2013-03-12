#include <string.h>

const std::string TECHNO_SAMPLE = "src/audio/samples/tek2beat178.wav";
const std::string SIMPLE_SAMPLE = "src/audio/samples/sound.wav";
const std::string NODENS = "src/audio/samples/nodens.mp3";
const std::string SOLACE = "src/audio/samples/solace.mp3";
const std::string JUMP = "src/audio/samples/jump.wav";

void initSound();
void playSampleWAV(std::string path);
void loopSampleWAV(std::string path);
void playMusic(std::string path);
void loopMusic(std::string path);
