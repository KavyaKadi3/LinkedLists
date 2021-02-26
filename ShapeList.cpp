//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include "ShapeList.h"
using namespace std;

ShapeList::ShapeList() {
    head = nullptr;
}

ShapeList::~ShapeList() {
	while (head != nullptr) {
                    ShapeNode* node = head->getNext();
		delete head;
		head = node;
	}
}

ShapeNode* ShapeList::getHead() const {
	return head;
}

void ShapeList::setHead(ShapeNode* ptr) {
	head = ptr;
}

ShapeNode* ShapeList::find(string name) const {
	ShapeNode* node = head;
	while (node && node->getShape()->getName() != name)
		node = node->getNext();
	return node;
}

void ShapeList::insert(ShapeNode* s) {
	if (head == nullptr) {
		head = s;
		return;
	}
	ShapeNode* node = head;
	while (node->getNext() != nullptr)
		node = node->getNext();
	node->setNext(s);
}
ShapeNode* ShapeList::remove(string name) {
    	ShapeNode* node = head;
	if (head == nullptr)
		return nullptr;
	if (head && head->getShape()->getName() == name) {
		ShapeNode* pptrTemp = head;
		head = head->getNext();
		pptrTemp->setNext(nullptr);
		return pptrTemp;
	}
	while (node->getNext() != nullptr) {
		if (node->getNext()->getShape()->getName() == name) {
			ShapeNode* pptrTemp = node->getNext();
			node->setNext(node->getNext()->getNext());
			pptrTemp->setNext(nullptr);
			return pptrTemp;
		}
		node = node->getNext();
	}
	return nullptr;
}

void ShapeList::print() const {
	ShapeNode* node = head;
	while (node != nullptr)
	{
		node->print();
		node = node->getNext();
	}
}