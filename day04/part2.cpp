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

bool digits_contain_a_strict_double(int digits) {
  std::string digit_string = std::to_string(digits);
  std::string group_buffer = "X";

  for (int i = 0; i < digit_string.size(); i++) {
    if (digit_string[i] == group_buffer[0]) {
      // this is another part of the same group
      group_buffer += digit_string[i];
    } else {
      // this digit is different to whats in the buffer, signaling a new group
      // handle the group in the buffer,
      if (group_buffer.length() == 2) {
        // this was a group which ended after 2 characters
        return true;
      }
      // if we didnt leave the function then set the buffer to the new group and
      // continue
      group_buffer = std::string{digit_string[i]};
    }
  }

  // need one last check because the last digit may be involved in a 2 digit
  // group
  if (group_buffer.length() == 2) {
    return true;
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

  // for (int i = 100; i < 300; i++) {
  // 965 too low
  for (int i = lower_bound; i < upper_bound; i++) {
    if (digits_increasing(i) && digits_contain_a_strict_double(i)) {
      total += 1;
    }
  }

  std::cout << "total: " << total << std::endl;
  return 0;
}