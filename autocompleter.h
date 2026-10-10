
#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>

using namespace std;

class Autocompleter
{
	// For the mandatory running times below:
	// Assume that the length of every string is O(1). 

	public:
		// Creates a new Autocompleter with an empty dictionary.
		//
		// Must run in O(1) time.
		Autocompiler::Autocompleter()
		{
			//creating the root and setting count take O(1)
			root = new Node;
			count = 0;
		}

		// Adds a string x to the dictionary.
		// If x is already in the dictionary, does nothing.
		//
		// Must run in O(1) time.
		void Autocompiler::insert(string x, int freq)
		{
			node* arrow = root;		//arrow ponts at root to traverse the trie
			vector<Node*> path;		//vector to store the path of nodes traversed	

			//visit each character of string x
			if(arrow->children[x[i]] == nullptr)		//if there is no next character
				arrow->children[x[i]] = new Node;		//create new node for next character

			arrow = arrow->children[x[i]];				//update/move arrow to the children of current node

			
		}

		// Returns the number of strings in the dictionary.
		// 
		// Must run in O(1) time.
		int Autocompiler::size();

		// Fills the vector T with the three most-frequent completions of x.
		// If x has less than three completions, then 
		// T is filled with all completions of x.
		// The completions appear in T from most to least frequent.
		// 
		// Must run in O(1) time.
		void Autocompiler::completions(string x, vector<string> &T);

	private:
		// A helper class that stores a string and a frequency.
		class Entry
		{
			public:
				string s;
				int freq; 
		};

		// A helper class that implements a trie node.
		class Node
		{
			public:
				Node()
				{
					this->marked = false;
					for (int i = 0; i < 256; ++i)
						children[i] = nullptr; 
				}

				bool marked;
				vector<Entry> top;
				Node* children[256];
		};

		// Root of the trie-based data structure
		Node* root;

		// Number of marked nodes in the trie-based data structure
		int count;
};

#endif
