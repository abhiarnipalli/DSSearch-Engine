
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
#include <set>
#include <string>
#include <filesystem>
#include <list>
#include <math.h>
#include "File_Parser.h"
#include "../rapidjson/document.h"
#include "../porter2stemmer/porter2_stemmer.h"

using namespace std;

File_Parser::File_Parser(){}

void File_Parser::CheckTree(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, vector<pair<char, string>> search){
    if(persistenceIndexPerson.root == NULL && persistenceIndexOrg.root == NULL && persistenceIndexSearch.root == NULL){
        cout << "No tree loaded, please load a tree." << endl;
        return;
    }
    else {
        vector<vector<pair<string,int>>> allVects;
        vector<vector<pair<string,int>>> allNotVects;
        vector<pair<string, int>> finalResults;
        pair<string, int> tempPair;
        int total;
        
        for(pair<char, string> iter : search){
            // cout << "SEARCH: " << iter.first << " - " << iter.second << endl;
            avlnode<unordered_map<string, int>>* tempNode = NULL;
            if (iter.first == 'p'){
                tempNode = persistenceIndexPerson.search(persistenceIndexPerson.root, iter.second);
                if (tempNode == NULL){
                    cout << endl << "No results found for: " << iter.second << endl << endl;
                    return;
                }
                allVects.push_back(getData(tempNode, iter.second));
            }
            if (iter.first == 'o'){
                tempNode = persistenceIndexOrg.search(persistenceIndexOrg.root, iter.second);
                if (tempNode == NULL){
                    cout << endl << "No results found for: " << iter.second << endl << endl;
                    return;
                }
                allVects.push_back(getData(tempNode, iter.second));
            }
            if (iter.first == 'w'){
                tempNode = persistenceIndexSearch.search(persistenceIndexSearch.root, iter.second);
                if (tempNode == NULL){
                    cout << endl << "No results found for: " << iter.second << endl << endl;
                    return;
                }
                allVects.push_back(getData(tempNode, iter.second));
            }
        }
        
        if(allVects.size() > 1){
            int i = 0;
            total = 0;
            for(auto iter : allVects){
                for(auto it : iter){
                    // cout << "ITERATOR RES: " << it.first << " - " << it.second << endl;
                    if (i == 0){
                        total += it.second;
                        tempPair.first = it.first;
                        tempPair.second = it.second;
                        // cout << "TEMP - " << tempPair.first << " - " << tempPair.second << endl;
                    }
                    else {
                        // cout << "ELSE" << endl;
                        if(tempPair.first.compare(it.first) == 0){
                            // cout << "FINAL - " << it.first << " - " << it.second << endl;
                            finalResults.push_back(make_pair(it.first, (it.second + tempPair.second)));
                        }
                        tempPair.first = it.first;
                        tempPair.second = it.second;
                    }
                    i++;
                }
            }
            cout << endl;
            cout << "---- Results ----" << endl;
            sort(finalResults.begin(), finalResults.end(), [](auto &left, auto &right){ return left.second > right.second;});
            for (auto iterator : finalResults){
                int ind = 1;
                cout << ind << " - "<< iterator.first << " - ";
                string date = "";
                
                cout << iterator.second;
                for(auto infoIter : extraInfo){
                    if (infoIter.first.compare(iterator.first) == 0){
                        date = infoIter.second.at(1);
                        cout << " - Publish Date: " << date;
                    }    
                }
                cout << endl;
                string searchVal;
                cout << "Select a search: ";
                cin >> searchVal;

                int searchIndex = stoi(searchVal);
                pair<string, int> checkPair;

                checkPair = finalResults.at(searchIndex - 1);
                for(auto infoIter : extraInfo){
                    // cout << " - " << infoIter.first << endl;
                    if (infoIter.first.compare(checkPair.first) == 0){
                        string data = infoIter.second.at(0);
                        cout << "Text:" << endl << data;
                    }    
                }
                
            }
        }
        else{
            cout << "---- Results ----" << endl;
            
            for(auto iter : allVects){
                for(auto it : iter){
                    string date = "";
                    int ind = 0;
                    for(auto infoIter : extraInfo){
                        // cout << "TEST" << endl;
                        if (infoIter.first.compare(it.first) == 0){
                            date = infoIter.second.at(1);
                            
                        }    
                    }
                    ind++;
                    cout << ind << " - " << it.first << " - " << it.second << " - Publish Date: " << date << endl;
                }
            }
            string searchVal;
            cout << "Select a search: ";
            cin >> searchVal;

            int searchIndex = stoi(searchVal);
            pair<string, int> checkPair;

            checkPair = allVects.at(0).at(0);
            for(auto infoIter : extraInfo){
                // cout << " - " << infoIter.first << endl;
                if (infoIter.first.compare(checkPair.first) == 0){
                    string data = infoIter.second.at(0);
                    cout << "Text:" << endl << data;
                }    
            }
            cout << endl << endl;
        }
        
        allVects.clear();
        finalResults.clear();
    }
    
}

