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
    template <typename T> static void readFile(std::string filename, std::vector<T> &out, bool split_file = false);
    template <typename T> static void readAsGrid(std::string filename, std::vector<std::vector<T>> &out, bool newline_break = false);
};

template <typename T> void Util::readFile(std::string filename, std::vector<T> &out, bool split_file)
{
  std::ifstream ifs;
  std::string str;
  bool start_parsing = !split_file;
  T token;

  ifs.open(filename);

  if(ifs)
  {
    while(!ifs.eof())
    {
      std::getline(ifs, str);
      
      if(start_parsing)
      {
	std::stringstream ss;
	ss << str;

	while(ss >> token)
	{
	  out.push_back(token);
        }
      }
      if((str == "") && split_file)
	start_parsing = true;
    }
  } 
}

template <typename T> void Util::readAsGrid(std::string filename, std::vector<std::vector<T>> &out, bool newline_break)
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
      
      if((str == "") && (newline_break))
	break;
      std::stringstream ss;
      ss << str;

      std::vector<T> temp;
      while(ss >> token)
      {
	temp.push_back(token);
      }
      out.push_back(temp);
    }
  } 
}
#endif
