#include "util.h"
#include <iostream>
#include <cstdlib>

int main()
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
