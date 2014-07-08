//Malcolm Samuel <m1samuel>

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"


class BogglePlayer : public BaseBogglePlayer {
  public:
    void buildLexicon(const set<string>& word_list);
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    bool isInLexicon(const string& word_to_check);
    vector<int> isOnBoard(const string& word);
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
    BogglePlayer(){setBoardCalled = buildLexiconCalled = false; result = new vector<int>();}
    ~BogglePlayer() {delete []board; delete lexTrie; delete []visited;}
  private:
    void getAllValidWords(string, int, int, unsigned int,set<string>*&);
    void isOnBoard(string wordRemaining, vector<int> &pathSoFar);
    bool isValidAdj(int&, int&, string&);
    bool isValidAdj(int&, int&);
    string strToLower(string word);
    string *board;
    TernaryTrie *lexTrie;
    vector<int> *result;
    int *visited;
    bool setBoardCalled, buildLexiconCalled, done;
    int c,n;
};

#endif
