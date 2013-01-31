#ifndef LOGIC_PUZZLE_SQUARE_H_
#define LOGIC_PUZZLE_SQUARE_H_

enum LogicPuzzleSquareType { LOGIC_PUZZLE_SQUARE_GREEN, LOGIC_PUZZLE_SQUARE_RED, LOGIC_PUZZLE_SQUARE_YELLOW };
class LogicPuzzleSquare {
  public:
   LogicPuzzleSquare(LogicPuzzleSquareType start_color, const std::string& id) :
      color_(start_color)
   { Initialize(id); }

  private:
   void Initialize(const std::string& id);
   LogicPuzzleSquareType color_;
};

#endif