void File_Parser::CreateIndex(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string directory){
    for (const auto & entry : filesystem::directory_iterator(directory)){ //../sample_data/test-data
        if(filesystem::is_regular_file(entry)){
            filePaths.push_back(entry.path());
        }
        // std::cout << entry.path() << std::endl;
    }
    float totalFileCount = 0;

    auto start = chrono::steady_clock::now();

    for(const auto &entry : filesystem::directory_iterator(directory)){
        totalFileCount++;
    }

    for(const auto & entry : filesystem::directory_iterator(directory)){
        if(filesystem::is_regular_file(entry)){
            // cout << entry << endl;
            
            rapidjson::Document doc;

            ifstream data (entry.path());

            string fileStore = "";
            string temp;

            while(getline(data, temp)){
                fileStore += temp;
            }
            data.close();
            doc.Parse(fileStore.c_str());

            string tempTitle = doc["title"].GetString();
            string title = "";
            for(size_t k = 0; k < tempTitle.length(); k++){
                if (tempTitle.at(k) != '`' && tempTitle.at(k) != '|' && tempTitle.at(k) != '~'){
                    title += tempTitle.at(k);
                }
            }
            string filetext = doc["text"].GetString();

            pair<string, vector<string>> info;
            info.first = title;
            string textData = doc["text"].GetString();
            textData.erase(remove(textData.begin(), textData.end(), '\n'), textData.end());
            info.second.push_back(textData);
            string publishDate = doc["published"].GetString();
            publishDate.erase(find(publishDate.begin(), publishDate.end(), 'T'), publishDate.end());
            info.second.push_back(doc["published"].GetString());
            extraInfo.push_back(info);


            //Read in people
            for(auto &current : doc["entities"]["persons"].GetArray()) { 
                string name = current["name"].GetString();
                transform(name.begin(), name.end(), name.begin(), ::tolower);
                avlnode<unordered_map<string, int>>* tempNode = NULL;

                tempNode = persistenceIndexPerson.search(persistenceIndexPerson.root, name);
                
                if (tempNode != NULL) {
                    
                    unordered_map<string, int>::iterator iter;
                    for (iter = tempNode->d.begin(); iter != tempNode->d.end(); iter++){
                        if (iter->first == doc["title"].GetString() && tempNode->nodeName == name){
                            iter->second++;
                        }
                        else {
                            tempNode->d.insert({title, 1});
                        }
                    }
                    tempNode = NULL;
                }
                
                else{
                    personNodeData.insert({doc["title"].GetString(), 1});

                    persistenceIndexPerson.insert(persistenceIndexPerson.root, personNodeData, name);

                    personNodeData.clear();
                }
            }


            //Read in organizations
            for(auto &current : doc["entities"]["organizations"].GetArray()) { 
                
                string name = current["name"].GetString();
                transform(name.begin(), name.end(), name.begin(), ::tolower);

                avlnode<unordered_map<string, int>>* tempNode = NULL;

                tempNode = persistenceIndexOrg.search(persistenceIndexOrg.root, name);

                if (tempNode != NULL) {
                    unordered_map<string, int>::iterator iter;
                    for (iter = tempNode->d.begin(); iter != tempNode->d.end(); ++iter){
                        if (iter->first == title && tempNode->nodeName == name){
                            iter->second++;
                        }
                    }
                    tempNode = NULL;
                }
                else {
                    orgNodeData.insert({title, 1});

                    persistenceIndexOrg.insert(persistenceIndexOrg.root, orgNodeData, name);
                    
                    //../sample_data/coll_1
                    //mnt/c/Users/bensa/Documents/JsonStorage/tempArchive
                }
            }

        
            // //Read in text
            string searchData = doc["text"].GetString();
            avlnode<unordered_map<string, int>>* tempNode = NULL;
            string tempWord = "";
            transform(searchData.begin(), searchData.end(), searchData.begin(), ::tolower);
            for(char i : searchData){
                if (i == ' '){
                    Porter2Stemmer::stem(tempWord);

                    if (count(stopWords.begin(), stopWords.end(), tempWord) == 0 && tempWord.find_first_not_of(' ') != string::npos){
                        
                        tempNode = persistenceIndexSearch.search(persistenceIndexSearch.root, tempWord);
                        if(tempNode != NULL){
                            unordered_map<string, int>::iterator iter;
                            for (iter = tempNode->d.begin(); iter != tempNode->d.end(); ++iter){
                                if (iter->first == title){
                                    iter->second++;
                                }
                            }
                        }
                        else{
                            searchNodeData.insert({title, 1});
                            persistenceIndexSearch.insert(persistenceIndexSearch.root, searchNodeData, tempWord);
                        }                       
                        
                    }
                    tempWord = "";
                }
                else if (isalpha((unsigned char)i) || isdigit(i)){
                    tempWord = tempWord + i;
                }
            }

        }
    }


    auto end = chrono::steady_clock::now();
    chrono::duration<double> time_elapsed = end - start;
    cout << "Time elapsed: " << time_elapsed.count() << " seconds" << endl;
}

