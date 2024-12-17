#include "util.h"
#include <iostream>
#include <cstdlib>
#include <regex>
#include "visualisation.h"
#include <stack>
#include "computer.h"

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
  Util::readAsGrid<unsigned int>("day2.txt", reports);

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

void day3()
{
  std::vector<std::string> instructions;
  std::vector<int> to_multiply;
  Util::readFile<std::string>("day3.txt", instructions);
  bool mult_allowed = true;

  for(auto str : instructions)
  {
    std::regex mult_regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)");
    auto instr_begin = std::sregex_iterator(str.begin(), str.end(), mult_regex);
    auto instr_end = std::sregex_iterator();
    for(std::sregex_iterator i = instr_begin; i != instr_end; ++i)
    {
      std::smatch match = *i;
      std::string match_str = match.str();
      std::regex num_regex("[0-9]{1,3}");
     if(match_str == "do()")
      {
  //    std::cout << match_str << std::endl;
      mult_allowed = true;
      }
      if(match_str == "don't()")
	mult_allowed = false;
      if(mult_allowed)
      {
	
        auto num_begin = std::sregex_iterator(match_str.begin(), match_str.end(), num_regex);
        auto num_end = std::sregex_iterator();
        int num = 1;
	bool add_num = false;
	for(std::sregex_iterator j = num_begin; j != num_end; ++j)
	{
	  num *= std::stoi((*j).str());
	  add_num = true;
//	std::cout << num << std::endl;
        }
	if(add_num)
          to_multiply.push_back(num);
      }
//      std::cout << match_str << std::endl;
    }
  }
  int sum = 0;
    
  for(auto mult : to_multiply)
  {
    sum += mult;
  }
  std::cout << sum << std::endl;
}

