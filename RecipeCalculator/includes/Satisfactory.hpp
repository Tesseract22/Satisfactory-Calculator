#ifndef SATISFACTORY_HPP
#define SATISFACTORY_HPP



#include <Recipe.hpp>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "func.hpp"
#include "Record.hpp"
#include "Precription.hpp"
#include <list>
using namespace std;
class Satisfactory {
    public:
        Satisfactory() = default;
        Satisfactory(const string& item_path, const string& recipe_path);
        pair<vector<Recipe>, vector<Recipe>> GetRecipeList(const string& item) const { return adj_.at(item); }
        set<string> GetStartItems() { return items_0_; }
        set<string> GetItems() { return items_; }
        map<string, int> GetItemOrders() { return item_order_; }
        int OrderHelper(string item);
        friend set<pair<string, int>, comp> Sort(map<string, int>& m);
        
        void Add(string prscrp, string item, double amount) { prscrps_.at(prscrp).Add(item, amount); }
        void Produce(string prscrp, string item, double amount);

    private:
        
        set<string> items_0_;
        set<string> items_;
        map<string, pair<vector<Recipe>, vector<Recipe>>> adj_;
        // first correspond to recipe that takes item as input, second corrsepond to recipe that takes item as output
        map<string, int> item_order_;
        map<string, Prescription> prscrps_;

        
};







#endif