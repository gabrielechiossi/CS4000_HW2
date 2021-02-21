/**
 *   @file: CircleTheWordSolver.h
 * @author: Gabriele Chiossi
 *   @date: 02/21/21
 */
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
  //function given to initialize the matrix and the words given to find 
  vector<pair<int, int> > word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist);
  //findLetter scan the matrix and finds every instance of the first letter of a word given
  vector<pair<int, int> > findLetter(vector<vector<char> > &puzzle, string temp[], char temp2[], int wordcount);
  //moveLetter finds the exact x and y position of the beginning of a word given
  pair<int, int> moveLetter(vector<vector<char> > &puzzle, string temp, int x, int y);
};
#endif


 

