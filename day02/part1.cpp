#include <fstream>
#include <iostream>
#include <vector>
#include "intcode.hpp"

int main() {
  std::ifstream inputFile("./input.txt");
  int total = 0;
  std::vector<int> init_memory;
  std::string complete_input;

  // concat all lines
  if (inputFile.is_open()) {
    std::string str_buffer;
    while (std::getline(inputFile, str_buffer)) {
      complete_input.append(str_buffer);
    }
  }

  // string split on commas
  // adding trailing comma just makes parsing slightly easier
  complete_input += ',';
  std::string num_buffer;
  for (int i = 0; i < complete_input.size(); i++) {
    if (complete_input[i] == ',') {
      init_memory.push_back(std::stoi(num_buffer));
      num_buffer = "";
    } else {
      num_buffer += complete_input[i];
    }
  }
  std::cout << std::endl;

  IntCodeMachine machine(init_memory, 0);

  // initial messing with the memory
  machine.set_memory(1, 12);
  machine.set_memory(2, 2);

  // exec until halted
  while (!machine.exec());

  std::cout << "final value in address 0: " << machine.get_memory(0)
            << std::endl;

  return 0;
}