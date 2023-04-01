//
// Created by Abhlash Arnipalli on 11/9/22.
//

#ifndef DSAVLTREE_H
#define DSAVLTREE_H


#include <typeinfo>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

template<class Obj>
struct avlnode {
    Obj d; //data
    string nodeName;
    struct avlnode *left = NULL; //left node
    struct avlnode *right = NULL; //right node
    int height = 0; //height int of the tree
};

template<class Obj>
class avl_tree {
public:
    int count = 0;
    avlnode<Obj>* root;
    int height(avlnode<Obj>*);
    int difference(avlnode<Obj>*);
    avlnode<Obj>* rr_rotate(avlnode<Obj>*);
    avlnode<Obj>* ll_rotate(avlnode<Obj>*);
    avlnode<Obj>* lr_rotate(avlnode<Obj>*);
    avlnode<Obj>* rl_rotate(avlnode<Obj>*);
    avlnode<Obj>* balance(avlnode<Obj>*);
    void insert(avlnode<Obj>*&, Obj, string);
    void show(avlnode<Obj>*, int l);
    void inorder(avlnode<Obj>*, string&/*ofstream& output_file*/);
    void level_order(avlnode<Obj>* personRoot, avlnode<Obj>* orgRoot, avlnode<Obj>* searchRoot, string &output_file);
    void preorder(avlnode<Obj>*);
    void postorder(avlnode<Obj>*);
    // void updateData(avlnode<Obj>*& node, string title);
    avlnode<Obj>* search(avlnode<Obj> *& root, string name);
    void freeTree(avlnode<Obj>* node);
    avl_tree() {
        root = NULL;
    }
};

