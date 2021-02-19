#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include "CircleTheWordSolver.h"
#include "omp.h"
using namespace std;

vector<pair<int, int> > CircleTheWordSolver::word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist){
    vector<pair<int, int> > prov;
    #pragma omp parallel for num_threads(4)
       for(int i = 0; i < wordlist.size(); i++){
              #pragma omp critical
              {
                     string temp = wordlist[i];
                     prov.push_back(findLetter(puzzle, temp));
              }
              
       }
       return prov;
}

pair<int, int> CircleTheWordSolver::findLetter(vector<vector<char> > &puzzle, string temp){
       int c = 0;
       pair<int, int> position;
       #pragma omp parallel for num_threads(4)
       for(int y = 0; y < puzzle.size(); y++){
              for(int x = 0; x < puzzle.size(); x++){
                     if(temp[c] == puzzle[x][y]){
                            position = moveLetter(puzzle, temp, x , y);
                            if(position != make_pair(-1, -1)){
                                   return position;
                            }
                     }
              }
       }
       position.first = -1;
       position.second = -1;
       return position;
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