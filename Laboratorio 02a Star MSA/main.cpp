#include "alineamiento.h"
#include "star.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;



int main() {
  vector<string> cadenas;
  string name;
  cout << "Nombre txt: ";
  cin >> name;
  readSeq(cadenas, name);
  
  int len = cadenas.size();

  vector<vector<pair<int, string>>> seqScore(
      len, vector<pair<int, string>>(len, {0, ""}));

  
  pair<int, string> temp;
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      if (i == j)
        continue;
      globalAlineament(cadenas[i], cadenas[j], 10, temp);
      seqScore[i][j] = temp;
    }
  }

  vector<int> sumScore(len, 0);
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      sumScore[i] += seqScore[i][j].first;
    }
  }
  int mayorScore = arrMax(sumScore);
  cout <<"Seq "<<mayorScore <<", Score Max : " << sumScore[mayorScore] << endl;
  
  vector<pair<int, string>> bestArr = seqScore[mayorScore];
  sort(bestArr.begin(), bestArr.end());
  string sq = bestArr[0].second;
  size_t posicion_coma = sq.find(',');
  sq = sq.substr(posicion_coma + 1);
  
  vector<string> MultiAli;
  vector<int> index;
  MultiAli.push_back(sq);
  
  pair<int, string> temp2;
  size_t longitud_maxima = sq.length();
  for (int i = 0; i < len; i++) {
    if (i == mayorScore){
      index.insert(index.begin(),i);
      continue;
    }
      
    globalAlineament(sq, cadenas[i], 10, temp2);
    string sq2 = temp2.second;
    posicion_coma = sq2.find(',');
    sq2 = sq2.substr(0, posicion_coma);

    MultiAli.push_back(sq2);
    index.push_back(i);
    longitud_maxima = max(longitud_maxima, sq2.length());
  }

  for (auto &cadena : MultiAli)
    cadena.resize(longitud_maxima, '-');

  int iSeq= 0;
  for (auto i : MultiAli)
    cout<<"Seq "<< index[iSeq++]<< " : "<< i << endl;
}