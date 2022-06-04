#include "Satisfactory.hpp"
#include "Readers.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;
set<string> cyclic_list = {"Empty Canister", "Packaged Water"};
Satisfactory::Satisfactory(const string& item_path, const string& recipe_path): 
    items_0_(ReadItems("local/item_0.text")),items_(ReadItems(item_path)), adj_(ToRecipeMap(recipe_path, items_)) {
    set<string>::const_iterator start_iter;
    for (string item : items_0_) {
        item_order_.insert(make_pair(item, 0));
    }
    for (string item : items_) {
        OrderHelper(item);
    }
    
}

int Satisfactory::OrderHelper(string item) {
    // cout << item << endl;
    if (items_.find(item) == items_.cend()) return 0;
    if (item_order_.find(item) != item_order_.cend() && item_order_.at(item) != -1) {
        // cout << item << " " << item_order_.at(item) << endl;
        return item_order_.at(item);
    }
    item_order_.insert(make_pair(item, 0));

    vector<Recipe>::const_iterator iter;
    vector<Recipe> child_recipes = adj_.at(item).second;
    for (iter = child_recipes.cbegin(); iter != child_recipes.cend(); ++iter) {
        map<string, float>::const_iterator iter_r;
        for (iter_r = iter->recipe_.first.cbegin(); iter_r != iter->recipe_.first.cend(); ++iter_r) {
            int order = OrderHelper(iter_r->first) + 1;
            if (order > item_order_.at(item)) item_order_.at(item) = order;
        }
    }
    // cout << item << " " << item_order_.at(item) << endl;
    return item_order_.at(item);
}


set<pair<string, int>, comp> Sort(map<string, int>& m) {
    return set<pair<string, int>, comp>(m.cbegin(), m.cend());
}