vector<pair<string,int>> File_Parser::getData(avlnode<unordered_map<string,int>>* node, string searchVal){
    
    vector<pair<string,int>> retMap;
    
    int index = 0;
    int updateIndex = 0;
    bool update = false;
    unordered_map<string, int>::iterator iter;
    for(iter = node->d.begin(); iter != node->d.end(); ++iter){
        if (retMap.size() >= 15){
            // cout << "too big" << endl;
            sort(retMap.begin(), retMap.end(), [](auto &left, auto &right){ return left.second > right.second;});
            if(iter->second > retMap.at(0).second){
                retMap.pop_back();
                retMap.push_back(make_pair(iter->first, iter->second));
            }
        }
        else {
            retMap.push_back(make_pair(iter->first, iter->second));
        }
    }
    sort(retMap.begin(), retMap.end(), [](auto &left, auto &right){ return left.second > right.second;});
    return retMap;
}

void File_Parser::fillStopWords(string filePath){
    ifstream dataStream (filePath);

    while (!dataStream.eof()){
        string word = "";
        getline(dataStream, word, ',');
        // cout << word << endl;

        stopWords.push_back(word);
    }
    // cout << "done";
}

void File_Parser::fillPersistenceIndex(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string filePath){ //../sample_data/coll    //../persistence.txt
    
    auto start = chrono::steady_clock::now();

    ofstream file(filePath);

    string output = "";

    persistenceIndexPerson.level_order(persistenceIndexPerson.root, persistenceIndexOrg.root, persistenceIndexSearch.root, output);

    // cout << "OUTPUT: " << endl << output << endl;

    while (output.find('\0') != string::npos){
        output.erase(find(output.begin(), output.end(), '\0'));
    }

    file << output;

    file.close();


    ofstream infoFile("../persistenceInfo.txt");
    string infoOutput = "";

    
    for(size_t i = 0; i < extraInfo.size(); i++){
        infoOutput = "";
        infoOutput += "<" + extraInfo.at(i).first + "`";
        for(size_t j = 0; j < extraInfo.at(i).second.size(); j++){
            infoOutput += extraInfo.at(i).second.at(j) + "~";
        }
        infoOutput += ">\n";
        infoFile << infoOutput;
    }

    cout << endl;

    infoFile.close();

    auto end = chrono::steady_clock::now();
    chrono::duration<double> time_elapsed = end - start;
    cout << "Time elapsed: " << time_elapsed.count() << " seconds" << endl;
}

