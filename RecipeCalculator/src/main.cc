
#include "Readers.hpp"
#include "Recipe.hpp"
#include "Satisfactory.hpp"
#include <iostream>

int main() {
    using namespace std;
    string KItemPath = "local/item_list.txt";
    string KRecipePath = "local/recipe_parsed.txt";
    Satisfactory s{KItemPath, KRecipePath};
    // auto l = SplitInAndOut("{\"Iron Ore\": 2.0, \"Copper Ore\": 2.0},{\"Iron Ingot\": 5.0}");
    // auto a = Split(l.at(0), ',')[0];
    // cout << a << endl;
    // auto d = ReadDict(a);
    // cout << d.first << endl;
    // for (auto i : s.GetStartItems()) cout << i << endl;
    // s.OrderHelper("Copper Ingot");
    for (auto i : Sort(s.GetItemOrders())) {
        cout << i.first << " " << i.second << endl;
        // if (i.second == 9) cout << i.first << endl;
    }
}