
#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <string>
#include <vector>
#include "../porter2stemmer/porter2_stemmer.h"
#include "DSAVLTree.h"
using namespace std;

class Query_Parser {


private:

    vector<pair<char, string>> mainQuery;

public:
    Query_Parser();

    void ReadQuery(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string&);

    vector<pair<char, string>> GetQuery();

    void PrintQuery();

};


#endif
