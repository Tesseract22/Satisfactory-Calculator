#ifndef RECIPE_HPP
#define RECIPE_HPP
#include <string>
#include <map>

using namespace std;
struct Recipe {
    pair<map<string, float>, map<string, float>> recipe_;
};
#endif