#ifndef PRESCRIPTION_HPP
#define PRESCRIPTION_HPP

#include <string>
#include <map>
#include "Record.hpp"
#include <list>
using namespace std;

class Prescription {
public:
    Prescription() = default;
    Prescription(string path);
    void Add(string item, double amount);
    void Produce(string item, double amount, Recipe recipe);
    void Save(string path);
    ~Prescription();
private:
    list<Record*> records_;
    map<string, int> net_out_;
    map<string, int> net_in_;
                
};

#endif