#include "FamilyTree.hpp"
using namespace family;

Tree::Tree(string name):
name(name),mother(NULL),father(NULL),root(NULL),height(0){
    if(this->root== NULL){
        this->root=this;
    }
}
Tree &Tree::addMother(string son, string mother){
    Tree* child = search(son ,this->root);
    if (child != NULL) {
        if (child->mother == NULL) {
            child->mother = new Tree(mother);
            Tree* mot =child->mother;
            mot->height=child->height+1;
            mot->gender=false;
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
                    Tree* mot =child->father;
                    mot->height=child->height+1;
                    mot->gender=true;
                    return *root;
                }else{
                    throw std::invalid_argument("there is a father");
                }
    }else{
            throw std::invalid_argument(son+" isnt existt");
        }
}
Tree* Tree::search(string name,Tree* curr)
{
   if(curr->name == name)
    {
        return curr ;
    }
    if(curr->father != NULL)
    {
        //curr->getFather()->gender = "father";
       Tree* toBRetrun = search(name,curr->getFather());
        if(toBRetrun != NULL)return toBRetrun;
    }
    if(curr->mother != NULL)
    {
       // curr->getMother()->gender = "mother";
        Tree* toBRetrun = search(name,curr->getMother());
        if(toBRetrun != NULL)return toBRetrun;
    }
    return NULL ;
}
Tree* Tree::searchRel(bool tgender,int theight,Tree* curr)
{
   if(curr->height == theight && curr->gender== tgender)
    {
        return curr ;
    }
    if(curr->father != NULL)
    {
        //curr->getFather()->gender = "father";
       Tree* toBRetrun = searchRel(tgender,theight,curr->getFather());
        if(toBRetrun != NULL)return toBRetrun;
    }
    if(curr->mother != NULL)
    {
       // curr->getMother()->gender = "mother";
        Tree* toBRetrun = searchRel(tgender,theight,curr->getMother());
        if(toBRetrun != NULL)return toBRetrun;
    }
    return NULL ;
}
Tree* Tree::searchDel(string name,Tree* curr){

    if((curr->father != NULL && curr->father->name == name) ||(curr->mother != NULL && curr->mother->name == name))
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
   // cout << root->getName() << endl;
    cout << root->name << endl;

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
Tree* Tree::relation(string rel,Tree *curr){
    return this;
}
string Tree::relation(string rel){
 string result = "";
 Tree* ans = search(rel,this->root);
 if(ans==NULL){
     return "unrelated";
 }
 if(ans->height==0){
     return"me";
 }
 if(ans->gender==true){
     result="father";
    for(int i =1 ; i <= ans->height; i++){
     if(i==2) {
         result = "grand" + result;;
     }
    else if(i>2){
        result = "great-" + result;
    }
    }
 }
 else{
     result="mother";
     for(int i =1 ; i <= ans->height; i++){
         if(i==2) {
             result = "grand" + result;;
         }
         else if(i>2){
             result = "great-" + result;
         }
     }
 }
    return result;
}
string Tree::find(string relation){
    string moshe = relation;
    string delimiter = "-";
    int counter=0;
    int index = 0;
    size_t pos = 0;
    string token;
    bool found = false;
    string lastWord = "";
    while ((pos = relation.find(delimiter)) != string::npos) {
        token = relation.substr(0, pos);
      //  string lowerToken = toLowerCse(token);
        counter++;
        relation.erase(0, pos + delimiter.length());
        lastWord = relation ;
    }
    if(relation=="me" ){
        return root->name;

    } else if (relation=="father"){
        index =1;
      Tree* pers = searchRel(true,index,this->root);
      if(pers!=NULL)
      return pers->getName();

    } else if (relation =="mother"){
        index=1;
        Tree* pers = searchRel(false,index,this->root);
        if(pers!=NULL)
        return pers->getName();
    }else if(relation=="grandfather"){
        index = 2+counter;
        Tree* pers = searchRel(true,index,this->root);
        if(pers!=NULL)
        return pers->getName();
    } else if (relation=="grandmother"){
        index=2+counter;
        Tree* pers = searchRel(false,index,this->root);
        if(pers!=NULL)
        return pers->getName();
    }
    throw std::invalid_argument(moshe+" doesnt exist ");
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