//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

GroupList* gList;

void groupCreation(string name);
void shapeInsertion(GroupNode* groupNode, string name, string type, int x_loc, int y_loc, int x_size, int y_size);
void deleting(string name);
void shapeMoves(string shape, string group);

int main() {
    gList = new GroupList();
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS - 1]);
    gList->insert(poolGroup);
    string line;
    string command;
    cout << "> ";         
    getline(cin, line);    
    while (!cin.eof()) {
        //check if the user press enter
        if (line != "") {
            stringstream lineStream(line);
            lineStream >> command;
            
            if (command == keyWordsList[0]) {
                string name, type;
                int x_loc, y_loc, x_size, y_size;
                lineStream >> name >> type >> x_loc >> y_loc >> x_size >> y_size;
                shapeInsertion(poolGroup, name, type, x_loc, y_loc, x_size, y_size);
            }          
            else if (command == keyWordsList[1]) {
                string name;
                lineStream >> name;
                groupCreation(name);
            }          
            else if (command == keyWordsList[2]) {
                string shape, group;
                lineStream >> shape >> group;
                shapeMoves(shape, group);
            }
            else if (command == keyWordsList[3]) {
                string name;
                lineStream >> name;
                deleting(name);
            }
            else if (command == keyWordsList[4]) {
                cout << "drawing:" << endl;
                gList->print();
            }
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
    }  // End input loop until EOF.
    delete gList;
    return 0;
}

void groupCreation(string name) {
    GroupNode* pptrTemp = gList->getHead();
    if (name == "shape" || name == "group" || name == "move" || name == "delete" || name == "draw" || name == "pool") {
        cout << "error: invalid name" <<  endl;
        return;
    }
    while (pptrTemp != nullptr) {
        if (pptrTemp->getName() == name) {
            cout << "error: name " << name << " exists" << endl;
            return;
        }
        pptrTemp = pptrTemp->getNext();
    }
    GroupNode* node = new GroupNode(name);
    gList->insert(node);
    cout << name << ": group" << endl;
}

void shapeInsertion(GroupNode* groupNode, string name, string type, int x_loc, int y_loc, int x_size, int y_size) {
    GroupNode* node = gList->getHead();
    if (name == "shape" || name == "group" || name == "move" || name == "delete" || name == "draw" || name == "pool") {
        cout << "error: invalid name" <<  endl;
        return;
    }
    while (node != nullptr) {
        if (node->getName() == name) {
            cout << "error: name " << name << " exists" << endl;
            return;
        }
        node = node->getNext();
    }
    ShapeNode* shapeNode = new ShapeNode(); 
    shapeNode->setShape(new Shape(name, type, x_loc, y_loc, x_size, y_size));
    groupNode->getShapeList()->insert(shapeNode); 
    shapeNode->print();
}

void deleting(string name) {
    GroupNode* pptrTemp = gList->getHead();
    if (name == "shape" || name == "group" || name == "move" || name == "delete" || name == "draw" || name == "pool") {
        cout << "error: invalid name" <<  endl;
        return;
    }
    while (pptrTemp != nullptr) {
        if (pptrTemp->getShapeList()->find(name)) {
            delete pptrTemp->getShapeList()->remove(name);
            cout << name << ": deleted" << endl;
            return;
        }
        if (pptrTemp->getName() == name) {
            gList->getHead()->getShapeList()->insert(pptrTemp->getShapeList()->getHead());
            pptrTemp->getShapeList()->setHead(nullptr);
            delete gList->remove(name);
            cout << name << ": deleted" << endl;
            return;
        }
        pptrTemp = pptrTemp->getNext();
    }
    cout << "error: shape " << name << " not found" << endl;
}

void shapeMoves(string shape, string group) {
    GroupNode* gNode = nullptr;
    GroupNode* sNode = nullptr;
    GroupNode* pptrTemp = gList->getHead();
    while (pptrTemp != nullptr) {
        if (sNode == nullptr && pptrTemp->getShapeList()->find(shape))
            sNode = pptrTemp;
        if (gNode == nullptr && pptrTemp->getName() == group) 
            gNode = pptrTemp;
        if (gNode && sNode)
            break;
        pptrTemp = pptrTemp->getNext();
    }
    if (gNode == nullptr) {
        cout << "error: group " << group << " not found" << endl;
        return;
    }
    if (sNode == nullptr) {
        cout << "error: shape " << shape << " not found" << endl;
        return;
    }
    gNode->getShapeList()->insert(sNode->getShapeList()->remove(shape));
    cout << "moved " << shape << " to " << group << endl;
}