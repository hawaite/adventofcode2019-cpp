#include <limits.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

struct point {
  int col, row;

  bool operator==(const point& other) const {
    return (col == other.col && row == other.row);
  }

  bool operator<(const point& other) const {
    if (col != other.col) {
      return col < other.col;
    }
    return row < other.row;
  }
};

int manhattan_distance(point p1, point p2) {
  return abs(p1.col - p2.col) + abs(p1.row - p2.row);
}
point command_to_direction(char command) {
  switch (command) {
    case 'R': {
      return {1, 0};
    }
    case 'L': {
      return {-1, 0};
    }
    case 'U': {
      return {0, -1};
    }
    case 'D': {
      return {0, 1};
    }
    default: {
      return {0, 0};
    }
  }
}

std::set<point> expand_wire_to_point_set(std::string wire_def) {
  std::set<point> seen_points;
  point current = {0, 0};
  seen_points.insert(current);

  wire_def += ',';
  std::string command_buffer;
  for (int i = 0; i < wire_def.size(); i++) {
    if (wire_def[i] == ',') {
      char command = command_buffer[0];
      int magnitude = std::stoi(command_buffer.substr(1));

      // we hit a comma, action this segment by expanding it to points and
      // adding them to the set
      point dir = command_to_direction(command);
      for (int j = 0; j < magnitude; j++) {
        current = {current.col + dir.col, current.row + dir.row};
        seen_points.insert(current);
      }

      command_buffer = "";
    } else {
      command_buffer += wire_def[i];
    }
  }
  return seen_points;
}

int main() {
  std::ifstream inputFile("./input.txt");
  int total = 0;
  std::string first_wire_def;
  std::string second_wire_def;
  if (inputFile.is_open()) {
    std::string str_buffer;

    while (std::getline(inputFile, str_buffer)) {
      if (first_wire_def == "") {
        first_wire_def = str_buffer;
      } else {
        second_wire_def = str_buffer;
      }
    }
  }

  std::set<point> wire_one_point_set = expand_wire_to_point_set(first_wire_def);
  wire_one_point_set.erase({0, 0});

  std::set<point> wire_two_point_set =
      expand_wire_to_point_set(second_wire_def);
  wire_two_point_set.erase({0, 0});

  std::vector<point> output_set;

  // set intersection lets us get points which exist on both wires
  std::set_intersection(wire_one_point_set.begin(), wire_one_point_set.end(),
                        wire_two_point_set.begin(), wire_two_point_set.end(),
                        std::back_inserter(output_set));

  int minimum = INT_MAX;
  for (point p : output_set) {
    int dist_from_center = manhattan_distance({0, 0}, p);

    if (dist_from_center < minimum) {
      minimum = dist_from_center;
    }
  }

  std::cout << "minimum distance to a crossing point: " << minimum << std::endl;
  return 0;
}