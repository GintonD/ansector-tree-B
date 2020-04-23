
#ifndef UNTITLED2_FAMILYTREE_H
#define UNTITLED2_FAMILYTREE_H
#pragma once
#include <iostream>

using namespace  std;
class Node{
public:
 int height  ;
 int sex ;
 string name;
 Node* father;
 Node* mother;


 Node(string name)
 {
     this->height = 0 ;
     this->sex = 0 ;
     this->name = name;
     this->father = NULL;
     this->mother = NULL;

 };

    ~ Node(){
        setFatherNull();
        setMotherNull();
    }

    void setFatherNull(){
        this->father=NULL;
    }

    void setMotherNull(){
        this->mother=NULL;
    }

};

namespace family {


    class Tree {

    public:
        Node *root;
        int size ;
        int maxHeight;
        Tree(string name) {
            this->root = new Node(name);
            size = 1 ;
            maxHeight = 0 ;
        };


        Tree& addMother(const string, const string);

        string relation(const string);

        string find(const string);

        void display();

        void remove(const string);

        Tree& addFather( string,  string);


        void findthis(const string , Node *pNode , Node **pNode1);

        void findtheFamily(int sex, int count, Node *pNode, Node **pNode1);

        void print2DUtil(Node *pNode,int space);


        void findthischild(const string basicString, Node *pNode, Node **pNode1);
    };
}



#endif //UNTITLED2_FAMILYTREE_H
