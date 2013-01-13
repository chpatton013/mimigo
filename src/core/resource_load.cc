#include "core/resource_load.h"
#include "core/mesh_load.h"
#include "core/texture.h"
#include "global/stl_util.h"

#include <fstream>
#include <unistd.h>
#include <sstream>

using namespace std;

void LoadResourcesFromFile(const string& filename) {
   c + s("loading resources from %s", filename.c_str());
   string line;
   ifstream in(filename.c_str());
   while (getline(in, line)) {
      if (line == "objects") {
         chdir("models");
         while (getline(in, line) && line != "end")
            LoadEntityFromOBJFile(line);
         chdir("..");
      } else if (line == "animations") {
      } else if (line == "resources") {
         while (getline(in, line) && line != "end")
            LoadResourcesFromFile(line);
      } else if (line == "textures") {
         chdir("textures");
         while (getline(in, line) && line != "end")
            LoadTexture((char*)line.c_str());
         chdir("..");
      }
   }
}
