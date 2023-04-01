
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Query_Parser.h"
#include "File_Parser.h"

using namespace std;

Query_Parser::Query_Parser(){}

void Query_Parser::ReadQuery(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string& query){
    string temp = "";
    bool openOrg = false;
    bool openPer = false;
    bool openNotOrg = false;
    bool openNotPer = false;

    for (size_t i = 0; i < query.length(); i++){
        // cout << query.at(i) << " " << query.length() << endl;
        if (temp == "ORG"){
            // cout << "Temp: " << temp << endl;
            openOrg = true;
            temp = "";
            i += 1;
        }
        else if (temp == "PERSON"){
            // cout << "Temp: " << temp << endl;
            openPer = true;
            temp = "";
            i += 1;
        }
        else if (temp == "-ORG"){
            // cout << "Temp: " << temp << endl;
            openNotOrg = true;
            temp = "";
            i += 1;
        }
        else if (temp == "-PERSON"){
            // cout << "Temp: " << temp << endl;
            openNotPer = true;
            temp = "";
            i += 1;
        }
        else if (query.at(i) == '-' && openOrg == false && openPer == false && openNotOrg == false && openNotPer == false){
            while(!isspace(query.at(i)) && i <= query.length()){
                temp += query.at(i);
                i++;
            }
            // cout << "TempCheck: " << temp << endl;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            Porter2Stemmer::stem(temp);
            mainQuery.push_back(make_pair('n', temp));
            temp = "";
        }
        else if(isspace(query.at(i)) && openOrg == false && openPer == false){
            // cout << "TempCheck: " << temp << endl;
            if(temp.find_first_not_of(' ') != string::npos){
                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                Porter2Stemmer::stem(temp);
                mainQuery.push_back(make_pair('w', temp));
            }
            temp = "";
        }
        else if (openNotOrg == true && query.at(i) == '>'){
            // cout << "TempCheck: " << temp << endl;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            Porter2Stemmer::stem(temp);
            mainQuery.push_back(make_pair('no', temp));
            temp = "";
            openOrg = false;
        }
        else if (openNotPer == true && query.at(i) == '>'){
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            Porter2Stemmer::stem(temp);
            mainQuery.push_back(make_pair('np', temp));
            temp = "";
            openOrg = false;
        }
        else if (openOrg == true && query.at(i) == '>'){
            // cout << "TempCheck: " << temp << endl;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            Porter2Stemmer::stem(temp);
            mainQuery.push_back(make_pair('o', temp));
            temp = "";
            openOrg = false;
        }
        else if (openPer == true && query.at(i) == '>'){
            // cout << "TempCheck: " << temp << endl;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            Porter2Stemmer::stem(temp);
            mainQuery.push_back(make_pair('p', temp));
            temp = "";
            openPer = false;
        }
        else {
            temp += query.at(i);
            // cout << "Temp: " << temp << " " << openOrg << " " << openPer << endl;
        }

    }



    File_Parser fp;

    // fp.GetFiles("../sample_data/coll_1");

    fp.CheckTree(persistenceIndexPerson, persistenceIndexOrg, persistenceIndexSearch, extraInfo, mainQuery);
    mainQuery.clear();


}

vector<pair<char, string>> Query_Parser::GetQuery(){
    return mainQuery;
}

void Query_Parser::PrintQuery(){
    for(auto & index : mainQuery){
        cout << index.first << ", " << index.second << endl;
    }
}