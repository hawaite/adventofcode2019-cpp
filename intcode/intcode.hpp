#include <vector>
#include <string>

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