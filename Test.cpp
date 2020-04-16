#include "doctest.h"
#include "FamilyTree.hpp"

using namespace family;


TEST_CASE("check add father tests") {//12
Tree* root = new Tree("yossef");
            CHECK_NOTHROW(root->addFather("yossef","moshe"));
            CHECK_NOTHROW(root->addFather("moshe","hen"));
            CHECK_NOTHROW(root->addFather("hen","roee"));
            CHECK_NOTHROW(root->addFather("roee","ori"));
            CHECK_NOTHROW(root->addFather("ori","roberto"));
            CHECK_NOTHROW(root->addFather("roberto","mor"));
            CHECK_THROWS(root->addFather("moriel","roni"));
            CHECK_THROWS(root->addFather("fucs","roee"));
            CHECK_THROWS(root->addFather("hen","roee"));
            CHECK_THROWS(root->addFather("eran","roee"));
            CHECK_THROWS(root->addFather("eran","roee"));
            CHECK_THROWS(root->addFather("shlomi","roee"));
}

TEST_CASE("check add mother tests") {//13
      Tree* root = new Tree("yossef");
            CHECK_NOTHROW(root->addMother("yossef","shani"));
            CHECK_NOTHROW(root->addMother("shani","hen"));
            CHECK_NOTHROW(root->addMother("hen","reut"));
            CHECK_NOTHROW(root->addMother("reut","ronit"));
            CHECK_NOTHROW(root->addMother("ronit","shilo"));
            CHECK_NOTHROW(root->addMother("shilo","shimrit"));
            CHECK_THROWS (root->addMother("natali","lilo"));
            CHECK_THROWS(root->addMother("shani","osnat"));
            CHECK_THROWS(root->addMother("osnat","levana"));
            CHECK_THROWS(root->addMother("hen","shir"));
            CHECK_THROWS(root->addMother("shir","rivka"));
}
TEST_CASE("father and mother functions") {//23+
    Tree* root = new Tree("samuel");
            CHECK_NOTHROW(root->addMother("samuel","michele"));
            CHECK_NOTHROW(root->addFather("samuel","frederic"));
            CHECK_NOTHROW(root->addMother("michele","sol"));
            CHECK_NOTHROW(root->addFather("michele","jacob"));
            CHECK_NOTHROW(root->addMother("frederic","judith"));
            CHECK_NOTHROW(root->addFather("frederic","gilbert"));
            CHECK_NOTHROW(root->addMother("judith","boube"));
            CHECK_NOTHROW(root->addMother("gilbert","pesci"));
            CHECK_NOTHROW(root->addMother("jacob","jamilah"));
            CHECK_NOTHROW(root->addFather("jacob","simon"));
            CHECK_NOTHROW(root->addFather("gilbert","nicolas"));
            CHECK_NOTHROW(root->addFather("nicolas","sigismon"));
            CHECK_THROWS(root->addMother("samuel","mouloud"));
            CHECK(root->remove("gilbert") == true);
            CHECK(root->remove("gilbert") == false);
            CHECK(root->remove("nicolas") == false);
            CHECK(root->remove("sol") == true);
            CHECK(root->remove("sol") == false);
            CHECK(root->remove("jamilah") == true);
            CHECK(root->remove("simon") == true);
            CHECK(root->remove("samuel") == true);
            CHECK(root->remove("samuel") == false);
            CHECK(root->remove("frederic") == false);
}
TEST_CASE("remove function") {//6
    Tree* root = new Tree("yossef");
    root->addMother("yossef","shani");
    root->addFather("yossef","moshe");
    root->addMother("shani","hen");
    root->addMother("hen","reut");
    root->addFather("hen","roee");
    root->addMother("shani","ronit");
    root->addFather("moshe","ron");
    root->addMother("moshe","orit");
    CHECK(root->remove("hen") == true); // remove one of the noded
    CHECK(root->remove("shani") == true);
    CHECK(root->remove("hen") == false);  // remove func without a member in the tree
    CHECK(root->remove("reut") == false);
    CHECK(root->remove("ron") == true);
    CHECK(root->remove("yossef") == true); //remove root
}
Tree buildTree(Tree &root){
    root.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
            .addMother("Yosef", "Rachel")  // Tells the tree that the mother of Yosef is Rachel.
            .addFather("Yaakov", "Isaac")
            .addMother("Yaakov", "Rivka")
            .addFather("Isaac", "Avraham")
            .addFather("Avraham", "Terah");

    return root;
}
TEST_CASE("display function") {//4
    family::Tree root("Yosef");
            CHECK_NOTHROW(root = buildTree(root));
            CHECK_NOTHROW(root.display());
            /* how it should be look like
   .---Rachel
---Yosef
   |    .---Rivka
    `---Yaakov
        `---Isaac
            `---Avraham
                `---Terah
*/
            root.addFather("Rachel","Lavan");
            root.addFather("Lavan","Betuel");
            //after adding nodes
            CHECK_NOTHROW(root.display());
            /*it is should show look like:
    .---Rachel
   |    `---Lavan
   |        `---Betuel
---Yosef
   |    .---Rivka
    `---Yaakov
        `---Isaac
            `---Avraham
                `---Terah

             */
            root.remove("Isaac");
            CHECK_NOTHROW(root.display());
/*
   .---Rachel
   |    `---Lavan
   |        `---Betuel
---Yosef
   |    .---Rivka
    `---Yaakov

 */
}
TEST_CASE("relation function") {//12
    family::Tree root("Yosef");
    root = buildTree(root);
    root.addMother("Isaac","Sara");
    root.addFather("Terah","Shem");
    root.addMother("Terah","Hani");
            CHECK(root.relation("Terah")=="great-great-grandfather");
            CHECK(root.relation("Sara")=="great-grandmother");
            CHECK(root.relation("Yaakov")=="father");
            CHECK(root.relation("Rachel")=="mother");
            CHECK(root.relation("David")=="unrelated");
            CHECK(root.relation("Isaac")=="grandfather");
            CHECK(root.relation("Avraham")=="great-grandfather");
            CHECK(root.relation("Rivka")=="grandmother");
            CHECK(root.relation("Lavan")=="unrelated");
            CHECK(root.relation("Betuel")=="unrelated");
            CHECK(root.relation("Hani")=="great-great-great-grandmother");
            CHECK(root.relation("Terah")=="great-great-great-grandfather");
}
TEST_CASE("find function") { // 8
    family::Tree root("Yosef");
    root = buildTree(root);
    root.addMother("Isaac","Sara");
    root.addFather("Terah","Shem");
    CHECK(root.find("great-great-great-grandfather")=="Shem");
    CHECK(root.find("great-grandfather")=="Avraham");
    CHECK(root.find("great-great-grandfather")=="Terah");
    CHECK(root.find("grandfather")=="Isaac");
    CHECK(root.find("father")=="Yaakov");
    CHECK(root.find("mother")=="Rachel");
    CHECK(root.find("grandmother")=="Rivka");
    CHECK(root.find("great-grandmother")=="Sara");
}

