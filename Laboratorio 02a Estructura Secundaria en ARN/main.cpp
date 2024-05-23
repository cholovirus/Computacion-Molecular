#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;
typedef vector<vector<pair<int,int>>> vvp;

void imprimirMatrizp(const std::vector<std::vector<std::pair<int, int>>>& matriz) {
    int maxDigits = 0;
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            std::string elementoStr = "(" + std::to_string(elemento.first) + "," + std::to_string(elemento.second) + ")";
            int digits = elementoStr.size();
            if (digits > maxDigits) {
                maxDigits = digits;
            }
        }
    }

    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            std::string elementoStr = "(" + std::to_string(elemento.first) + "," + std::to_string(elemento.second) + ")";
            std::cout << std::setw(maxDigits + 2) << elementoStr;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void imprimirMatriz(const std::vector<std::vector<int>>& matriz) {

  int maxDigits = 0;
  for (const auto& fila : matriz) {
      for (int elemento : fila) {
          int digits = std::to_string(elemento).size();
          if (digits > maxDigits) {
              maxDigits = digits;
          }
      }
  }

  for (const auto& fila : matriz) {
      for (int elemento : fila) {
          std::cout << std::setw(maxDigits + 2) << elemento;  
      }
      std::cout << std::endl; 
  }
  cout<<endl;

}



int Ef1 (string a){
    int result =0;
    if(a =="AU" || a == "UA") result=-1;
    if(a =="CG" || a == "GC") result=-1;
    return result;
    
}

int Ef2(string a){
    int result =0;
    if(a =="AU" || a == "UA") result=-4;
    if(a =="CG" || a == "GC") result=-5;
    if(a =="GU" || a == "UG") result=-1;
    return result;
}

void calcular_eficiencia(vector<vector<int>>& matrix,string f,string seq,int i,int j,vvp& c){
    int energy=0;
    vector<int> valores;
    if (f =="f1") energy = Ef1(string(1, seq[i]) + string(1, seq[j]));
    else if (f =="f2") energy = Ef2(string(1, seq[i]) + string(1, seq[j]));

    
    valores.push_back(matrix[i][j-1]);
    valores.push_back(matrix[i+1][j]);
    valores.push_back(matrix[i+1][j-1]+energy);
    
    vector<int> ak;
    vector<pair<int,int>> paak;
    for (int k =i;k<j;k++) {
        ak.push_back(matrix[i][k]+matrix[k+1][j]);
        paak.push_back(make_pair(k+1,j));
    }
        
    pair<int,int> pairk;
    if(ak.size()){
        int mimk=ak[0];
        pairk=paak[0];
        for(int in=1;in<ak.size();in++){
            if(ak[in]<mimk) {
                mimk=ak[in];
                pairk=paak[in];
            };
        }
        valores.push_back(mimk);
    }

    
    int minimo = valores[0];
    int pairindex =0;
    
    for(int in = 1; in < valores.size(); in++) {
        if(valores[in] < minimo ) {
            minimo = valores[in];
            pairindex = in;
        }
    }
    
    matrix[i][j]=minimo;
    minimo = valores[0];
    pairindex =0;
    for(int in = 1; in < valores.size(); in++) {
        if(valores[in] > minimo && in==2) {
            minimo = valores[in];
            pairindex = in;
        }
    }
    if(pairindex==0) c[i][j]=make_pair(i,j-1);
    else if(pairindex==1) c[i][j]=make_pair(i+1,j);
    else if(pairindex==2) c[i][j]=make_pair(i+1,j-1);
    else c[i][j]=pairk;
    
    
    
}

void ARN(string seq,string function){
  int lenseq = seq.length();
  vector<vector<int>> matrix(lenseq,vector<int>(lenseq,0));

  vvp camino(lenseq,vector<pair<int,int>>(lenseq,make_pair(0,0)));
  for (int i=0;i<lenseq;i++){
    matrix[i][i]=0;
    if(i+1<lenseq) matrix[i+1][i]=0;
  }
  for (int i =1;i<lenseq;i++){
    int temp=i;
    for (int j =0;j<lenseq;j++){
        if(temp == lenseq) break;
        calcular_eficiencia(matrix,function,seq,j,temp,camino);
        temp++;
    }
    
  }
  //imprimirMatrizp(camino);
  imprimirMatriz(matrix);
  int x=0;
  int y=lenseq-1;

    
  for(int i=0;i<int(lenseq/2);i++){
    
    cout<<seq[i]<< "-"<<seq[y]<<endl;
    if(i+1==int(lenseq/2)){
        cout<<"|_|"<<endl;break;
    }
    cout<<"| |"<<endl;  
    pair<int,int> pos = camino[x][y];
    x=pos.first;
    y=pos.second;
    
  }
  cout<<endl;
}
int main() {
    ARN("GGAAAUCC","f1");
    ARN("GGAAAUCC","f2");
    
    ARN("ACUCGAUUCCGAG","f1");
    ARN("ACUCGAUUCCGAG","f2");
    
}