#ifndef _STL_UTIL_H_
#define _STL_UTIL_H_

#include <algorithm>
#include <stdio.h>
#include <map>
#include <string>
#include <cstdarg>
#include <vector>
#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>

template<typename T>
std::string toString(const T& value) {
   std::ostringstream oss;
   oss << value;
   return oss.str();
}

class FString : public std::string {
public:
   FString(const char *fmt, ...) {
      static const int bufLen = 1024;
      static char buf[bufLen];
      va_list args;

      va_start(args, fmt);
      vsnprintf(buf, bufLen, fmt, args);
      va_end(args);

      *(std::string *)this = std::string(buf);
   }
};

namespace stl_util {

template <class T>
bool Remove(std::vector<T>& list, T remove) {
   typename std::vector<T>::iterator it =
         std::find(list.begin(), list.end(), remove);
   if (it != list.end()) {
      list.erase(it);
      return true;
   }
   return false;
}

// Removes all of remove from list. Stops at the first failure.
template <class T>
bool RemoveAllOf(std::vector<T>& list, const std::vector<T>& remove) {
   bool ret = true;
   for (size_t i = 0; i < remove.size(); ++i)
      ret = ret && Remove(list, remove[i]);
   return ret;
}

template <class T>
bool Contains(const std::vector<T>& list, const T& item) {
   return std::find(list.begin(), list.end(), item) != list.end();
}

template <class Collection, class Key>
bool ContainsKey(const Collection& collection, const Key& key) {
   return collection.find(key) != collection.end();
}

template <class F>
bool Equal(F a, F b) {
   return std::abs(a - b) < std::numeric_limits<F>::epsilon();
}

}

#endif
