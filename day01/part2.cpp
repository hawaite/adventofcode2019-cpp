#include <fstream>
#include <iostream>

int calc_fuel(int mass) {
  int fuel = mass / 3;
  fuel -= 2;
  if (fuel <= 0) return 0;

  return fuel + calc_fuel(fuel);
}

int main() {
  std::ifstream inputFile("./input.txt");
  int total = 0;
  if (inputFile.is_open()) {
    std::string str_buffer;

    while (std::getline(inputFile, str_buffer)) {
      total += calc_fuel(std::stoi(str_buffer));
    }
  }

  std::cout << "total: " << total << std::endl;
  return 0;
}