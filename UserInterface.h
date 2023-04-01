
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <vector>
#include "DSAVLTree.h"
using namespace std;

class UserInterface {


private:


public:
    UserInterface();

    void printUI(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo);

};


#endif