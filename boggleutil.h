//Malcolm Samuel <m1samuel>

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.
#endif

#include <vector>
#include <string>
#include <set>

class TrieNode{
public:
    TrieNode(char);
    void setSymbol(int);
    void setLast();
    bool isLastSymbolInLexeme();
    char getSymbol();
    TrieNode *getLeft();
    TrieNode *getRight();
    TrieNode *getMid();
    void setLeft(TrieNode*);
    void setRight(TrieNode*);
    void setMid(TrieNode*);
private:
    bool isLast;
    char c;
    TrieNode *left,*middle,*right;
};

class TernaryTrie{
public:
    TernaryTrie();
    ~TernaryTrie();
    void deleteTrie(TrieNode*);
    TrieNode *top(){return root;}
    TrieNode *insert(TrieNode*,std::string,unsigned int);
    int find(const std::string&);
    void buildTree(const std::vector<std::string>&);
private:
    TrieNode *root;
};

