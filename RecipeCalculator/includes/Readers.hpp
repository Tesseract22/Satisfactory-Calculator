#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <list>
#include "Recipe.hpp"
#include <set>
std::vector<std::string> SplitInAndOut(const std::string& str);
std::vector<std::string> Split(const std::string& str, char delimiter);
std::pair<std::string, float> ReadDict(std::string line);
map<string, pair<vector<Recipe>, vector<Recipe>>> ToRecipeMap(const string& recipe_path, const set<string>& items);
set<string> ReadItems(const string& path);
#endif