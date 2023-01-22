#include "Trie.h"

Trie::~Trie()
{
	clear(root);
}

void Trie::clear(TrieNode* curr)
{
	if (!isEmpty(curr))
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (curr->children[i] != nullptr)
			{
				clear(curr->children[i]); // rec call for curr->children[i]
			}
		}
	}

	delete curr;
	curr = nullptr;
}

bool Trie::delW(string wrd)
{
	bool found = searchT(root, wrd); //chack if the word exist in tree.
	if(found)
		remove(root, wrd);

	return found;
}

bool Trie::insertT(TrieNode* curr, string key)
{

	if (key.size() == 0)
	{
		if (curr->isWordEnd)
			return false; // because the word is alredy exist.
		else
		{
			curr->isWordEnd = true;
			return true;
		}	
	}

	int index = CHAR_TO_INDEX(key[0]);

	if(curr->children[index] == nullptr)
		curr->children[index] = new TrieNode();

	return insertT(curr->children[index], key.erase(0, 1));
}

TrieNode* Trie::remove(TrieNode* curr, string key, int depth)
{
	// If tree is empty
	if (!curr)
		return NULL;

	// If last character of key is being processed
	if (depth == key.size()) {

		// This node is no more end of word after
		// removal of given key
		if (curr->isWordEnd)
			curr->isWordEnd = false;

		// If given is not prefix of any other word
		if (isEmpty(curr)) {
			delete (curr);
			curr = NULL;
		}

		return curr;
	}

	// If not last character, recur for the child
	// obtained using ASCII value
	int index = key[depth] - 'a';
	curr->children[index] =
		remove(curr->children[index], key, depth + 1);

	// If root does not have any child (its only child got
	// deleted), and it is not end of another word.
	if (isEmpty(curr) && curr->isWordEnd == false) {
		delete (curr);
		curr = NULL;
	}

	return curr;
}

bool Trie::searchT(TrieNode* curr, string key)
{
	int index = CHAR_TO_INDEX(key[0]);

	// In case the word is longer then required route.
	if (key.size() > 0 && curr->children[index] == nullptr)
		return false;

	// In case the all chars exist in tree, check if isWordEnd = true.
	if (key.size() == 0)
		return curr->isWordEnd;

	return searchT(curr->children[index], key.erase(0, 1));
}

void Trie::suggestionsRec(TrieNode* curr, string currPrefix)
{
	// found a string in Trie with the given prefix
	if (curr->isWordEnd)
		cout << currPrefix << endl;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (curr->children[i]) {
			// child node character value
			suggestionsRec(curr->children[i],
				currPrefix + char('a' + i));
		}
}

int Trie::printAutoSuggestionsT(TrieNode* root, string query)
{
	TrieNode* ptr = root;
	for (char c : query) {
		int ind = CHAR_TO_INDEX(c);

		// no string in the Trie has this prefix
		if (ptr->children[ind] == nullptr)
			return 0;

		ptr = ptr->children[ind];
	}

	// If prefix is present as a word, but
	// there is no subtree below the last
	// matching node.
	if (isEmpty(ptr)) {
		cout << query << endl;
		return -1;
	}

	//call to rec func to print all auto suggestions from the "ptr"
	suggestionsRec(ptr, query);
	return 1;
}

void Trie::printT(TrieNode* curr, string str)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (curr->children[i] != nullptr)
		{
			cout << str << (char)(i + 'a') << ":" << endl;
			printT(curr->children[i], str + "  "); // rec call for curr->children[i]
		}
	}
}

bool Trie::isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

