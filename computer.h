#include <cstdint>
#include <vector>
#include <cmath>

struct Operand
{
  uint8_t op : 3;
};

class Computer
{
  private:
    uint32_t A;
    uint32_t B;
    uint32_t C;
    std::vector<Operand> sequence;
    uint8_t instruction_ptr;
    std::string output;

    void adv(uint32_t combo)
    {
      std::cout << "ADV: " << combo << std::endl;
      double result = pow(2, combo);
      result = A / result;

      A = static_cast<uint32_t>(std::floor(result));
    }

    void bxl(uint32_t combo)
    {
      std::cout << "BXL: " << combo << std::endl;
      B ^= combo;
    }

    void bst(uint32_t combo)
    {
      std::cout << "BST: " << combo << std::endl;
      B &= 0x07;
    }
    
    bool jnz(uint32_t combo)
    {
      std::cout << "JNZ: " << combo << std::endl;
      if(A != 0)
      {
	instruction_ptr = combo;
	return false;
      }
      return true;
    }

    void bxc()
    {
      std::cout << "BXC" << std::endl;
      B ^= C;
    }

    uint8_t out(uint32_t combo)
    {
      std::cout << "OUT: " << combo << std::endl;
      Operand result;
      result.op = combo & 0x07;
      return result.op;
    }

    void bdv(uint32_t combo)
    {
      std::cout << "BDV: " << combo << std::endl;
      double result = pow(2, combo);
      result = A / result;

      B = static_cast<uint32_t>(std::floor(result));
    }

    void cdv(uint32_t combo)
    {
      std::cout << "CDV: " << combo << std::endl;
      double result = pow(2, combo);
      result = A / result;

      C = static_cast<uint32_t>(std::floor(result));
    }
    
  public:

    Computer(uint32_t _A, uint32_t _B, uint32_t _C, std::string program):A{_A}, B{_B}, C{_C}, instruction_ptr{0}
    {
      for(auto c : program)
      {
	if(c != ',')
	{
	  uint8_t op = (uint8_t)c - 0x30;
	  sequence.push_back(Operand{op});
	}
      }
      for(auto o : sequence)
      {
//	std::cout << (uint32_t)o.op << ","; 
      }
//      std::cout << std::endl;
    }

  void print_output()
  {
    std::cout << output << std::endl;
  }

  void tick()
  {
    if(instruction_ptr < sequence.size())
    {
      uint32_t combo{sequence.at(instruction_ptr+1).op};
      if(combo == 4)
      {
	combo = A;
      }
      else if(combo == 5)
      {
	combo = B;
      }
      else if(combo == 6)
      {
	combo = C;
      }
      else if(combo == 7)
      {
	std::cout << "Invalid combo operand\n";
      }
      
      bool increment_ptr = true;
      switch(sequence.at(instruction_ptr).op)
      {
	case 0:
	  adv(combo);
	break;
	case 1:
	  bxl(combo);
//	  if(combo > 3)
//	    std::cout << "Invalid combo for bxl: " << combo << std::endl;
	break;
	case 2:
	  bst(combo);
	break;
	case 3:
	  increment_ptr = jnz(combo);
	  if(combo > 3)
	    std::cout << "Invalid combo for jnz: " << combo << std::endl;
	break;
	case 4:
	  bxc();
	break;
	case 5:
	  if(output != "")
	    output += ",";
	  output += std::to_string(out(combo));	  
	break;
	case 6:
	  bdv(combo);
	break;
	case 7:
	  cdv(combo);
	break;
      }
      if(increment_ptr)
	instruction_ptr += 2;
    } 
  }

  void run()
  {
    while(instruction_ptr < sequence.size())
    {
      std::cout << "Instruction ptr: " << (uint32_t)instruction_ptr << std::endl;
      tick();
    }

    print_output();
  }
};

