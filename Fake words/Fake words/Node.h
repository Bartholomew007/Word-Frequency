#pragma once
#pragma once

#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;
class Node
{
public:
	// We actually implement the constructor here,
	// in the header file (it's too little to "earn" a .cpp)
	Node(string n)
	{
		this->key = n;
		left = right = nullptr;
		count = 1;
	}

	string  key;
	Node* left;
	Node* right;
	int count;
};

#endif


