//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below
// 

#include "GroupList.h"

GroupList::GroupList() {
    head = nullptr;
}

GroupList::~GroupList() {
	while (head != nullptr) {
                    GroupNode* node = head->getNext();
		delete head;
		head = node;
	}
}

GroupNode* GroupList::getHead() const {
	return head;
}

void GroupList::setHead(GroupNode* ptr) {
	head = ptr;
}

void GroupList::insert(GroupNode* s) {
    GroupNode* node = head;
	if (head == nullptr) {
		head = s;
		return;
	}	
        while (node->getNext() != nullptr)
		node = node->getNext();
	node->setNext(s);
}

GroupNode* GroupList::remove(string name) {
    	GroupNode* node = head;
	if (head == nullptr)
		return nullptr;
	if (head && head->getName() == name) {
		GroupNode* pptrTemp = head;
		head = head->getNext();
		pptrTemp->setNext(nullptr);
		return pptrTemp;
	}
	while (node->getNext() != nullptr) {
		if (node->getNext()->getName() == name) {
			GroupNode* pptrTemp = node->getNext();
			node->setNext(node->getNext()->getNext());
			pptrTemp->setNext(nullptr);
			return pptrTemp;
		}
		node = node->getNext();
	}
	return nullptr;
}

void GroupList::print() const {
	GroupNode* node = head;
	while (node != nullptr)
	{
		node->print();
		node = node->getNext();
	}
}