void File_Parser::readPersistenceIndex(avl_tree<unordered_map<string, int>>& persistenceIndexPerson, avl_tree<unordered_map<string, int>>& persistenceIndexOrg, avl_tree<unordered_map<string, int>>& persistenceIndexSearch, vector<pair<string, vector<string>>>& extraInfo, string filePath){
    
    auto start = chrono::steady_clock::now();
    
    ifstream file (filePath);
    string temp = "";

    
    string nameData = "";
    string title = "";
    string tempFreq = "";
    int freq = 0;

    unordered_map<string, int> dataStore;
    int count = 0;
    while(getline(file, temp)){  

        nameData = "";
        title = "";
        freq = 0;
        bool name = true;
        for(size_t i = 0; i < temp.size(); i++){
            i++;
            if (temp.at(i) == 'p'){
                i += 2;
                while (temp.at(i) != '>'){
                    if (name == true){
                        while(temp.at(i) != '~'){
                            nameData += temp.at(i);
                            i++;
                        }
                        i++;
                        name = false;
                    }
                    while(temp.at(i) != '|'){
                        title += temp.at(i);
                        i++;
                    }
                    i++;
                    while (temp.at(i) != '~'){
                        tempFreq = temp.at(i);
                        stringstream ss(tempFreq);
                        ss >> freq;

                        i++;
                    }
                    

                    // cout << "pWORD: " << nameData << " - " << freq << endl;

                    dataStore.insert({title, freq});
                    tempFreq = "";
                    freq = 0;
                    title = "";
                     
                    i++;
                }
                persistenceIndexPerson.insert(persistenceIndexPerson.root, dataStore, nameData); 
                dataStore.clear();
            }
            else if(temp.at(i) == 'o'){
                i += 2;
                while (temp.at(i) != '>'){
                    if (name == true){
                        while(temp.at(i) != '~'){
                            nameData += temp.at(i);
                            i++;
                        }
                        i++;
                        name = false;
                    }
                    while(temp.at(i) != '|'){
                        title += temp.at(i);
                        i++;
                    }
                    i++;
                    while (temp.at(i) != '~'){
                        tempFreq = temp.at(i);
                        stringstream ss(tempFreq);
                        ss >> freq;

                        i++;
                    }
                    

                    // cout << "oWORD: " << nameData << " - " << freq << endl;

                    dataStore.insert({title, freq});
                    tempFreq = "";
                    freq = 0;
                    title = "";
                     
                    i++;
                }
                persistenceIndexOrg.insert(persistenceIndexOrg.root, dataStore, nameData);
                dataStore.clear();
            }
            else if(temp.at(i) == 'w'){
                i += 2;
                while (temp.at(i) != '>'){
                    if (name == true){
                        while(temp.at(i) != '~'){
                            nameData += temp.at(i);
                            i++;
                        }
                        i++;
                        name = false;
                    }
                    while(temp.at(i) != '|'){
                        title += temp.at(i);
                        i++;
                    }
                    i++;
                    while (temp.at(i) != '~'){
                        tempFreq += temp.at(i);
                        i++;
                    }
                    freq = stoi(tempFreq);
                    
                    if (freq > 4){
                        // cout << "wWORD: " << nameData << " - " << freq << endl;
                    }

                    dataStore.insert({title, freq});

                    tempFreq = "";
                    freq = 0;
                    title = "";
                     
                    i++;
                }
                persistenceIndexSearch.insert(persistenceIndexSearch.root, dataStore, nameData); 
                dataStore.clear();
            }
        }
    }
    file.close();

    ifstream infoFile("../persistenceInfo.txt");
    string dataString = "";
    
    pair<string, vector<string>> pairInfo;
    string tempInfo = "";
    
    while(getline(infoFile, dataString)){
        for(size_t i = 0; i < dataString.size(); i++){
                i++;
                while(dataString.at(i) != '`'){
                    tempInfo += dataString.at(i);
                    i++;
                }
                i++;
                pairInfo.first = tempInfo;
                tempInfo = "";
                while(dataString.at(i) != '~'){
                    tempInfo += dataString.at(i);
                    i++;
                }
                i++;
                pairInfo.second.push_back(tempInfo);
                tempInfo = "";
                while(dataString.at(i) != '~'){
                    tempInfo += dataString.at(i);
                    i++;
                }
                i++;
                pairInfo.second.push_back(tempInfo);
                extraInfo.push_back(pairInfo);
                pairInfo.first.clear();
                pairInfo.second.clear();
                tempInfo = "";
            // }
            break;
        }
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> time_elapsed = end - start;
    cout << "Time elapsed: " << time_elapsed.count() << " seconds" << endl;
}
