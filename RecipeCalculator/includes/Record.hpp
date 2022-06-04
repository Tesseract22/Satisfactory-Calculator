#ifndef RECORD_HPP
#define RECORD_HPP

#include "Recipe.hpp"
class Record {
public:
    Record() = default;
    Record(Recipe* recipe, string item, double multiple);

private:
    Recipe* recipe_;
    string item_;
    double multiple_ = 0;
    
};

#endif