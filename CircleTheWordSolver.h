#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef DWJ_WORD_CIRCLE_DEF
#define DWJ_WORD_CIRCLE_DEF
class CircleTheWordSolver {
 public:
  vector<pair<int, int> > word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist);
  vector<pair<int, int> > find(vector<vector<char> > &puzzle, string temp);
  vector<pair<int, int> > move(vector<vector<char> > &puzzle, string temp, int x, int y);
  
};
#endif


 

