#include "SocialNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

SocialNetwork::SocialNetwork() {
    loadData();
}

SocialNetwork::~SocialNetwork() {
    saveData();
}

void SocialNetwork::saveData() {
    ofstream outFile(dataFile);
    if (!outFile) {
        cerr << "Error saving data to file!" << endl;
        return;
    }

    outFile << people.size() << endl;

    for (const auto& [id, person] : people) {
        outFile << person.id << endl;
        outFile << person.name << endl;
        outFile << person.interests.size() << endl;
        for (const string& interest : person.interests)
            outFile << interest << endl;

        outFile << person.friends.size() << endl;
        for (int friendId : person.friends)
            outFile << friendId << endl;
    }
    outFile.close();
}

void SocialNetwork::loadData() {
    ifstream inFile(dataFile);
    if (!inFile) return;

    int personCount;
    inFile >> personCount;
    inFile.ignore();

    for (int i = 0; i < personCount; ++i) {
        Person p;
        inFile >> p.id;
        inFile.ignore();
        getline(inFile, p.name);

        int interestCount;
        inFile >> interestCount;
        inFile.ignore();
        for (int j = 0; j < interestCount; ++j) {
            string interest;
            getline(inFile, interest);
            p.interests.push_back(interest);
        }

        int friendCount;
        inFile >> friendCount;
        inFile.ignore();
        for (int j = 0; j < friendCount; ++j) {
            int friendId;
            inFile >> friendId;
            inFile.ignore();
            p.friends.push_back(friendId);
        }

        people[p.id] = p;
    }

    if (!people.empty())
        nextId = people.rbegin()->first + 1;

    inFile.close();
}

void SocialNetwork::addPerson() {
    Person p;
    p.id = nextId++;

    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Enter interests (comma-separated): ";
    string input;
    getline(cin, input);

    size_t pos = 0;
    while ((pos = input.find(',')) != string::npos) {
        string interest = input.substr(0, pos);
        p.interests.push_back(trim(interest));
        input.erase(0, pos + 1);
    }
    p.interests.push_back(trim(input));

    people[p.id] = p;
    cout << "Added new person with ID: " << p.id << endl;
}

string SocialNetwork::trim(const string& s) {
    size_t first = s.find_first_not_of(' ');
    if (string::npos == first)
        return "";
    size_t last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

void SocialNetwork::addFriendship() {
    if (people.size() < 2) {
        cout << "Need at least 2 people to connect." << endl;
        return;
    }

    listPeople();

    int id1, id2;
    cout << "Enter first person's ID: ";
    cin >> id1;
    cout << "Enter second person's ID: ";
    cin >> id2;

    if (!personExists(id1) || !personExists(id2)) {
        cout << "Invalid ID(s)." << endl;
        return;
    }

    if (isAlreadyFriends(id1, id2)) {
        cout << "These individuals are already friends." << endl;
        return;
    }

    people[id1].friends.push_back(id2);
    people[id2].friends.push_back(id1);
    cout << people[id1].name << " and " << people[id2].name << " are now connected." << endl;
}

bool SocialNetwork::isAlreadyFriends(int id1, int id2) {
    const vector<int>& friends = people[id1].friends;
    return find(friends.begin(), friends.end(), id2) != friends.end();
}

bool SocialNetwork::personExists(int id) {
    return people.find(id) != people.end();
}

void SocialNetwork::findPath() {
    if (people.size() < 2) {
        cout << "Need at least 2 people to find a path." << endl;
        return;
    }

    listPeople();

    int start, end;
    cout << "Enter starting person ID: ";
    cin >> start;
    cout << "Enter ending person ID: ";
    cin >> end;

    if (!personExists(start) || !personExists(end)) {
        cout << "Invalid ID(s)." << endl;
        return;
    }

    queue<int> q;
    map<int, int> parent;
    set<int> visited;

    q.push(start);
    visited.insert(start);
    parent[start] = -1;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        if (current == end) break;

        for (int friendId : people[current].friends) {
            if (!visited.count(friendId)) {
                visited.insert(friendId);
                parent[friendId] = current;
                q.push(friendId);
            }
        }
    }

    if (parent.find(end) == parent.end()) {
        cout << "No path exists between these people." << endl;
        return;
    }

    vector<int> path;
    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);
    reverse(path.begin(), path.end());

    cout << "Connection path (" << path.size() - 1 << " steps):" << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << people[path[i]].name;
    }
    cout << endl;
}

void SocialNetwork::findGroup() {
    if (people.empty()) {
        cout << "No people have been added yet." << endl;
        return;
    }

    listPeople();
    int start;
    string interest;
    cout << "Enter starting person ID: ";
    cin >> start;
    cout << "Enter an interest to search for: ";
    cin.ignore();
    getline(cin, interest);

    if (!personExists(start)) {
        cout << "Invalid ID." << endl;
        return;
    }

    stack<int> dfsStack;
    set<int> visited, group;

    dfsStack.push(start);
    visited.insert(start);

    while (!dfsStack.empty()) {
        int current = dfsStack.top(); dfsStack.pop();

        for (const string& i : people[current].interests) {
            if (i == interest) {
                group.insert(current);
                break;
            }
        }

        for (int friendId : people[current].friends) {
            if (!visited.count(friendId)) {
                visited.insert(friendId);
                dfsStack.push(friendId);
            }
        }
    }

    if (group.empty()) {
        cout << "No one shares that interest in the network." << endl;
        return;
    }

    cout << "People interested in "" << interest << "":" << endl;
    for (int id : group)
        cout << "- " << people[id].name << endl;
}

void SocialNetwork::listPeople() {
    if (people.empty()) {
        cout << "No people have been added yet." << endl;
        return;
    }

    cout << "
List of people in the network:" << endl;
    for (auto& [id, person] : people) {
        cout << id << ": " << person.name << " | Friends: ";
        if (person.friends.empty()) cout << "None";
        else for (int fid : person.friends) cout << people[fid].name << " ";
        cout << endl;
    }
}
