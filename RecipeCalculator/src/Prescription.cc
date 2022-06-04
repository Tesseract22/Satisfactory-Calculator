#include "Precription.hpp"

Prescription::~Prescription() {
    for (auto r : records_) {
        delete r;
    }
}


Prescription::Prescription(string path) {
    
}

void Prescription::Add(string item, double amount) {
    records_.push_back(new Record(nullptr, item, amount));
    net_out_.insert(make_pair(item, amount));
}

void Prescription::Produce(string item, double amount, Recipe recipe) {
    double mul  = amount / recipe.recipe_.second.at(item);
    records_.push_back(new Record(&recipe, item, mul));
    for (auto i : recipe.recipe_.second) {
        net_out_.insert(make_pair(i.first, mul * i.second));
    }
    for (auto i : recipe.recipe_.first) {
        net_in_.insert(make_pair(i.first, mul * i.second));
    }
}