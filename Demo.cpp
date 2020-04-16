/**
 * Demo for Family Tree
 * 
 * First version by Adam Lev-Ari,  2019-12
 * Second version by Erel Segal-Halevi, 2020-04
 */

#include "FamilyTree.hpp"

#include <iostream>
using namespace std;

int main() {
    family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
    T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
            .addMother("Yosef", "Rachel")  // Tells the tree that the mother of Yosef is Rachel.
             .addFather("Rachel","Lavan")
            .addFather("Lavan","Betuel")
           .addFather("Yaakov", "Isaac")
           .addMother("Yaakov", "Rivka")
            .addFather("Isaac", "Avraham")
            .addFather("Avraham", "Terah");

    T.remove("Isaac");
    T.display();                        // displays the tree in a human-friendly format.
/*
    cout << T.relation("Yaakov") << endl;  // prints "father"
    cout << T.relation("Rachel") << endl;  // prints "mother"
    cout << T.relation("Rivka") << endl;  // prints "grandmother"
    cout << T.relation("Avraham") << endl;  // prints "great-grandfather"
    cout << T.relation("Terah") << endl;  // prints "great-great-grandfather"
    cout << T.relation("xyz") << endl;  // prints "unrelated"
    cout << T.relation("Yosef") << endl;  // prints "me"

    cout << T.find("mother") << endl;  // prints "Rachel"
    cout << T.find("great-great-grandfather") << endl;  // prints "Terah"
    try {
        cout << T.find("uncle") << endl;  // throws an exception
    } catch (const exception& ex) {
        cout << ex.what() << endl;  // prints "The tree cannot handle the 'uncle' relation"
    }
*/
/*
  cout<<  T.remove("Yosef")<<endl; // removes Avraham and Terah

    T.display();
   // T.addFather("Yosef","jacky");
    T.display();
*/
    //  cout << T.relation("Terah") << endl;  // prints "unrelated"

    return 0;
}