TEST_CASE("father and mother remove and realtion functions") {//21
    Tree* root = new Tree("yonatan");
            CHECK_NOTHROW(root->addMother("yonatan","osnat"));
            CHECK_NOTHROW(root->addFather("yonatan","meir"));
            CHECK_NOTHROW(root->addMother("meir","mami"));
            CHECK_NOTHROW(root->addFather("meir","mazliah"));
            CHECK_NOTHROW(root->addFather("osnat","aharon"));
            CHECK_NOTHROW(root->addMother("osnat","sharin"));
            CHECK_NOTHROW(root->addFather("mazliah","ben-zion"));
            CHECK(root->find("father")=="meir");
            CHECK(root->find("mother")=="osnat");
            CHECK(root->find("great-grandfather")=="ben-zion");
            CHECK(root->relation("osnat")=="mother");
            CHECK(root->relation("meir")=="father");
            CHECK(root->relation("ben-zion")=="great-grandfather");
            CHECK(root->remove("sharin")==true);
            CHECK(root->remove("mazliah")==true);
            CHECK(root->relation("mami")=="grandmother");
            CHECK(root->relation("aharon")=="grandfather");
            CHECK(root->remove("mami")==true);
            CHECK(root->remove("ben-zion")==true);
            CHECK(root->remove("sharin")==false);
            CHECK(root->remove("aharon")==true);
}