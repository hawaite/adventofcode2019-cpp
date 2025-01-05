#include <fstream>
#include <iostream>
#include <vector>

class IntCodeMachine {
 private:
  std::vector<int> memory;
  int ip;

 public:
  IntCodeMachine(std::vector<int> initial_memory, int initial_ip) {
    memory = initial_memory;
    ip = initial_ip;
  }

  bool exec();
  int get_memory(int address) { return memory[address]; }
  void set_memory(int address, int value) { memory[address] = value; }
  std::string render_memory() {
    std::string buf;
    for (int i = 0; i < memory.size(); i++) {
      buf += std::to_string(memory[i]);
      buf += ", ";
    }
    return buf.substr(0, buf.size() - 2);
  }
};

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