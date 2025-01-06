#include <limits.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
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

  std::string to_string() {
    std::stringstream key;
    key << "(" << col << "," << row << ")";
    return key.str();
  }
};

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

void expand_wire_to_point_set(std::string wire_def,
                              std::set<point>* seen_points,
                              std::map<std::string, int>* wire_distance_map) {
  point current = {0, 0};
  seen_points->insert(current);

  wire_def += ',';
  std::string command_buffer;
  int moves = 1;
  for (int i = 0; i < wire_def.size(); i++) {
    if (wire_def[i] == ',') {
      char command = command_buffer[0];
      int magnitude = std::stoi(command_buffer.substr(1));

      // we hit a comma, action this segment by expanding it to points and
      // adding them to the set
      point dir = command_to_direction(command);
      for (int j = 0; j < magnitude; j++) {
        current = {current.col + dir.col, current.row + dir.row};
        seen_points->insert(current);
        std::string key_str = current.to_string();

        auto found = wire_distance_map->find(key_str);
        if (found == wire_distance_map->end()) {
          // key was not in map. Only care about first time we see this point.
          wire_distance_map->insert({key_str, moves});
        }

        moves++;
      }

      command_buffer = "";
    } else {
      command_buffer += wire_def[i];
    }
  }
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

  std::set<point> wire_one_point_set;
  std::map<std::string, int> wire_one_distance_map;
  expand_wire_to_point_set(first_wire_def, &wire_one_point_set,
                           &wire_one_distance_map);
  wire_one_point_set.erase({0, 0});

  std::set<point> wire_two_point_set;
  std::map<std::string, int> wire_two_distance_map;
  expand_wire_to_point_set(second_wire_def, &wire_two_point_set,
                           &wire_two_distance_map);
  wire_two_point_set.erase({0, 0});

  std::vector<point> output_set;
  std::set_intersection(wire_one_point_set.begin(), wire_one_point_set.end(),
                        wire_two_point_set.begin(), wire_two_point_set.end(),
                        std::back_inserter(output_set));

  int minimum = INT_MAX;
  for (point p : output_set) {
    std::string key_str = p.to_string();

    int wire_one_dist = (*wire_one_distance_map.find(key_str)).second;
    int wire_two_dist = (*wire_two_distance_map.find(key_str)).second;

    if (wire_one_dist + wire_two_dist < minimum) {
      minimum = wire_one_dist + wire_two_dist;
    }
  }

  std::cout << "minimum combined distance to a crossing point: " << minimum
            << std::endl;

  return 0;
}