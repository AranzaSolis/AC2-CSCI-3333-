
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
		Autocompleter()
		{
			//creating the root and setting count take O(1)
			root = new Node;
			count = 0;
		}

		// Adds a string x to the dictionary.
		// If x is already in the dictionary, does nothing.
		//
		// Must run in O(1) time.
		void insert(string x, int freq)
		{
			Node* arrow = root;		//arrow ponts at root to traverse the trie
			vector<Node*> path;		//vector to store the path of nodes traversed	
			path.push_back(root);	//saves root node once

			//loops through each character of the string x and creates a new node for each character if it does not exist in the trie
			for(int i=0; i<x.length(); i++)
			{
				//visit each character of string x
				if(arrow->children[x[i]] == nullptr)		//if there is no next character
					arrow->children[x[i]] = new Node;		//create new node for next character
			
				arrow = arrow->children[x[i]];				//update/move arrow to the children of current node
				path.push_back(arrow);						//store the current character node in the path vector
			}

			//If the word already exists, do nothing
        	if (arrow->marked)
            	return;

			arrow->marked = true;		//mark the last node of the path as true to complete the word
			count++;					//increment number of words in dictionary

			Entry e;		//create an entry to store the string and its frequency
			e.s = x;		//store the string in the entry
			e.freq = freq;	//store the frequency in the entry

			// THIS IS WHERE WE WILL STORE AND UPDATE TOP 3 COMPLETIONS
			//visit every node along the path of the word
			//O(1) time because the length of the string is O(1)
			for(int i=0; i<path.size(); i++)
			{
				Node* p = path[i];		//get the current node at index i of the path
				p->top.push_back(e);		//add the entry to the top vector of the current node
				
				// === sort candidates from highest to lowest frequency
				//O(1) because we compare AT MOST 4 entries (the new entry and the previous top 3 entries)
				//Compare the last entry with the entry before it.
				//Move the new entry toward the front if its frequency is higher.
				//There are at most 4 entries, so these comparisons take O(1).

				//Compare with top 3
				if (p->top.size() >= 4 &&
					p->top[3].freq > p->top[2].freq)
				{
					Entry temp = p->top[3];			//store entry 4 temporarily
					p->top[3] = p->top[2];			//Moves entry 3 to position 4
					p->top[2] = temp;				//move the saved entry 4 to position 3
				}

				//Compare with top 2
				if (p->top.size() >= 3 &&
					p->top[2].freq > p->top[1].freq)
				{
					Entry temp = p->top[2];			//store entry 3 temporarily
					p->top[2] = p->top[1];			//move entry 2 to position 3
					p->top[1] = temp;				//move the saved entry 3 to position 2
				}

				//Compare with top 1
				if (p->top.size() >= 2 &&
					p->top[1].freq > p->top[0].freq)
				{
					Entry temp = p->top[1];			//store entry 2 temporarily
					p->top[1] = p->top[0];			//move entry 1 to position 2
					p->top[0] = temp;				//move the saved entry 2 to position 1
				}

				// If there are more than 3 entries, remove the last entry
				if (p->top.size() > 3)
					p->top.pop_back();
			}

		
			
		// Returns the number of strings in the dictionary.
		// 
		// Must run in O(1) time.
		int size()
		{
			//O(1) time because it just returns the count of words in the dictionary
			return count;
		}

		// Fills the vector T with the three most-frequent completions of x.
		// If x has less than three completions, then 
		// T is filled with all completions of x.
		// The completions appear in T from most to least frequent.
		// 
		// Must run in O(1) time.
		void completions(string x, vector<string> &T)
		{
			//a prefix usually takes O(|x|) time to traverse the trie, 
			//but since we assume that the length of every string is O(1), 
			// it takes O(1) time to traverse the trie for a prefix

			T.clear();		//clear the vector T to store new completions

			Node* finger=root;	//start at root of node
			//traverse the trie to find the node corresponding to the prefix x
			for(int i=0; i<x.length(); i++)
			{
				if(finger->children[x[i]] == nullptr)
					return;		//if the prefix is not found, return empty vector
				finger = finger->children[x[i]];  //moves to the next character's node

			}

			//copies the stored top completions into T
			for(int i=0; i<finger->top.size(); i++)
				T.push_back(finger->top[i].s);		//adds each word to the result
		}


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
