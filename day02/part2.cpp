#include <fstream>
#include <iostream>
#include <vector>
#include "intcode.hpp"

std::string zero_padded(int val) {
  std::string val_str = std::to_string(val);
  if (val_str.size() == 1) {
    val_str = "0" + val_str;
  }
  return val_str;
}

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

  const int target = 19690720;
  for (int noun = 0; noun < 100; noun++) {
    for (int verb = 0; verb < 100; verb++) {
      IntCodeMachine machine(init_memory, 0);
      machine.set_memory(1, noun);
      machine.set_memory(2, verb);
      // exec until halted
      while (!machine.exec());
      if (machine.get_memory(0) == target) {
        std::cout << "Found pair. Noun: " << noun << ", Verb: " << verb
                  << ", result: " << zero_padded(noun) << zero_padded(verb)
                  << std::endl;
      }
    }
  }

  return 0;
}