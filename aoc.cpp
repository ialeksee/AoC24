#include "util.h"
#include <iostream>
#include <cstdlib>

void day1()
{
    std::vector<unsigned int> test_vector;
    std::vector<unsigned int> left;
    std::vector<unsigned int> right;
    Util::readFile<unsigned int>("day1.txt", test_vector);
    bool is_left = true;
    for(auto num : test_vector)
    {
      (is_left) ? left.push_back(num) : right.push_back(num);
      is_left = !is_left;
    }  
    std::stable_sort(left.begin(), left.end());
    std::stable_sort(right.begin(), right.end());
    unsigned int distance_total{0};
    auto lit = left.begin();
    
    for(;lit != left.end(); ++lit)
    {
      unsigned int num = *lit;
      
      distance_total += num*std::count(right.begin(), right.end(), num);
    }
    std::cout << distance_total << std::endl; 
}

void day2()
{
  int safe_reports = 0;
  std::vector<std::vector<unsigned int>> reports;
  Util::readByLine<unsigned int>("day2.txt", reports);

  for(auto report : reports)
  {
    bool is_safe = true;
    bool is_really_safe = true;
    bool is_ascending = false;
    bool is_descending = false;
    if(report.empty())
      break;
    auto iter = report.begin();
    while(iter + 1 != report.end())
    {
      auto diff = std::abs((int)(*(iter + 1) - *iter));
      if((diff == 0)||(diff > 3))
      {
	is_safe = false;
	break;
      }
      if(*(iter + 1) > *iter)
      {
	if(!is_descending && !is_ascending)
	{
	  is_ascending = true;
	}
	else if(is_descending)
	{  
	  is_safe = false;
	  break;
	}
      }
      
      if(*(iter + 1) < *iter)
      {
	if(!is_descending && !is_ascending)
	{
	  is_descending = true;
	}
	else if(is_ascending)
	{  
	  is_safe = false;
	  break;
	}
      }
      iter++;
    }
    if(is_safe)
      safe_reports++;
  }

  std::cout << safe_reports << std::endl;
}

int main()
{
  day2();
}
