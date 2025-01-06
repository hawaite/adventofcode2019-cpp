#include <fstream>
#include <iostream>

bool digits_increasing(int digits) {
  std::string digit_string = std::to_string(digits);
  for (int i = 0; i < digit_string.size() - 1; i++) {
    // ascii values of digits are the same as the digit values themselves
    if (digit_string[i + 1] < digit_string[i]) {
      return false;
    }
  }
  return true;
}

bool digits_contain_a_double(int digits) {
  std::string digit_string = std::to_string(digits);

  for (int i = 0; i < digit_string.size() - 1; i++) {
    if (digit_string[i] == digit_string[i + 1]) {
      return true;
    }
  }

  return false;
}

int main() {
  std::ifstream inputFile("./input.txt");
  int total = 0;
  std::string str_buffer;
  if (inputFile.is_open()) {
    std::getline(inputFile, str_buffer);
  }

  str_buffer += '-';
  int lower_bound = 0;
  int upper_bound = 0;
  std::string bound_buffer;
  for (int i = 0; i < str_buffer.size(); i++) {
    if (str_buffer[i] == '-') {
      if (lower_bound == 0) {
        lower_bound = std::stoi(bound_buffer);
      } else {
        upper_bound = std::stoi(bound_buffer);
      }
      bound_buffer = "";
    } else {
      bound_buffer += str_buffer[i];
    }
  }

  for (int i = lower_bound; i < upper_bound; i++) {
    if (digits_increasing(i) && digits_contain_a_double(i)) {
      total += 1;
    }
  }

  std::cout << "total: " << total << std::endl;
  return 0;
}