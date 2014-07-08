//Malcolm Samuel <m1samuel>

#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "boggleplayer.h"
#include "iostream"


//Build the ternary trie used for the lexicon
void BogglePlayer::buildLexicon(const set<string>& word_list){
    std::srand(unsigned(std::time(0)));
    vector<string> words;
    set<string>::iterator it;
    for (it = word_list.begin(); it != word_list.end(); it++)
        words.push_back(*it);
    std::random_shuffle(words.begin(), words.end());
    lexTrie = new TernaryTrie();
    lexTrie->buildTree(words);
    buildLexiconCalled = true;
}

//set the board for the game
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
    c = cols;
    n = rows*cols;
    visited = new int[n];
    board = new string[rows*cols];
    int k = 0;
    for (unsigned i = 0; i < rows; i++){
        for (unsigned j = 0; j < cols; j++){
            board[k] = strToLower(diceArray[i][j]);
            k++;
        }
    }
    setBoardCalled = true;
}

//will return all valid words currently on the board.
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
    if (!(setBoardCalled || buildLexiconCalled)) return false;
    for (int i = 0; i < n; i++) {
        memset(visited, 0, n*sizeof(*visited));
        visited[i] = 1;
        getAllValidWords(board[i], i, 1, minimum_word_length, words);
    }
    return true;
}

//helper fn for above

void BogglePlayer::getAllValidWords(string w, int bi, int nv, unsigned int ml,set<string>*& words){
    if (w.length() >= ml){
        if (lexTrie->find(w) > 0) {
            words->insert(w);
        } else if (lexTrie->find(w) == 0) return;
    }
    int adj[8] = {bi-c-1,bi-c,bi-c+1,bi+1,bi+c+1,bi+c,bi+c-1,bi-1};
    int y = adj[0];
    for (int i = 0; i < 8; i++) {
        if (isValidAdj(bi, y)) {
            visited[y] = 1;
            getAllValidWords(w + board[y], y, nv + 1, ml, words);
            visited[y] = 0;
        }
        if (i != 8) y = adj[i+1];
    }
}

//checks to see if word is in lexicon
bool BogglePlayer::isInLexicon(const string& word_to_check) {
    if (!buildLexiconCalled) return false;
    if (lexTrie->find(word_to_check) > 0) return true;
    return false;
}

//helper fn for below
inline void BogglePlayer::isOnBoard(string wordRemaining, vector<int> &pathSoFar){
    if (wordRemaining.length() == 0) {done = true; return;}
    int x = pathSoFar[pathSoFar.size()-1];
    int adj[8] = {x-c-1,x-c,x-c+1,x+1,x+c+1,x+c,x+c-1,x-1};
    int y = adj[0];
    for (int i = 0; i < 8; i++) {
        if (!done && isValidAdj(x,y,wordRemaining)) {
            pathSoFar.push_back(y);
            visited[y] = 1;
            isOnBoard(wordRemaining.substr(board[y].length(),wordRemaining.length()), pathSoFar);
            if (done) return;
        }
        if (i != 8) y = adj[i+1];
    }
    if (wordRemaining.length() != 0) {
        visited[x] = 0;
        pathSoFar.pop_back();
    }
}

//checks if a word is on the board
inline vector<int> BogglePlayer::isOnBoard(const string& word) {
    string lcs = strToLower(word);
    result->resize(0);
    if (!setBoardCalled) return *result;
    for (int j = 0; j < n; j++){
        if (std::strcmp(board[j].c_str(), lcs.substr(0,board[j].length()).c_str()) == 0) {
            done = false;
            std::memset(visited, 0, n*sizeof(*visited));
            visited[j] = 1;
            result->push_back(j);
            isOnBoard(lcs.substr(board[j].length(),lcs.length()), *result);
        }
        if (!result->empty()) return *result;
    }
    return *result;
}

//checks if adj selected from array of adjacencies is indeed valid
inline bool BogglePlayer::isValidAdj(int &x, int &y, string &wordRemaining){
    return (y >= 0 && y < n)
    && !(x%c==0&&(y==x-1 || y==x-c-1 || y==x+c-1))
    && !(y%c==0&&x==y-1)
    && !(x%c==c-1&&y%c==0)
    && visited[y] == 0
    && std::strcmp(board[y].c_str(),wordRemaining.substr(0,board[y].length()).c_str()) == 0;
}

inline bool BogglePlayer::isValidAdj(int &x, int &y){
    return (y >= 0 && y < n)
    && !(x%c==0&&(y==x-1 || y==x-c-1 || y==x+c-1))
    && !(y%c==0&&x==y-1)
    && !(x%c==c-1&&y%c==0)
    && visited[y] == 0;
}
//to convert strings on board or inputted to lower case
inline string BogglePlayer::strToLower(string word){
    string lcs = "";
    for (unsigned i = 0; i < word.length(); i++)
        lcs += tolower(word[i]);
    return lcs;
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {}

