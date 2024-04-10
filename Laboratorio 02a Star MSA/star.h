#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <unistd.h>
#include <vector>
using namespace std;

char obtenerBaseComplementaria(char base) {
  switch (base) {
  case 'A':
    return 'T';
  case 'T':
    return 'A';
  case 'C':
    return 'G';
  case 'G':
    return 'C';
  default:
    return base;
  }
}

string Bcomp(const string &cadena) {
  string complementaria = "";
  for (char base : cadena) {
    complementaria += obtenerBaseComplementaria(base);
  }
  return complementaria;
}

void readSeq(vector<string> &sq, string name) {
  ifstream archivo(name + ".txt");
  if (!archivo)
    return;
  string linea;
  while (getline(archivo, linea))
    sq.push_back(linea);
  archivo.close();
}

int arrMax(vector<int> arr) {

  int mayor = arr[0];
  int indice = 0;
  for (int i = 1; i < arr.size(); ++i) {
    if (arr[i] > mayor) {
      mayor = arr[i];
      indice = i;
    }
  }
  return indice;
}

