#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

struct Person {
    int id;
    std::string name;
    std::vector<std::string> interests;
    std::vector<int> friends;
};

#endif
