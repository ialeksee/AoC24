#ifndef VISUALISATION_H
#define VISUALISATION_H
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine/olcPixelGameEngine.h"

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

    if(temp_x >= 0)
      x = temp_x;
    if(temp_y >= 0)
      y = temp_y;
  }
};

class Visualisation : public olc::PixelGameEngine
{
public:
	std::vector<std::vector<char>> grid;
	Crawler crawl;
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
		  crawl.moveCrawler(Direction::LEFT)
      };
	  if('X' == grid[crawl.y][crawl.x])
	  {

	  }
	  for(int y = 0; y < grid.size(); y++)
	  {
	    for(int x = 0; x < grid[y].size(); x++)
	    {
	      std::string txt{grid[y][x]};
	      DrawStringDecal({x*2, y*2}, txt, olc::WHITE, { 0.2f, 0.2f });
	      //DrawString(x*2, y*2, txt, olc::WHITE,0.2);	
		//crawl.moveCrawler(Crawler::Direction::Right);
		//std::cout << grid[y][x];
	    }
	    //crawl.moveCrawler(Crawler::Direction::Down);
	    //std::cout << std::endl;
	  }
	 
		// called once per frame
//		for (int x = 0; x < ScreenWidth(); x++)
	//		for (int y = 0; y < ScreenHeight(); y++)
		//		Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
		return true;
	}
};


#endif
