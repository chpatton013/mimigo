#ifndef CALLBACK_H_
#define CALLBACK_H_

class Callback {
  public:
   Callback(void (*func)(void *), void *caller) :
      func_(func),
      caller_(caller)
   {}

   void Call() { if (func_ && caller_) func_(caller_); }

  private:
   void (*func_)(void *);
   void *caller_;
};

#endif
