#include "intcode.hpp"

bool IntCodeMachine::exec() {
  // returns true if is halted
  switch (memory[ip]) {
    case 99:
      return true;
    case 1:  // add
    {
      int src_one_addr = memory[ip + 1];
      int src_two_addr = memory[ip + 2];
      int dest_addr = memory[ip + 3];
      memory[dest_addr] = memory[src_one_addr] + memory[src_two_addr];
      ip += 4;
      return false;
    }
    case 2:  // mult
    {
      int src_one_addr = memory[ip + 1];
      int src_two_addr = memory[ip + 2];
      int dest_addr = memory[ip + 3];
      memory[dest_addr] = memory[src_one_addr] * memory[src_two_addr];
      ip += 4;
      return false;
    }
  }

  return false;
}