#ifndef SOCIAL_NETWORK_H
#define SOCIAL_NETWORK_H

#include "Person.h"
#include <map>
#include <string>

class SocialNetwork {
private:
    std::map<int, Person> people;
    int nextId = 1;
    const std::string dataFile = "social_network_data.txt";

    void saveData();
    void loadData();
    bool personExists(int id);
    bool isAlreadyFriends(int id1, int id2);

public:
    SocialNetwork();
    ~SocialNetwork();

    void addPerson();
    void addFriendship();
    void findPath();
    void findGroup();
    void listPeople();
};

#endif // SOCIAL_NETWORK_H