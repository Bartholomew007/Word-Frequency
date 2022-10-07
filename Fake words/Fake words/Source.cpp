#include <cstdlib>
#include <iostream>
#include <string>
#include "Node.h"
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std::chrono;

//Eduardo Saldana
//Francisco Hernandez
//Daniel Masamba

using namespace std;

void insertion(string word, Node* root) {        //function used to make the BST using the words from the input file

	if (root == nullptr) {
		Node* node = new Node(word);
		return;
	}
	if (word == root->key) {
		root->count++;
		return;
	}
	if (root->key > word) {
		if (root->left == nullptr) {
			root->left = new Node(word);
			return;
		}
		insertion(word, root->left);
	}
	if (root->key < word) {
		if (root->right == nullptr) {
			root->right = new Node(word);
			return;
		}
		insertion(word, root->right);
	}

}

void print(Node* root, ofstream& outFile, vector<string>& A, multimap<int, string>& M) {          //function used to print whether the words are fake or not and populates the multimap with all the fake words
	
	if (root == nullptr) {
		return;
	}
	int s, n, m;
	s = 0;
	n = A.size()-1;
	bool flag=false;
	
	while (( s<=n)) {
		m = (s + n) / 2;
		
		if (A[m] == root->key) {
			outFile << root->key << " " << root->count << endl;
			flag = true;
			break;
		}
		else if (A[m] < root->key) {
			s = m + 1;
		}
		else if (A[m] > root->key) {
			n = m - 1;
		}
	
		
	}
	if (flag == false) {

		outFile << "(fake word) " << root->key << " " << root->count << endl;
		M.insert(pair<int, string>(root->count, root->key));
		
	}
	
	print(root->left, outFile, A, M);
	print(root->right, outFile, A, M);
	
}



int main() {
	auto start = high_resolution_clock::now();

	multimap<int, string> L;

	Node* root = new Node("");
	ifstream whale;
	ofstream output;
	ifstream fake;
	ofstream word_output;
	
	vector<string> A;
	whale.open("whale.txt");
	output.open("wordCount.txt");
	fake.open("largedictionary.txt");
	word_output.open("topMistakes.txt");

	if (!(whale)) {               //function used to tell us whether the input file is found or not
		cout << "We could not find the text file.";
		return -1;

	}
	if (!(fake)) {               //function used to tell us if the input file is found or not
		cout << "We could not find the text file.";
		return -1;
	}

	while (!(whale.eof())) {       //populates the function with strings from the input file in order to make the BST
		string a = "";
		whale >> a;
		insertion(a, root);


	}
	while (!(fake.eof())) {       //populates the vector with the strings of the dictionary
		string b = "";
		fake >> b;
		A.push_back(b);
		
		
	}
	whale.close();
	
	print(root, output, A, L);
	output.close();
	multimap <int, string> ::reverse_iterator itr;
	
	fake.close();
	int count = 0;
	for (itr = L.rbegin();itr != L.rend();itr++) {        //uses the reverse of the multimap in order to print the fake word with the highest count first all the way to the 100th element
		if (count == 100) {
			break;
		}
		else {
			word_output << itr->second << " " << itr->first << endl;
			count++;
		}
	}
	word_output.close();


	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << duration.count() / 1000000 << "seconds " << endl;

}



