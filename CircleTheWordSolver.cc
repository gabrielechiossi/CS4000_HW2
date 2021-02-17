#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include "CircleTheWordSolver.h"
using namespace std;

vector<pair<int, int> > word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist){
    vector<pair<int, int> > prov;
       for(int i = 0; i < wordlist.size(); i++){
              string temp = wordlist[i];
              vector<pair<int, int> > locations;
              locations = find(&puzzle, temp);
              prov[i] = locations;
       }
       return prov;
}

vector<pair<int, int> > find(vector<vector<char> > &puzzle, string temp){
       int c = 0;
       vector<pair<int, int> > position;
       for(int y = 0; y < puzzle.size(); y++){
              for(int x = 0; x < puzzle.size(); x++){
                     if(temp[c] == puzzle[x][y]){
                            position = move(puzzle, temp, x , y);
                            if(position != make_pair(-1, -1)){
                                   return position;
                            }else{
                                  break; 
                            }
                     }
              }
       }
       position.back().first = -1;
       position.back().second = -1;
       return position;
}

vector<pair<int, int> > move(vector<vector<char> > &puzzle, string temp, int x, int y){
       int l = temp.length();
       int posx, posy;
       vector<pair<int, int> > initialPosition;
       for(int i = 0; i < 8; i++){
              int counter = 1;
              if(i == 0){
                     for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x][y+j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y+j;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }else if(i == 1){
                     for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x-j][y+j]){
                                   if(j == 1){
                                          posx = x-j;
                                          posy = y+j;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }else if(i == 2){
                   for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x-j][y]){
                                   if(j == 1){
                                          posx = x-j;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }  
              }else if(i == 3){
                     for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x-j][y-j]){
                                   if(j == 1){
                                          posx = x-j;
                                          posy = y-j;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }  
              }else if(i == 4){
                     for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x][y-j]){
                                   if(j == 1){
                                          posx = x;
                                          posy = y-j;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }  
              }else if(i == 5){
                     for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x+j][y-j]){
                                   if(j == 1){
                                          posx = x+j;
                                          posy = y-j;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }else if(i == 6){
                    for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x+j][y]){
                                   if(j == 1){
                                          posx = x+j;
                                          posy = y;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     } 
              }else if(i == 7){
                     for(int j = 1; j < puzzle.size(); j++){
                            if(temp[j] == puzzle[x+j][y+j]){
                                   if(j == 1){
                                          posx = x+j;
                                          posy = y+j;
                                   }
                                   counter++;
                            }else{
                                   break;
                            }
                     }
              }
              if(counter == l){
                    initialPosition.back().first = posx;
                    initialPosition.back().second = posy;
                    return initialPosition;
              }
       }
       initialPosition.back().first = -1;
       initialPosition.back().second = -1;
       return initialPosition;
}