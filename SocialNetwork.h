#ifndef SOCIAL_NETWORK_H
#define SOCIAL_NETWORK_H

#include "Person.h"
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <vector>

class SocialNetwork {
private:
    std::map<int, Person> people;
    int nextId = 1;
    const std::string dataFile = "social_network_data.txt";

    void saveData();
    void loadData();
    std::string trim(const std::string& s);
    bool isAlreadyFriends(int id1, int id2);
    bool personExists(int id);

public:
    SocialNetwork();
    ~SocialNetwork();

    void addPerson();
    void addFriendship();
    void findPath();
    void findGroup();
    void listPeople();
};

#endif
