#include "FamilyTree.hpp"
using namespace family;

Tree::Tree(string name):
name(name),mother(NULL),father(NULL),root(NULL){
    if(this->root== NULL){
        this->root=this;
    }
}
Tree &Tree::addMother(string son, string mother){
    Tree* child = search(son ,this->root);
    if (child != NULL) {
        if (child->mother == NULL) {
            child->mother = new Tree(mother);
            return *root;
        }else{
            throw std::invalid_argument("there is a mother");
        }
    }else{
        throw std::invalid_argument(son+" isnt exist");
    }
}
Tree &Tree::addFather(string son, string father){
    Tree* child = search(son ,this->root);
        if (child != NULL) {
                if (child->father == NULL) {
                    child->father = new Tree(father);
                    return *root;
                }else{
                    throw std::invalid_argument("there is a father");
                }
    }else{
            throw std::invalid_argument(son+" isnt existt");
        }
}
Tree* Tree::search(string name,Tree* curr){
   if(curr->name == name)
    {
        return curr ;
    }
    if(curr->father != NULL)
    {
        Tree* toBRetrun = search(name,curr->getFather());
        if(toBRetrun != NULL)return toBRetrun;
    }
    if(curr->mother != NULL)
    {
        Tree* toBRetrun = search(name,curr->getMother());
        if(toBRetrun != NULL)return toBRetrun;
    }
    return NULL ;
}
Tree* Tree::searchDel(string name,Tree* curr){
    if(curr->father->name == name ||curr->mother->name == name)
    {
        return curr ;
    }
    if(curr->father != NULL)
    {
        Tree* toBRetrun = searchDel(name,curr->getFather());
        if(toBRetrun != NULL)return toBRetrun;
    }
    if(curr->mother != NULL)
    {
        Tree* toBRetrun = searchDel(name,curr->getMother());
        if(toBRetrun != NULL)return toBRetrun;
    }
    return NULL ;
}
void Tree::showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}
void Tree::printTree(Tree *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getMother(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->getName() << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getFather(), trunk, false);
}
void Tree::display(){
    printTree(this->root, nullptr, false);
    
}
//lo lishkoah limhok fonction print
void Tree::print(){
    cout<<this->name<<endl;
}
string Tree::getName(){
    return this->name ;
}
string Tree::relation(string rel){
    return "";
}
string Tree::find(string name){
    return "" ;
}
bool Tree::remove(string name){
    if(name == root->name){
        DestroyRecursive(root);
        root=NULL;
        return true;
    }

    Tree *toBeRemoved = searchDel(name,root);

    if(toBeRemoved==NULL){
        return false;
    }
    else if(toBeRemoved->getFather()->getName()==name){
            DestroyRecursive(toBeRemoved->father);
            toBeRemoved->father=NULL;
            return true;
    } else if (toBeRemoved->getMother()->getName()==name){
        DestroyRecursive(toBeRemoved->mother);
        toBeRemoved->mother=NULL;
        return true;
    }
    else{
        return false;
    }
}
void Tree::DestroyRecursive(Tree* node)
{
    if (node != nullptr)
    {
        DestroyRecursive(node->getFather());
        DestroyRecursive(node->getMother());
        node->father=NULL;
        node->mother=NULL;
    }
}
Tree::~Tree()
{

}
Tree* Tree::getFather(){
    return this->father;
}
Tree* Tree::getMother(){
    return this->mother;
}