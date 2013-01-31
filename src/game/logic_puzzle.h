#ifndef LOGIC_PUZZLE_H_
#define LOGIC_PUZZLE_H_

#include "logic_puzzle_square.h"

class LogicPuzzle {
  public:
   LogicPuzzle(int width, int height) :
      width_(width),
      height_(height)
   {}

  private:
   const int width_, height_;
};

#endif
