#include "util.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>

int main()
{
  std::ifstream ifs;
  std::string str;
  std::vector<unsigned int> left;
  std::vector<unsigned int> right;
  unsigned int number;
  bool isRight = false;
  ifs.open("day1.txt");

  if(ifs)
  {
    while(!ifs.eof())
    {
      std::getline(ifs, str);

      std::stringstream ss;
      ss << str;

      while(ss >> number)
      {
	if(isRight)
	{
	  right.push_back(number);
	}
	else
	{
	  left.push_back(number);
	}
	isRight = !isRight;
      }
    }
    
    std::stable_sort(left.begin(), left.end());
    std::stable_sort(right.begin(), right.end());
    unsigned int distance_total{0};
    auto lit = left.begin();
    auto rit = right.begin();
    for(;lit != left.end(); ++lit, ++rit)
    {
      distance_total += std::abs(int(*lit - *rit));
    }

    std::cout << "Distance: "<< distance_total << std::endl;
    /*
    std::cout << "Left array" << std::endl;
    for(auto num : left)
    {
      std::cout << num << std::endl;
    }

    std::cout << "Right array" << std::endl;
    for(auto num : right)
    {
      std::cout << num << std::endl;
    }
    */
  }
}