template<class Obj>
int avl_tree<Obj>::height(avlnode<Obj>* t) { //returns the height of the AVL tree
    int h = 0;
    if (t != NULL) {
        // cout << "FIRST " << t->nodeName << endl;
        int l_height = height(t->left);
        // cout << "SECOND " << t->nodeName << endl;
        int r_height = height(t->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;

}


template<class Obj>
int avl_tree<Obj>::difference(avlnode<Obj>* t) { //returns the difference between the heihgt of left child and the height of the right child
    // cout << "check1" << endl;
    int l_height = height(t->left);
    // cout << "check2" << endl;
    int r_height = height(t->right);
    // cout << "check3" << endl;
    int b_factor = l_height - r_height;
    return b_factor;
}

template<class Obj>
avlnode<Obj>* avl_tree<Obj>::rr_rotate(avlnode<Obj>* parent) { //right right rotation function
    avlnode<Obj> *t;
    // cout<<"Right-Right Rotation" << endl;
    t = parent->right;
    parent->right = t->left;
    t->left = parent;
    return t;
}

template<class Obj>
avlnode<Obj>* avl_tree<Obj>::ll_rotate(avlnode<Obj>* parent) { //left left rotation function
    avlnode<Obj> *t;
    // cout<<"Left-Left Rotation" << endl;
    t = parent->left;
    parent->left = t->right;
    t->right = parent;
    return t;
}

template<class Obj>
avlnode<Obj>* avl_tree<Obj>::lr_rotate(avlnode<Obj>* parent) { //left right rotation function
    avlnode<Obj>* t;
    // cout<<"Left-Right Rotation" << endl;
    t = parent->left;
    parent->left = rr_rotate(t);
    return ll_rotate(parent);
}

template<class Obj>
avlnode<Obj>* avl_tree<Obj>::rl_rotate(avlnode<Obj>* parent) { //right left rotation function
    avlnode<Obj> *t;
    t = parent->right;
    // cout<<"Right-Left Rotation" << endl;
    parent->right = ll_rotate(t);
    return rr_rotate(parent);
}

template<class Obj>
avlnode<Obj>* avl_tree<Obj>::balance(avlnode<Obj>* t) { //balances the branches on the tree using rr, ll, rl, and lr functions
    

    avlnode<Obj>* newroot = NULL;

    if (t->left){
        t->left = balance(t->left);
    }
    if (t->right){
        t->right = balance(t->right);
    }

    int diff = difference(t);

    if (diff >= 2){
        if (difference(t->left) <= -1){
            newroot = lr_rotate(t);
        }
        else{
            newroot = ll_rotate(t);
        }
    }
    else if(diff <= -2){
        if(difference(t->right) >= 1){
            newroot = rl_rotate(t);
        }
        else {
            newroot = rr_rotate(t);
        }
    }
    else {
        newroot = t;
    }
    return newroot;
}

template<class Obj>
void avl_tree<Obj>::insert(avlnode<Obj>*& r, Obj v, string name) { //inserts new node to the tree
    avlnode<Obj> *node = NULL;
    avlnode<Obj> *next = NULL;
    avlnode<Obj> *last = NULL;
    count++;

    if (r == NULL){
        node = new avlnode<Obj>;
        node->d = v;
        node->nodeName = name;
        node->left = NULL;
        node->right = NULL;
        r = node;
      
    }
    else {
        next = r;
        while (next != NULL){
            last = next;

            if (name.compare(next->nodeName) < 0){
                next = next->left;
            }
            else if(name.compare(next->nodeName) > 0){
                next = next->right;
            }
            else if(name.compare(next->nodeName) == 0){
                return;
            }
        }

        node = new avlnode<Obj>;
        node->d = v;
        node->nodeName = name;
        node->left = NULL;
        node->right = NULL;
        
        if (name.compare(last->nodeName) < 0){
            last->left = node;
        }
        if (name.compare(last->nodeName) > 0){
            last->right = node;
        }
        
        
    }
    count++;
    avlnode<Obj>* newroot = NULL;

    newroot = balance(r);

    if (newroot != r){
        r = newroot;
    }
    
}

template<class Obj>
void avl_tree<Obj>::show(avlnode<Obj>* p, int l) { //displays the root node of the tree
    int i;
    if (p != NULL) {
        
        show(p->right, l + 1);
        if (p->nodeName.compare(root->nodeName) == 0){
            cout << " Root->";
        }
        for (i = 0; i < l && p->nodeName != root->nodeName; i++)
            cout << " ";
        cout << p->nodeName;
        show(p->left, l + 1);
    }
}

template<class Obj>
void avl_tree<Obj>::inorder(avlnode<Obj>* t, string& output/*ofstream &output_file*/) { //traverses the tree inorder
    if (t == NULL)
        return;
    inorder(t->left, output);
    // cout << (t->nodeName) << " ";
    output += (t->nodeName);
    inorder(t->right, output);
}

template<class Obj>
void avl_tree<Obj>::level_order(avlnode<Obj>* personRoot, avlnode<Obj>* orgRoot, avlnode<Obj>* searchRoot, string &output){ //traverses the tree by level order [goes through every level in the tree] (optimal for insertion from persistent index)
    string treeType;
    for(size_t i = 0; i < 3; i++){
        if(personRoot == NULL && orgRoot == NULL && searchRoot == NULL){
            cout << "No temporary index detected";
            return;
        }
        queue<avlnode<Obj>*> node_queue;
        if(i == 0){
            node_queue.push(personRoot);
            treeType = "p";
        }
        else if (i == 1){
            node_queue.push(orgRoot);
            treeType = "o";
        }
        else if (i == 2){
            node_queue.push(searchRoot);
            treeType = "w";
        }
        
        avlnode<Obj>* currentNode = node_queue.front();
        output += "<" + treeType + "`" + currentNode->nodeName + "~";
        unordered_map<string, int>::iterator iter;
        for (auto iter : currentNode->d){
            
            output += iter.first;
            output += "|";
            output += to_string(iter.second);
            output += "~";
        }
        output += ">\n";
        node_queue.pop();
        node_queue.push(currentNode->left);
        node_queue.push(currentNode->right);
        while(!node_queue.empty()) { ///
            currentNode = node_queue.front();
            output += "<" + treeType + "`" + currentNode->nodeName + "~";
            
            for (auto iter : currentNode->d){
                output += iter.first;
                output += "|";
                output += to_string(iter.second);
                output += "~";
            }
            output += ">\n";
            node_queue.pop();
            if(currentNode->left != NULL) { ///
                node_queue.push(currentNode->left);
            } ///
            if(currentNode->right != NULL) { ///
                node_queue.push(currentNode->right);
            } ///
        } ///
    }
    // while loop should continue until queue empty
    // only push nodes onto queu if children are not null
}


template<class Obj>
void avl_tree<Obj>::preorder(avlnode<Obj>* t) { //traverses the tree by preorder
    if (t == NULL)
        return;
    cout << *t->d << " ";
    preorder(t->left);
    preorder(t->right);
}

template<class Obj>
void avl_tree<Obj>::postorder(avlnode<Obj> *t) { //traverses the tree by postorder
    if (t == NULL)
        return;
    postorder(t ->left);
    postorder(t ->right);
    cout << t->d << " ";
}

template<class Obj>
avlnode<Obj>* avl_tree<Obj>::search(avlnode<Obj> *& r, string name){ //searches for a particular node in the tree
    
    if (r == NULL){
        return NULL;
    }

    if (r->nodeName.compare(name) == 0){
        return r;
    }
    if (r->nodeName.compare(name) > 0){
        return search(r->left, name);
    }
    if (r->nodeName.compare(name) < 0){
        return search(r->right, name);
    }
    else{
        cout << "Sorry, we could not find any documents that matched your search criteria" << endl;
        exit(-1); //query was not found
    }
    
    return r;
}

#endif //FINALPROJEXAMPLES_DSAVLTREE_H
