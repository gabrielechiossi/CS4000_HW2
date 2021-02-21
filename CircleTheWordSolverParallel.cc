#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <array>
#include "CircleTheWordSolver.h"
#include <omp.h>
using namespace std;

vector<pair<int, int> > CircleTheWordSolver::word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist){
    vector<pair<int, int> > prov;
    string temp[wordlist.size()];
    char temp2[wordlist.size()];
       for(int i = 0; i < wordlist.size(); i++){
            temp[i] = wordlist[i];
            string firstLetter = temp[i];
            temp2[i] = firstLetter[0];     
       }
       prov = findLetter(puzzle, temp, temp2, wordlist.size());
       return prov;
}

vector<pair<int, int> > CircleTheWordSolver::findLetter(vector<vector<char> > &puzzle, string temp[], char temp2[], int wordcount){
       vector<pair<int, int> >position;
       vector<pair<int, int> > final;
       vector<vector<pair<int, int> > > arr;
       string words [4][wordcount];
       char fLetter[4][wordcount];
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
       #pragma omp parallel for num_threads(4)
       for(int y = 0; y < puzzle.size(); y++){
              for(int x = 0; x < puzzle.size(); x++){
                     for(int c = 0; c < wordcount; c++){
                            if(fLetter[omp_get_thread_num()][c] == puzzle[x][y]){
                                   position[omp_get_thread_num()] = moveLetter(puzzle, words[omp_get_thread_num()][c], x , y);
                                          if((position[omp_get_thread_num()].first != -1) && (position[omp_get_thread_num()].second != -1)){
                                                 arr[omp_get_thread_num()][c] = position[omp_get_thread_num()];
                                          } 
                            }
                     } 
              }
       }
       cout << endl;
       for(int i = 0; i < 4; i++){
              for(int c = 0; c < wordcount; c++){
                     if(arr[i][c] != make_pair(-1, -1)){
                            final[c] = arr[i][c];
                     }
              }  
       }
       return final;
}

pair<int, int> CircleTheWordSolver::moveLetter(vector<vector<char> > &puzzle, string temp, int x, int y){
       int l = temp.length();
       int posx, posy;
       pair<int, int> initialPosition;
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