


#ifndef FILE_PARSER_H
#define FILE_PARSER_H
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "DSAVLTree.h"
using namespace std;

class File_Parser {

private:

    

    vector<string> filePaths;
    
    vector<string> stopWords;

    unordered_map<string, int> wordIndex;
    unordered_set<string> wordKey;

    unordered_map<string, int> personNodeData;
    avlnode<unordered_map<string, int>>* personNodeTemp = NULL;

    unordered_map<string, int> orgNodeData;
    avlnode<unordered_map<string, int>>* orgNodeTemp = NULL;

    unordered_map<string, int> searchNodeData;
    avlnode<unordered_map<string, int>>* searchNodeTemp = NULL;
    

    // avl_tree<unordered_map<string, int>> persistenceIndexSearch;
    // avl_tree<unordered_map<string, int>> persistenceIndexPerson;
    // avl_tree<unordered_map<string, int>> persistenceIndexOrg;

public:
    File_Parser();

    void CheckTree(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, vector<pair<char, string>>);

    void CreateIndex(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string directory);

    vector<pair<string,int>> getData(avlnode<unordered_map<string,int>>* node, string searchVal);

    void fillStopWords(string);

    void fillPersistenceIndex(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string);

    void readPersistenceIndex(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string);

};

#endif