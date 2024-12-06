#ifndef VISUALISATION_H
#define VISUALISATION_H
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine/olcPixelGameEngine.h"
#define GRID_SIZE 140
struct Crawler
{
  unsigned int x{0}, y{0};
  enum class Direction{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
  };

  void moveCrawler(Crawler::Direction dir)
  {
    int temp_x = x;
    int temp_y = y;
    switch(dir)
    {
      case Direction::LEFT:
	temp_x -= 1;
      break;
      case Direction::RIGHT:
	temp_x += 1;
      break;
      case Direction::UP:
	temp_y -= 1;
      break;
      case Direction::DOWN:
	temp_y += 1;
      break;
      case Direction::UP_LEFT:
	temp_x -= 1;
	temp_y -= 1;
      break;	
      case Direction::UP_RIGHT:
	temp_x += 1;
        temp_y -= 1;
      break;
      case Direction::DOWN_LEFT:
	temp_x -= 1;
	temp_y += 1;
      break;
      case Direction::DOWN_RIGHT:
	temp_x += 1;
	temp_y += 1;
      break;
    };

    if((temp_x >= 0) && (temp_x < GRID_SIZE))
      x = temp_x;
    if((temp_y >= 0) && (temp_y < GRID_SIZE))
      y = temp_y;
  }
};

class Visualisation : public olc::PixelGameEngine
{
public:
	std::vector<std::vector<char>> grid;
	Crawler crawl;
	int xmas_count{0};
	bool stop_rendering{false};
	bool end_reached{false};
	bool end_reached_y{false};
	Visualisation()
	{
		sAppName = "Advent of Code 2024";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
	  auto check_for_letter = [&] (char c)
	  {
	    unsigned int initial_x{crawl.x}, initial_y{crawl.y};
	    crawl.moveCrawler(Crawler::Direction::LEFT);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::RIGHT);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::UP);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::DOWN);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::UP_LEFT);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::UP_RIGHT);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::DOWN_RIGHT);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    crawl.moveCrawler(Crawler::Direction::DOWN_LEFT);
	    if(c == grid[crawl.y][crawl.x])
	      return true;
	    crawl.x = initial_x;
	    crawl.y = initial_y;
	    return false;
	  };
	  
	  if(!stop_rendering)
	  {
	    if('X' == grid[crawl.y][crawl.x])
	    {
	      unsigned int start_x{crawl.x}, start_y{crawl.y};
	      if(check_for_letter('M'))
		if(check_for_letter('A'))
		  if(check_for_letter('S'))
		    xmas_count++;
	      crawl.x = start_x;
	      crawl.y = start_y;
	    }
	    crawl.moveCrawler(Crawler::Direction::RIGHT);
	    if(crawl.x == grid[crawl.y].size() - 1)
	    {
	      if(!end_reached)
		end_reached = true;
	      else
	      {
		crawl.x = 0;
		crawl.moveCrawler(Crawler::Direction::DOWN);
		end_reached = false;
	      }
	    }
	    if(crawl.y == GRID_SIZE-1)
	      if(!end_reached_y)
		end_reached_y = true;
	      else
		stop_rendering = true;
	  }
	 // for(int y = 0; y < grid.size(); y++)
//	  {
//	    for(int x = 0; x < grid[y].size(); x++)
//	    {
	  if(!stop_rendering)  
	  {
	    std::string txt = "XMAS count: " + std::to_string(xmas_count);
	    std::string txt2 = "Crawler X: " + std::to_string(crawl.x);
	    std::string txt3 = "Crawler Y: " + std::to_string(crawl.y);
      //DrawStringDecal({x*2, y*2}, txt, olc::WHITE, { 0.2f, 0.2f });
	    Clear(olc::BLACK);
	    DrawString(0, 0, txt);
	    DrawString(0, 20, txt2);
	    DrawString(0, 40, txt3);
	  }
		//crawl.moveCrawler(Crawler::Direction::Right);
		//std::cout << grid[y][x];
//	    }
	    //crawl.moveCrawler(Crawler::Direction::Down);
	    //std::cout << std::endl;
//	  }
	 
		// called once per frame
//		for (int x = 0; x < ScreenWidth(); x++)
	//		for (int y = 0; y < ScreenHeight(); y++)
		//		Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
		return true;
	}
};


#endif
