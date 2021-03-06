#ifndef _FamilyTree_
#define _FamilyTree_
#include <exception>
#include <string>
#include <iostream>
using namespace std;
namespace family
{
    struct Trunk
    {
        Trunk *prev;
        string str;
        Trunk(Trunk *prev, string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };
    class Tree {
        Tree* search(string son, Tree* curr);
        Tree* searchDel(string name,Tree* curr);
    public:
        string name;
        Tree* mother;
        Tree* father;
        Tree* root;
        bool gender;
        int height;
        void printTree(Tree *root, Trunk *prev, bool isLeft);
        void showTrunks(Trunk *p);
        string getName();
        Tree* getFather();
        Tree* getMother();
        void print();
        Tree* relation(string name , Tree* curr);
        Tree(string name);
        ~Tree();
        Tree* searchRel(bool tgender,int theight,Tree* curr);
        void DestroyRecursive(Tree* node);
        Tree &addFather(string son, string father);
        Tree &addMother(string son, string mother);
        void display();
        string relation(string rel);
        string find(string name);
        bool remove(string name);
    };
}
#endif