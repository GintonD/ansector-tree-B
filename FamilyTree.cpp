#include "FamilyTree.hpp"
#include <iostream>
#include <string>
#include <cmath>
bool static check = false; //flag of findthis function
bool static check1 = false ;
int static check2 = 0 ;
using namespace family;
using namespace std ;

void print2DUtil(Node *runner, int space);

Tree& Tree::addFather( string child, string father) 
{
    int a=0;
    if (this->root == NULL)
    {
        out_of_range{"The Family tree is Empty!"};
        return *this;
    }
    
    Node *temp = nullptr;
    findthis(child, this->root ,&temp); // check if there such child
    check = false ; //restart the flag
    if(temp == NULL)
    {
        throw out_of_range{"cannot find this child!"};
    }
    
    if(temp != NULL)
    {
        if(temp->father != NULL) throw out_of_range("aleardy have father");
        temp->father = new Node(father); //add the new father
        temp->father->height = temp->height+1 ; //update the hight
        temp->father->sex = 1 ; //set the gender number
        this->size++;
        if(maxHeight < temp->father->height)
            maxHeight = temp->father->height;

    }
    check = false ;
    return *this;


}

Tree& Tree::addMother( string child, string mother) 
{
    if (this->root == NULL)
    {
        out_of_range{"The Family tree is Empty!"};
        return *this;
    }
    

    Node *temp = nullptr; //temp for check if there is such a child
    findthis(child, this->root ,&temp);
    check = false ;
    if(temp == NULL)
    {
        throw out_of_range{"cannot fin.id this child!"};
    }
    if(temp != NULL)
    {
        if(temp->mother != NULL) throw out_of_range("aleardy have mother");
        temp->mother = new Node(mother);
        temp->mother->height = temp->height+1 ;
        temp->mother->sex = 2 ;
        this->size++;
        if(maxHeight < temp->mother->height) maxHeight = temp->mother->height;

    }
    check = false ;
    return *this;

}


string Tree::relation(const string name)
{

    Node *temp = nullptr;
    findthis(name, this->root ,&temp);
    check = false ;
    if(temp == NULL)
        return "unrelated" ;
    int height = temp->height;
    int sex = temp->sex ;
    check = false ;
    if(height == 0 ) return "me" ;
    if(sex == 1 && height == 1) return "father" ;
    if(sex == 2 && height == 1) return  "mother" ;
    if(sex == 1 && height == 2) return "grandfather" ;
    if(sex == 2 && height == 2) return  "grandmother" ;

    if(sex == 1 && height > 2)
    {
        string ans =  "grandfather" ;
        while(height != 2)
        {
            ans = "great-" + ans ;
            height--;
        }
        return ans ;
    }

    if(sex == 2 && height > 2)
    {
        string ans =  "grandmother" ;
        while(height != 2)
        {
            height--;
            ans = "great-" + ans ;
        }
        return ans ;
    }
    return "" ;
}

string Tree::find(const string reletion )
{

    int count = -1 ;
    int sex = -1 ;
    string granm = "grandmother";
    string granf = "grandfahter";
    if(reletion == "son")
    {
        count = -1;
        sex = -1;
        Node *tempnode = nullptr;
        findtheFamily(sex , count , root , &tempnode);
        check1 = false ;
        if(tempnode == nullptr) throw out_of_range("false");
        return tempnode->name ;
    }
    if(reletion == "me")
    {
        count = 0 ;
        sex = 0 ;
    }
    if (reletion == "father")
    {
        count = 1;
        sex = 1 ;
    }
    if (reletion == "mother")
    {
        count = 1;
        sex = 2;
    }
    if (reletion == "grandfather")
    {
        count = 2;
        sex = 1;
    }
    if (reletion == "grandmother")
    {
        count = 2;
        sex = 2;
    }


     if(reletion.find("grandmother") > 4 )
     {

         size_t temp = reletion.find("grandmother") ;
         if(temp != string::npos)
         {

             temp = (temp) / 6;
             for (int i = 0; i < reletion.size(); ++i)
             {
                if((reletion[i] < 97 || reletion[i] > 122) && reletion[i] != 45) throw out_of_range("not good reletion");
             } //not from the 'a'-'z' range and not '-'  
             count = temp + 2;
             sex = 2;
         }
     }

     if(reletion.find("grandfather") > 4 )
    {
        size_t temp = reletion.find("grandfather") ;
        if(temp != string::npos)
        {
            for (int i = 0; i < reletion.size(); ++i)
            {
                if((reletion[i] < 97 || reletion[i] > 122) && reletion[i] != 45) throw out_of_range("not good reletion");
            }
            temp = (temp) / 6;
            count = temp + 2;
            sex = 1;
        }
    }
     Node *tempnode = nullptr;
     findtheFamily(sex , count , root , &tempnode);
    check1 = false ;
    if((sex == -1 && count == -1) || tempnode == NULL ) throw out_of_range("cannot find the reletion");
    return tempnode->name ;

}
void deleteFromTree(Node** node){
    if (*node == NULL) return;
    deleteFromTree(&(*(node))->mother);
    deleteFromTree(&(*(node))->father);
    *node = nullptr;
    delete *node;
}







void Tree::findthis(const string child, Node *root ,  Node** temp) 
{

    if(root == NULL) return;
    if(root->name == child && !check)
    {

      check = true ;
        *temp = root  ;
    }
    if(!check)
    {
        Tree::findthis(child , root->father , temp);
        Tree::findthis(child , root->mother , temp );
    }
}



void Tree::findtheFamily(int sex, int count, Node *root, Node **temp) 
{
    if(root == NULL) return;
    if(root->sex  == sex && root->height == count  )
    {
        *temp = root  ;
        check1 = true ;

    }
    if(!check1)
    {
        Tree::findtheFamily(sex ,count , root->father , temp);
        Tree::findtheFamily(sex ,count ,  root->mother , temp );
    }

}

void Tree::remove(const string name)
{
    Node *temp = nullptr;
    findthischild(name, this->root ,&temp);
    check = false ;
    if(temp == NULL) throw out_of_range("the name is no in the tree");
    if(check2 == 1)  deleteFromTree(&temp ->father);
    if(check2 == 2)  deleteFromTree(&temp ->mother);
    check2 = 0 ;

}

void Tree::display()
{
    print2DUtil(root,0);

}

// It does reverse inorder traversal  
//example:
/*                             david

                    moshe

                              liat

          root

                              yosef

                    rivka

                              rachel


*/
////Help function From "https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/"
void Tree::print2DUtil(Node *runner,int space) 
{
// Base case
int count = 10;
if (runner == NULL)
return;

// Increase distance between levels
space += count;

// Process right child first
print2DUtil(runner->father, space);

// Print current node after space
// count
cout<<endl;
for(int i=count ;i< space ;i++)
{
        cout << " ";
}
cout<<runner->name<<"\n";

// Process left child
print2DUtil(runner->mother, space);
}



void Tree::findthischild(const string child, Node *root, Node **temp) 
{

    if(root == NULL) return;
    if(root->father != NULL && root->father->name == child && !check)
    {

        check = true ;
        check2 = 1;
        *temp = root  ;
    }
    if(root->mother != NULL && root->mother->name == child && !check)
    {

        check = true ;
        check2 = 2 ;
        *temp = root  ;

    }
    if(!check)
    {
        Tree::findthischild(child , root->father , temp);
        Tree::findthischild(child , root->mother , temp );
    }
}
