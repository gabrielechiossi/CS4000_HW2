/**
 *   @file: CircleTheWordSolverParallel.cc
 * @author: Gabriele Chiossi
 *   @date: 02/21/21
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include "CircleTheWordSolver.h"
#include <omp.h>
using namespace std;

//word_locations we initialize all the variables needed to solve this game
vector<pair<int, int> > CircleTheWordSolver::word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist){
       vector<pair<int, int> > prov;
       string temp[wordlist.size()];
       char temp2[wordlist.size()];
       //in this for loop below we make two array one containing the words given and the other 
       //one containing the first char of every word given
       for(int i = 0; i < wordlist.size(); i++){
              temp[i] = wordlist[i];
              string firstLetter = temp[i];
              temp2[i] = firstLetter[0];     
       }
       //here we call findLetter to solve this game
       prov = findLetter(puzzle, temp, temp2, wordlist.size());
       return prov;
}

//findLetter is the hearth of the algorithm where most of th works happens
vector<pair<int, int> > CircleTheWordSolver::findLetter(vector<vector<char> > &puzzle, string temp[], char temp2[], int wordcount){
       vector<pair<int, int> >position;
       vector<pair<int, int> > final;
       vector<vector<pair<int, int> > > arr;
       string words [4][wordcount];
       char fLetter[4][wordcount];
       //from line 46 until line 68 the variables are getting initialize so segmentation fault 
       //error won't happen and also initializing the locations of the words to not found to 
       //make the algorithm later easier to execute

       //in the parallel version of this program we have to have 2d vector or array to avoid
       //race condition because if we would not we might end up with a different output than expected
       for(int i = 0; i < 4; i++){
              for(int j = 0; j < wordcount; j++){
                     words[i][j] = temp[j];
                     fLetter[i][j] = temp2[j];
              }
       }
       arr.reserve(wordcount);
       arr[0].resize(wordcount);
       arr[1].resize(wordcount);
       arr[2].resize(wordcount);
       arr[3].resize(wordcount);
       position.reserve(wordcount);
       position.resize(wordcount);
       final.reserve(wordcount);
       final.resize(wordcount);
       for(int i = 0; i < 4; i++){
              for(int j = 0; j < wordcount; j++){
                     arr[i][j] = make_pair(-1, -1);
              }
       }
       for(int i = 0; i < wordcount; i++){
              final[i] = make_pair(-1, -1);
       }
       //here is where the algorithm runs in parallel
       #pragma omp parallel for num_threads(4)
       for(int y = 0; y < puzzle.size(); y++){
              for(int x = 0; x < puzzle.size(); x++){
                     for(int c = 0; c < wordcount; c++){
                            //here we can see why we needed these 2d arrays and vectors to avoid that
                            //same variables are being share between different threads causing the
                            //output to be not right or expected

                            //this if check if the letter in the matrix corrispond to any first letter of
                            //any of the words given
                            if(fLetter[omp_get_thread_num()][c] == puzzle[x][y]){
                                   //if so we call moveLetter and check if the letter in the matrix is actally
                                   //the first letter of the words or not
                                   position[omp_get_thread_num()] = moveLetter(puzzle, words[omp_get_thread_num()][c], x , y);
                                   //if it is the first letter of the words means we found the position x and y and we save it
                                   //in arr
                                          if((position[omp_get_thread_num()].first != -1) && (position[omp_get_thread_num()].second != -1)){
                                                 arr[omp_get_thread_num()][c] = position[omp_get_thread_num()];
                                          } 
                            }
                     } 
              }
       }
       //here is where we merge arr that is a 2d vector to just one vector
       for(int i = 0; i < 4; i++){
              for(int c = 0; c < wordcount; c++){
                     //we check if arr has any "found" location if so they get copy in the main 1d vector
                     if(arr[i][c] != make_pair(-1, -1)){
                            final[c] = arr[i][c];
                     }
              }  
       }
       return final;
}

//moveLetter finds if the location x and y found is a valid position by checking all the other letter
pair<int, int> CircleTheWordSolver::moveLetter(vector<vector<char> > &puzzle, string temp, int x, int y){
       int l = temp.length();
       int posx, posy;
       pair<int, int> initialPosition;
       //this is a bruteforce solution
       //in fact we check all 8 directions if a word is found in any directions the locations of the
       //first letter of a word gets saved and send to findLetter if not the location x and y that
       //is been sent to this function gets mark with -1, -1 that means that is not a valid location
       for(int i = 0; i < 8; i++){
              int counter = 1;
              if(i == 0){
                     for(int j = 1; j < l; j++){
                            if(y+j < puzzle.size() && temp[j] == puzzle[x][y+j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }else if(i == 1){
                     for(int j = 1; j < l; j++){
                            if((y+j < puzzle.size() && x-j > -1) && temp[j] == puzzle[x-j][y+j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }else if(i == 2){
                   for(int j = 1; j < l; j++){
                            if(x-j > -1 && temp[j] == puzzle[x-j][y]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }  
              }else if(i == 3){
                     for(int j = 1; j < l; j++){
                            if((y-j > -1 && x-j > -1) && temp[j] == puzzle[x-j][y-j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }  
              }else if(i == 4){
                     for(int j = 1; j < l; j++){
                            if(y-j > -1 && temp[j] == puzzle[x][y-j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }  
              }else if(i == 5){
                     for(int j = 1; j < l; j++){
                            if((y-j > -1 && x+j < puzzle.size()) && temp[j] == puzzle[x+j][y-j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }else if(i == 6){
                    for(int j = 1; j < l; j++){
                            if(x+j < puzzle.size() && temp[j] == puzzle[x+j][y]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     } 
              }else if(i == 7){
                     for(int j = 1; j < l; j++){
                            if((y+j < puzzle.size() && x+j < puzzle.size()) && temp[j] == puzzle[x+j][y+j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }
              if(counter == l){
                    initialPosition.first = posy;
                    initialPosition.second = posx;
                    return initialPosition;
              }
       }
       initialPosition.first = -1;
       initialPosition.second = -1;
       return initialPosition;
}