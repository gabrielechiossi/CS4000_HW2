#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <array>
#include <omp.h>
using namespace std;

#ifndef DWJ_WORD_CIRCLE_DEF
#define DWJ_WORD_CIRCLE_DEF
class CircleTheWordSolver {
 public:
  vector<pair<int, int> > word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist);
  vector<pair<int, int> > findLetter(vector<vector<char> > &puzzle, string temp[], char temp2[], int wordcount);
  pair<int, int> moveLetter(vector<vector<char> > &puzzle, string temp, int x, int y);

};
#endif


 

