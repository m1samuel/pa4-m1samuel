#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>
#include <thread>
#include <cstdlib>

int main (int argc, char* argv[]) {
    set<string> words;
    vector<int> locations;
    BaseBogglePlayer * p = new BogglePlayer();
    set<string> lex;
    std::ifstream in("/Users/m2/Desktop/pa4/pa4/brd.txt");
    string n, m;
    getline(in, n);
    getline(in, m);
    int r = std::atoi(n.c_str());
    int c = std::atoi(m.c_str());
    string **board = new string*[c];
    for (int i = 0; i < r; i++)
        board[i] = new string[c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            getline(in, board[i][j]);
            //cout << board[i][j] << " ";
        }
        //cout << "\n";
    }
    in.close();
    in.open("/Users/m2/Desktop/pa4/pa4/lex.txt");
    string line;
    while (in.good()) {
        getline(in, line);
        if (in.good()) lex.insert(line);
    }
  /*string wordA("nod");
  string wordB("where");
  string wordC("do");
  string wordD("we");
  string wordE("go");
  string wordX("fvrst");
  lex.insert(wordA);
  lex.insert(wordC);
  lex.insert(wordD);
  lex.insert(wordE);
  lex.insert(wordB);
  string row0[] = {"a","a","a","fv","a","a","a","a"};
  string row1[] = {"e","f","g","h","rst","a","i","v"};
  string row2[] = {"i","j","k", "l","r","a","i","v"};
  string row3[] = {"r","a","i","v","a","c","d","f"};
  string* board[] = {row0,row1,row2,row3};*/


  p->buildLexicon(lex);

  p->setBoard(r,c,board);

  /*if(p->isInLexicon(wordX)) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }
  if(!p->isInLexicon(wordA) || !p->isInLexicon(wordB)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }
    locations = p->isOnBoard(wordX);
  if(p->isOnBoard(wordX).size() > 0) {
      for (int i = 0; i < locations.size(); i++) std::cout << locations[i] << " " << board[(locations[i]-locations[i]%8)/8][locations[i]%8] << "\n";
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }
  locations.clear();
  locations = p->isOnBoard(wordA);
  if(locations.size() != 3 || locations[0] != 3) {
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    return -1;
  }*/
  if(!p->getAllValidWords(2,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  };
 /*if(words.size() != 2 || words.count(wordA) != 1) {
      std::set<string>::iterator it;
      for (it = words.begin(); it != words.end(); ++it)
          std::cout << *it << "\n";
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  }*/
  delete p;
  return 0;

}