void day4()
{
  std::vector<std::vector<char>> grid;
  Util::readAsGrid<char>("test.txt", grid);
  Crawler crawl;

  Visualisation display{};
  display.grid = grid;
  if (display.Construct(256, 240, 4, 4))
    display.Start();


/*
  for(int y = 0; y < grid.size(); y++)
  {
    for(int x = 0; x < grid[y].size(); x++)
    {
//	crawl.moveCrawler(Crawler::Direction::Right);
	std::cout << grid[y][x];
    }
  //  crawl.moveCrawler(Crawler::Direction::Down);
    std::cout << std::endl;
  }
  for(auto row : grid)
  {
    for(auto c : row)
    {
//	std::cout << c;
    }
//    std::cout << std::endl;
  }
	 */
}
#define GRID_SIZE 12
void day8()
{
  std::vector<std::vector<char>> grid;
  Util::readAsGrid<char>("test.txt", grid);
  struct Node
  {
    char c;
    olc::vu2d pos;
  };

  for(auto row : grid)
  {
    for(auto c : row)
    {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  
  int overlap_counter = 0;
  for(int y = 0; y < GRID_SIZE; y ++)
  {
    for(int x = 0; x < grid[y].size(); x++)
    {
      //search for an antenna
      char c = grid[y][x];
      if((c != '.') && (c != '#'))
      {
	Node first_node;
	first_node.c = c;
	first_node.pos.x = x;
	first_node.pos.y = y;
	bool first_row = true;
	for(int y2 = y; y2 < GRID_SIZE; y2++)
	{
	  for(int x2 = 0; x2 < grid[y].size(); x2++)
	  {
	    if(first_row)
	    {
	      x2 = x+1;
	      first_row = false;
	    }
	    c = grid[y2][x2];
	    if(c == first_node.c)
	    {
	      olc::vi2d second_pos{x2, y};
	      olc::vi2d distance = second_pos - first_node.pos;
	      olc::vi2d distance_to_antinode = first_node.pos - distance;
	      std::cout << "first node: " << first_node.pos.str() << std::endl; 
	      std::cout << "second node: " << second_pos.str() << std::endl; 
	      std::cout << "Distance: " << distance.str() << std::endl; 
	      if((distance_to_antinode.x >= 0) && (distance_to_antinode.x < GRID_SIZE) &&
		 (distance_to_antinode.y >= 0) && (distance_to_antinode.y < GRID_SIZE))
	      {
		std::cout << "Distance to antinode: " << distance_to_antinode.str() << std::endl; 
		if(grid[distance_to_antinode.y][distance_to_antinode.x] == '.')
		{
		  grid[distance_to_antinode.y][distance_to_antinode.x] = '#'; 
		}
		else
		{
		  overlap_counter++;
		}
	      }
	      distance_to_antinode = second_pos + distance;
	      if((distance_to_antinode.x >= 0) && (distance_to_antinode.x < GRID_SIZE) &&
		 (distance_to_antinode.y >= 0) && (distance_to_antinode.y < GRID_SIZE))
	      {
		std::cout << "Distance to antinode: " << distance_to_antinode.str() << std::endl; 
		if(grid[distance_to_antinode.y][distance_to_antinode.x] == '.')
		{
		  grid[distance_to_antinode.y][distance_to_antinode.x] = '#'; 
		}
		else
		{
		  overlap_counter++;
		}
	      }
	    }
	  }
	}
      }
    }
  }

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
 
  for(auto row : grid)
  {
    for(auto c : row)
    {
      std::cout << c;
    }
    std::cout << std::endl;
  }
 
  //parse the grid
  //find antenna save location
  //then search for the next
  //calculate the distance to the antinode
  //update the grid with the antinodes
  //if occuppied just increase the counter...
}

void day15()
{
  constexpr int GRID_WIDTH{50};
  constexpr int GRID_HEIGHT{50};
  constexpr char WALL{'#'};
  constexpr char BOX{'O'};
  constexpr char ROBOT{'@'};
  constexpr char EMPTY_SPACE{'.'};
  
  std::vector<std::string> instructions;

  enum class Direction
  {
    right,
    left,
    up,
    down
  };

  class Robot 
  {
    std::vector<std::vector<char>> grid;
    public:
      olc::vi2d pos;
      Robot(olc::vi2d _pos):pos{_pos} 
      {
	Util::readAsGrid<char>("day15.txt", grid, true);
      };
      void print_grid()
      {
 	for(auto row : grid)
	{
	  for(auto c : row)
	  {
	    std::cout << c;
	  }
	  std::cout << std::endl;
	}
	std::cout << std::endl;
      };
      
      void count_boxes()
      {
	int coo_sum{0}, x{0}, y{0};
	for(auto row : grid)
	{
	  for(auto c : row)
	  {
	    if(BOX == c)
	    {
	      int coo{0};

	      coo = (100 * y) + x;
	      coo_sum += coo;
	    }
	    x++;
	  }
	  y++;
	  x = 0;
	}
	std::cout << "Coordinate sum: " << coo_sum << std::endl;
      }

      void move(Direction dir)
      {
	olc::vi2d new_pos{pos};
	auto calculate_pos = [](olc::vi2d &new_pos, Direction dir)
	{
	  switch(dir)
	  {
	    case Direction::left:
	      new_pos -= olc::vi2d({1,0});	    
	    break;
	    case Direction::right:
	      new_pos += olc::vi2d({1,0});
	    break;
	    case Direction::up:
	      new_pos -= olc::vi2d({0,1});
	    break;
	    case Direction::down:
	      new_pos += olc::vi2d({0,1});
	    break;
	  }
	};

	calculate_pos(new_pos, dir);
	// ! seems a suitable invalid character
	char next_tile = '!';
	auto check_validity =  [](olc::vi2d &new_pos) {
	  if((new_pos.x >= 0) && (new_pos.x < GRID_WIDTH) &&
	    (new_pos.y >= 0) && (new_pos.y < GRID_HEIGHT))
	      return true;
	  else
	    return false;
	};

	if(check_validity(new_pos))
	{
	  next_tile = grid[new_pos.y][new_pos.x];
//	  pos = new_pos;
//	  std::cout << "Char @ pos " << pos << ": " << next_tile << std::endl;
	}
	else
	{
	  next_tile = '!';
	  std::cout << "Invalid new position @ " << new_pos << std::endl;
	}
	
	auto swap_tiles = [&](olc::vi2d new_p, olc::vi2d old_p)
	{
	  char old_c = grid[old_p.y][old_p.x];
	  grid[old_p.y][old_p.x] = grid[new_p.y][new_p.x];
	  grid[new_p.y][new_p.x] = old_c;
	};

	if('!' != next_tile)
	{
	  if(WALL != next_tile)
	  {
	    if(EMPTY_SPACE == next_tile)
	    {
	      grid[pos.y][pos.x] = EMPTY_SPACE;
	      grid[new_pos.y][new_pos.x] = ROBOT;
	      pos = new_pos;
	    }
	    else if(BOX == next_tile)
	    {
	      bool stop_checking = false;
	      bool empty_stack = false;
	      olc::vi2d next_pos{new_pos};
	      std::stack<olc::vi2d> checked_pos;
	      // stack
	      checked_pos.push(next_pos);
	      while(!stop_checking)
	      {
		calculate_pos(next_pos, dir);

		if(check_validity(next_pos))
		{
		  checked_pos.push(next_pos);
		  next_tile = grid[next_pos.y][next_pos.x];
		  if(EMPTY_SPACE == next_tile)
		  {
		    stop_checking = true;
		  }
		  else if(WALL == next_tile)
		  {
		    //empty the stack
		    while(!checked_pos.empty())
		      checked_pos.pop();
		    stop_checking = true;
		  }		  
		}
		else
		{
		  stop_checking = true;
		}	
	      }
	      while(!checked_pos.empty())
	      {
		olc::vi2d old_pos = checked_pos.top();
		olc::vi2d new_pos{old_pos};
		checked_pos.pop();
		switch(dir)
		{
		  case Direction::left:
		    calculate_pos(new_pos, Direction::right);
		  break;
		  case Direction::right:
	  	    calculate_pos(new_pos, Direction::left);
		  break;
		  case Direction::up:
		    calculate_pos(new_pos, Direction::down);
	          break;
	          case Direction::down:
		    calculate_pos(new_pos, Direction::up);
		  break;
		}
		
		swap_tiles(old_pos, new_pos);
		pos = old_pos;
	      }
	    }
	  }
	}
      };
  };


  Util::readFile("day15.txt", instructions, true);
  for(auto instr : instructions)
    std::cout << instr << std::endl;

  Robot roby{{24,24}};
  roby.print_grid();
  for(std::string instr : instructions)
  {
    std::stringstream ss;
    char dir;
    ss << instr;

    while(ss >> dir)
    {
     // std::cout << "Move " << dir << ":" << std::endl;
      if(dir == '<')
	roby.move(Direction::left);
      else if(dir == 'v')
	roby.move(Direction::down);
      else if(dir == '^')
	roby.move(Direction::up);
      else if(dir == '>')
	roby.move(Direction::right);
      //roby.print_grid();
    }
  }  
  roby.print_grid();
  roby.count_boxes();
}

void day17()
{
  Computer chrono{18427963, 0, 0, "2,4,1,1,7,5,0,3,4,3,1,6,5,5,3,0"};
  chrono.run();
}

int main()
{
//  Visualisation display{};
//  if (display.Construct(256, 240, 4, 4))
//    display.Start();


  day17();
}
