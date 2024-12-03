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
  int old_safe_reps = 0;
  int new_safe_reps = 0;
  std::vector<std::vector<unsigned int>> reports;
  Util::readByLine<unsigned int>("day2.txt", reports);

  for(auto report : reports)
  {
    bool is_safe = true;
    bool is_dampened = false;
   if(report.empty())
      break;
//    std::cout << "Initial report: ";
//    for(auto num : report)
//      std::cout << num << " ";
//    std::cout << std::endl;
    auto check_safety = [&](std::vector<unsigned int> rep)
    {
      auto iter = rep.begin();
      bool is_ascending = false;
      bool is_descending = false;
    
      while(iter + 1 != rep.end())
      {
	//std::cout << *iter << " ";
	auto diff = std::abs((int)(*(iter + 1) - *iter));
	if((diff == 0)||(diff > 3))
	{
	  is_safe = false;
//	  std::cout << "Diff is: " << diff << std::endl;
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
//	    std::cout << "Ascending broken"  << std::endl;
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
//		  std::cout << "Descending broken" << std::endl;
	  }
	}
	if(!is_safe)
	{
	  break;
	}
	iter++;
      }
    };
    check_safety(report);
 //   std::cout << std::endl;
    if(is_safe)
    {
//      std::cout << "Initial report: ";
//      for(auto num : report)
//	std::cout << num << " ";
// ..     std::cout << std::endl;
      old_safe_reps++;
      safe_reports++;
    }
    else
    {
      std::vector<unsigned int> copy_vec;
      auto it = report.begin();
      int idx = 0;
      while(it != report.end())
      {
	copy_vec = report;
	is_safe = true;
	copy_vec.erase(copy_vec.begin() + idx);
	//std::cout << "Copy vector: ";
	//for(auto num : copy_vec)
	 // std::cout << num << " ";
	//std::cout << std::endl;
	check_safety(copy_vec);
	//std::cout << std::endl;
//	if(is_safe)
/*	{
	  std::cout << "Original report: ";
	  for(auto num : report)
	    std::cout << num << " ";
	  std::cout << std::endl;
	  
	  std::cout << "Copy vector: ";
	  for(auto num : copy_vec)
	    std::cout << num << " ";
	  std::cout << std::endl;
*/
	if(is_safe)
	{
	  new_safe_reps++;
	  safe_reports++;
	  break;
	}
	it++;
	idx++;
      }
    }
  }

   std::cout << old_safe_reps << std::endl;
   std::cout << new_safe_reps << std::endl;
   std::cout << safe_reports << std::endl;
}

int main()
{
  day2();
}
