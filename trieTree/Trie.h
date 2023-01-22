#pragma once

#include <iostream>
#include <string>
using namespace std;

// Alphabet size (# of symbols). 
#define ALPHABET_SIZE (26) 

// Converts key current character into index use only 'a' through 'z' and lower case. 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

// trie node 
struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE] {nullptr} ; //all pointers are null.

	// isWordEnd is true if the node represents end of a word. 
	bool isWordEnd = false; // as a default.
};

class Trie
{
	TrieNode* root;

public:

	//ctor
	Trie() { root = new TrieNode(); }

	//dtor
	~Trie();

	/// <summary>
	/// Insert a new word to the tree.
	/// </summary>
	/// <param name="wrd">The word to add</param>
	/// <returns>True if the word not exist alraedy and false if the ward is in the tree already</returns>
	bool insert(string wrd) { return insertT(root, wrd); }

	/// <summary>
	/// Delete word from the tree.
	/// </summary>
	/// <param name="wrd">Word to delete</param>
	/// <returns>True if the word have been in tree</returns>
	bool delW(string wrd);

	/// <summary>
	/// Search word/key in the tree.
	/// </summary>
	/// <param name="key">Word to search</param>
	/// <returns>True if the word exist in tree</returns>
	bool search(string key) { return searchT(root, key); }

	/// <summary>
	/// Get a word and suggest words which this word is prefix of.
	/// </summary>
	/// <param name="wrd">prefix</param>
	/// <returns> return 0 if there are no words with this prefix</returns>
	int printAutoSuggestions(string wrd) { return printAutoSuggestionsT(root, wrd); }

	/// <summary>
	/// Print all tree in a hierarchical way.
	/// </summary>
	void printTrie() { printT(root); }

private:

	/// <summary>
	/// recursive function which actually insert the new word.
	/// </summary>
	/// <param name="curr">Pointer to node</param>
	/// <param name="key">woed to insret</param>
	/// <returns>True if the word not exist alraedy and false if the ward is in the tree already</returns>
	bool insertT(TrieNode* curr, string key);

	/// <summary>
	/// //Recursive function to delete a key from given Trie.
	/// </summary>
	/// <param name="curr">Pointer to node</param>
	/// <param name="key">word to remove</param>
	/// <param name="depth">depth of rec</param>
	/// <returns></returns>
	TrieNode* remove(TrieNode* curr, string key, int depth = 0);

	/// <summary>
	/// Recursive search func to find a word in tree.
	/// </summary>
	/// <param name="curr">Pointer to node</param>
	/// <param name="key">Word to search</param>
	/// <returns>True if the word exist in tree</returns>
	bool searchT(TrieNode* curr, string key);

	/// <summary>
	/// rec func, print words suggestions which start with this prefix  
	/// </summary>
	/// <param name="curr">Pointer to node</param>
	/// <param name="currPrefix">curr prefix</param>
	void suggestionsRec(TrieNode* curr, string currPrefix);

	/// <summary>
	/// Get a word and Pointer to end of prefix. Suggest words which this word is prefix of
	/// </summary>
	/// <param name="root">Pointer to node</param>
	/// <param name="query">prefix</param>
	/// <returns></returns>
	int printAutoSuggestionsT(TrieNode* root, string query);

	/// <summary>
	/// Rec func to print all tree in a hierarchical way.
	/// </summary>
	/// <param name="curr">Pointer to node</param>
	/// <param name="str">space of hierarchical</param>
	void printT(TrieNode* curr, string str = "");

	/// <summary>
	/// chack if the list of root(children) is empty.
	/// </summary>
	/// <param name="root">:point to TrieNode who needed to chack</param>
	/// <returns>true if is empty</returns>
	bool isEmpty(TrieNode* root);

	/// <summary>
	/// Clear the tree.
	/// </summary>
	/// <param name="curr">Pointe to current node</param>
	void clear(TrieNode* curr);
};

