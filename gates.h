#pragma once
#include <vector>
#include <string>

enum class Operation {AND, OR, XOR, NA};

struct Gate
{
  Gate input1;
  Gate input2;
  Gate output;
  std::string name;
  Operation op;
  bool input1_set;
  bool input2_set;
  bool output_ready;

  void calc();
  void main_task();
};


