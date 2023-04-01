
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include "UserInterface.h"
#include "Query_Parser.h"
#include "File_Parser.h"

using namespace std;

UserInterface::UserInterface(){}

void UserInterface::printUI(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo){

    File_Parser fp;
    Query_Parser qp;
    
    cout << "Welcome to Super Search" << endl;
    cout << "Select an Option Below" << endl;
    cout << "   1 - Create an index from a directory with documents " << endl;
    cout << "   2 - Write the index to a file" << endl;
    cout << "   3 - Read an index from a file" << endl;
    cout << "   4 - Enter a query" << endl;
    cout << "   5 - Exit" << endl;

    int input;
    cin >> input;

    if (input == 1){
        string directory = "";
        cout << endl << "Enter the path of the directory: ";
        getline(cin >> ws, directory);
        fp.fillStopWords("../stopwords.txt");
        fp.CreateIndex(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, directory);
        // fp.CreateIndex("/mnt/c/Users/bensa/Documents/JsonStorage/tempArchive");
        // fp.CreateIndex(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, "../sample_data/coll_1");
        cout << "Index Created" << endl << endl;
        printUI(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo);
    }
    else if (input == 2){
        string filePath = "";
        cout << endl << "Enter the file path: ";
        getline(cin >> ws, filePath);
        fp.fillPersistenceIndex(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, filePath);
        // fp.fillPersistenceIndex(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, "../persistencetest.txt");
        cout << "Persistence Index Written" << endl << endl;
        printUI(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo);
    }
    else if (input == 3){
        string filePath = "";
        cout << endl << "Enter the file path";
        getline(cin >> ws, filePath);
        fp.readPersistenceIndex(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, filePath);
        // fp.readPersistenceIndex(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, "../persistence2.txt");
        cout << "Persistence Index Read" << endl << endl;
        printUI(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo);
    }
    else if (input == 4){
        cin.clear();
        string query = "";
        cout << endl << "Enter your search: ";
        getline(cin >> ws, query);
        query += " ";
        qp.ReadQuery(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, query);
        printUI(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo);
        // qp.PrintQuery();
    }
    else if (input == 5){
    }
    else {
        cout << "Invalid Input, please try again" << endl;
        printUI(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo);
    }
}