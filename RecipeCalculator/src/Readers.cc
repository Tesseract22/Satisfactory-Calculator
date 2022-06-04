#include "Readers.hpp"
#include "Recipe.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
std::vector<std::string> SplitInAndOut(const std::string& str) {
  std::vector<std::string> results;
  std::string result;
  bool record = false;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == '{') {
      record = true;
      continue;
    }
    if (str.at(i) == '}') {
      record = false;
      results.push_back(result);
      result = "";
      continue;
    }
    if (record) {
      result += str.at(i);
    }
  }
  return results;
}

std::pair<std::string, float> ReadDict(std::string str) {
  bool str_record = false;
  std::string name;
  int num_start = 0;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == '\"') {
      str_record = !str_record ? true : false;
      continue;
    }
    if (str_record) name += str.at(i);
    if (str.at(i) == ':') num_start = i + 2;
  }
  float num = std::stof(str.substr(num_start, str.length()));
  return std::make_pair(name, num);
}
std::vector<std::string> Split(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter || str.at(i) == '\r') {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }

  if (last != str.size()) {
    std::string substr = str.substr(last, str.length() - last);
    substrs.push_back(substr);
  }

  return substrs;
}

map<string, pair<vector<Recipe>, vector<Recipe>>> ToRecipeMap(const string& recipe_path, const set<string>& items) {
  map<string, pair<vector<Recipe>, vector<Recipe>>> result; // map a string to two lists of recipes
  set<string>::const_iterator iter;
  for (iter = items.cbegin(); iter != items.cend(); ++iter) {
    result.insert(make_pair(*iter, pair<vector<Recipe>, vector<Recipe>>())); // map items to empty 
  }
  ifstream ifs{recipe_path};
  for (std::string line; getline(ifs, line); line = "") { // every line correspond to one recipe
    vector<string> splited = SplitInAndOut(line);
    vector<string> input_items_r = Split(splited.at(0), ',');
    vector<string> output_items_r = Split(splited.at(1), ',');
    list<string> input_items; // list of output/input items, not directly related to the construction of map,
    list<string> output_items; // but related to the adj_
    map<string, float> input; // the fianl result, mapping item name to int vals
    map<string, float> output;
    // assume the name is already in result
    for (string item : input_items_r) {
      auto i = ReadDict(item);
      input.insert(i);
      input_items.push_back(i.first);
    }
    for (string item : output_items_r) {
      auto i = ReadDict(item);
      output.insert(i);
      output_items.push_back(i.first);
    }
    if (input == output) continue;
    Recipe recipe{make_pair(input, output)};
    for (auto i : input_items) {
      try {
      result.at(i).first.push_back(recipe);
      } catch (std::out_of_range e) {
        std::cout << "Error: item " << i << " not in item_list" << std::endl;
      }
    }
    for (auto i : output_items) {
      try {
      result.at(i).second.push_back(recipe);
      } catch (std::out_of_range e) {
        std::cout << "Error: item " << i << " not in item_list" << std::endl;
      }
    }
    
  }
  return result;
}

set<string> ReadItems(const string& path) {
  set<string> result;
  ifstream ifs(path);
  for (std::string line; getline(ifs, line); line = "") {
    vector<string> v = Split(line, ',');
    set<string> s {v.cbegin(), v.cend()};
    result.insert(s.cbegin(), s.cend());
  }
  return result;
}