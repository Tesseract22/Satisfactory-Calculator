#ifndef FUNC_HPP
#define FUNC_HPP

#include "Satisfactory.hpp"
#include <set>
#include <map>
using namespace std;
 // namespace std;

struct comp {
    template <typename T>
  
    // Comparator function
    bool operator()(const T& l,
                    const T& r) const
    {
        if (l.second != r.second) {
            return l.second < r.second;
        }
        return l.first < r.first;
    }
};

// set<pair<string, int>, comp> Sort(map<string, int>& m) {
//     return set<pair<string, int>, comp>(m.cbegin(), m.cend());
// }
#endif