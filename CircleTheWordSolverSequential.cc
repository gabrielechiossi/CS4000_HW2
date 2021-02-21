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
       pair<int, int> position;
       vector<pair<int, int> > final;
       final.reserve(wordcount);
       final.resize(wordcount);
       for(int i = 0; i < wordcount; i++){
              final[i] = make_pair(-1, -1);
       }
       for(int y = 0; y < puzzle.size(); y++){
              for(int x = 0; x < puzzle.size(); x++){
                     {
                            int c = 0;
                            do{
                                   if(temp2[c] == puzzle[x][y]){
                                   position = moveLetter(puzzle, temp[c], x , y);
                                   if(position != make_pair(-1, -1)){
                                          final[c] = position;
                                   } 
                                   }
                                   c++;
                            }while(c < wordcount);  
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