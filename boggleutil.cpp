//Malcolm Samuel <m1samuel>

#include <cstdlib>
#include"boggleutil.h"
#include "iostream"

//This file contains all function definition for ternary trie which is used for maintaining the lexicon
TrieNode::TrieNode(char ch){
    isLast = false;
    c = ch;
    left = right = middle = nullptr;
}
    
char TrieNode::getSymbol(){
    return c;
}

TrieNode *TrieNode::getLeft(){
    return left;
}

TrieNode *TrieNode::getMid(){
    return middle;
}

TrieNode *TrieNode::getRight(){
    return right;
}

void TrieNode::setLeft(TrieNode*l){
    left = l;
}

void TrieNode::setMid(TrieNode*m){
    middle = m;
}

void TrieNode::setRight(TrieNode*r){
    right = r;
}

void TrieNode::setSymbol(int n){
    c = n;
}

bool TrieNode::isLastSymbolInLexeme(){
    return isLast;
}

void TrieNode::setLast(){
    isLast = true;
}

TrieNode *TernaryTrie::insert(TrieNode *n, std::string s, unsigned int i){
    if (n == nullptr)
        n = new TrieNode(s[i]);
    if (s[i] < n->getSymbol()){
        n->setLeft(insert(n->getLeft(),s,i));
    } else if (s[i] > n->getSymbol()){
        n->setRight(insert(n->getRight(),s,i));
    } else {
        if (i + 1 == s.length()) {
            n->setLast();
        } else {
            n->setMid(insert(n->getMid(),s,i+1));
        }
    }
    return n;
}

TernaryTrie::TernaryTrie(){
    root = nullptr;
}

TernaryTrie::~TernaryTrie(){
    deleteTrie(root);
}

void TernaryTrie::deleteTrie(TrieNode *n){
    if (n->getLeft() != nullptr)
        deleteTrie(n->getLeft());
    if (n->getRight() != nullptr)
        deleteTrie(n->getRight());
    if (n->getMid() != nullptr)
        deleteTrie(n->getMid());
    delete n;
}

//builds the trie by setting root to insert which is recursively called
void TernaryTrie::buildTree(const std::vector<std::string>& words){
    for (unsigned i = 0; i < words.size(); i++)
        root = insert(root, words[i], 0);
}

//will determine if a given word is in the lexicon
int TernaryTrie::find(const std::string &word_to_check){
    TrieNode *curr;
    curr = root;
    unsigned int i = 0;
    while (curr) {
        if (word_to_check[i] < curr->getSymbol()) {
            curr = curr->getLeft();
        } else if (word_to_check[i] > curr->getSymbol()) {
            curr = curr->getRight();
        } else {
            if (i+1 == word_to_check.length() && curr->isLastSymbolInLexeme()){
                return (int)word_to_check.length();
            } else if (i+1 == word_to_check.length() && !curr->isLastSymbolInLexeme()){
                return -1;
            }
            curr = curr->getMid();
            i++;
        }
    }
    return 0;
}
