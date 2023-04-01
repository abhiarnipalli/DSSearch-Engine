#include <iostream>
#include <string>
#include "UserInterface.h"
#include "DSAVLTree.h"
//final

using namespace std;

avl_tree<unordered_map<string, int>> persistenceIndexSearch;
avl_tree<unordered_map<string, int>> persistenceIndexPerson;
avl_tree<unordered_map<string, int>> persistenceIndexOrg;
vector<pair<string, vector<string>>> extraInfo;

int main(){


    UserInterface ui;

    ui.printUI(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo);

    // string query = "";

    // cout << "Enter your search: ";

    // getline(cin, query);

    // Query_Parser qp;

    // qp.ReadQuery(query);

    // qp.PrintQuery();

}