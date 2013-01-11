#ifndef _MATRIX_STACK_H_
#define _MATRIX_STACK_H_

#include "../../third_party/glm/glm/gtx/vector_angle.hpp"
#include <deque>

class MatrixStack {
  public:
   MatrixStack() { load_identity(); }

   void load_identity()
   { stack.clear(); stack.push_back(glm::mat4(1.0f)); }

   void push() { stack.push_back(stack.back()); }
   void pop() {
      assert(!stack.empty());
      stack.pop_back();
      if (stack.empty()) load_identity();
   }

   void translate(const glm::vec3& offset)
   { stack.push_back(top() * glm::translate(top(), offset)); }
   void scale(const glm::vec3& s)
   { stack.push_back(top() * glm::scale(top(), s)); }
   void rotate(float angle, const glm::vec3& axis)
   { stack.push_back(top() * glm::rotate(top(), angle, axis)); }
   void multiply(const glm::mat4& matrix)
   { stack.push_back(top() * matrix); }

   const glm::mat4& top() { return stack.back(); }

   void ortho(float left, float right, float bottom, float t,
              float z_near, float z_far) {
      stack.push_back(top() * glm::ortho(left, right, bottom, t,
               z_near, z_far));
   }

   void frustum(float left, float right, float bottom, float t,
                float z_near, float z_far) {
      stack.push_back(top() * glm::frustum(left, right, bottom, t,
               z_near, z_far));
   }

   void lookAt(const glm::vec3& eye,
         const glm::vec3& target,
         const glm::vec3& up) {
      stack.push_back(top() * glm::lookAt(eye, target, up));
   }

  private:
   std::deque<glm::mat4> stack;
};

#endif
