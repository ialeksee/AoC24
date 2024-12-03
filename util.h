#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Util
{
  public:
    Util(){};
    template <typename T> static void readFile(std::string filename, std::vector<T> &out);
};

template <typename T> void Util::readFile(std::string filename, std::vector<T> &out)
{
  std::ifstream ifs;
  std::string str;
  T token;

  ifs.open(filename);

  if(ifs)
  {
    while(!ifs.eof())
    {
      std::getline(ifs, str);

      std::stringstream ss;
      ss << str;

      while(ss >> token)
      {
	out.push_back(token);
      }
    }
  } 
}

#endif
