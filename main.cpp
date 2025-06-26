#include "SocialNetwork.h"
#include <iostream>

using namespace std;

int main() {
    SocialNetwork network;
    int choice;
    while (true) {
        cout << "\n=== Social Network Analysis ===\n";
        cout << "1. Add a person\n";
        cout << "2. Connect two people\n";
        cout << "3. Find connection path\n";
        cout << "4. Search for interest group\n";
        cout << "5. List all people\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        switch (choice) {
            case 1: network.addPerson(); break;
            case 2: network.addFriendship(); break;
            case 3: network.findPath(); break;
            case 4: network.findGroup(); break;
            case 5: network.listPeople(); break;
            case 6:
                cout << "Exiting... Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}