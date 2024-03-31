#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <unistd.h> 
using namespace std;

typedef vector<vector<vector<pair<int,int>>>> vvvp;

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
}

void maxi(vector<vector<int>> m, int i, int j,vvvp &a, int n){
  pair<int,pair<int,int>> pos1=make_pair(m[i-1][j-1]+n,make_pair(i-1,j-1));
  pair<int,pair<int,int>> pos2=make_pair(m[i-1][j]-2,make_pair(i-1,j));
  pair<int,pair<int,int>> pos3=make_pair(m[i][j-1]-2,make_pair(i,j-1));
  vector<pair<int,pair<int,int>>> tempv={pos1,pos2,pos3};
  
  
  auto comparador = [](const std::pair<int, std::pair<int, int>>& a, const std::pair<int, std::pair<int, int>>& b) {
      return a.first > b.first;
  };
  sort(tempv.begin(), tempv.end(), comparador);  
  int maximo= tempv[0].first;
  a[i][j].push_back(tempv[0].second);
  for(int r=1;r<3;r++) {
    if(tempv[r].first==maximo)
      a[i][j].push_back(tempv[r].second);
    else break;
  }
  
  
}

void calC(vector<pair<int,int>> &com,vvvp dir ,int c1,int c2){
  pair<int,int> c=make_pair(c1-1,c2-1);
  com.push_back(c);
  std::random_device rd;
  std::mt19937 gen(rd());

  while(c.first!=0 || c.second!=0){
    int v=dir[c.first][c.second].size();
    std::uniform_int_distribution<> distrib(0, v-1);
    int rn = distrib(gen);
    pair<int,int> af=dir[c.first][c.second][rn];
    com.push_back(af);
    c=af;
  }
}

string camino(vector<pair<int,int>> com,string c2){
  string h="";
  
  for (int i=0;i<com.size();i++){
    if(com[i].second != com[i+1].second){
      h=c2[com[i].second]+h; 
    }else{
      h="-"+h;
    }
  }
  h.erase(0, 1);
  return h;
}
void matriX(vector<vector<int>> &m,string c1,string c2,vvvp &dir){
  for(int i=1;i<m.size();i++){
    for(int j=1;j<m[0].size();j++){
      m[0][j]=m[0][j-1]-2;
      if(dir[0][j].size()==1) continue;
      dir[0][j].push_back(make_pair(0, j-1));
    }
    m[i][0]=m[i-1][0]-2;
    dir[i][0].push_back(make_pair(i-1,0));
  }
  for (int i=1;i<c1.size();i++){
    for (int j=1;j<c2.size();j++){
      if(c1[i] == c2[j]) {
        m[i][j]= max({m[i-1][j-1]+1,m[i-1][j]-2,m[i][j-1]-2 });
        maxi(m,i,j,dir,+1);
      }
      else {
        m[i][j]= max({m[i-1][j-1]-1,m[i-1][j]-2,m[i][j-1]-2 });
        maxi(m,i,j,dir,-1);
      } 
    }
  }

}

int score(string c1,string c2){
  int sco=0;
  for(int i=0;i<c1.size();i++){
    if(c1[i]==c2[i]) sco++;
    else if(c2[i] =='-') sco-=2;
    else sco--;
  }
  cout<<"score: "<<sco<<endl;
  return sco;
}
void globalAlineament(string c1,string c2,int iter) {
  string gap= "-";
  string cad1 = gap+c1;
  string cad2 = gap+c2;
  int n = cad1.size();
  int m = cad2.size();
  vector<vector<int>> matrix(n, vector<int>(m, 0));
  vvvp dir(cad1.size(),vector<vector<pair<int, int>>>(cad2.size()));
  
  matriX(matrix,cad1,cad2,dir);

  string cadF="";
  vector<pair<int,int>> com;
  
  vector<pair<int,int>> best;
  int bestscore;
  string cadbest="";

  for (int i=0;i<iter;i++){
    calC(com, dir,cad1.size(),cad2.size());
    cadF=camino(com,cad2);
    cout<<cad1.substr(1)<<endl;
    cout<<cadF<<endl;
    int  s=score(cad1.substr(1),cadF);
    if(i==0){
      bestscore=s;
      cadbest=cadF;
      best=com;
    }else if(bestscore>s){
      bestscore=s;
      best=com;
      cadbest=cadF;
    }
    cout<<"-----FIN-----"<<endl;
    com.clear();
  }
  
  ofstream archivo("pares.txt");
  if (archivo.is_open()) {
    for (const auto& par : best) 
      archivo << par.first << "," << par.second <<endl;
    
  }
  archivo.close();
  ofstream archivo2("cadenas.txt");
  if (archivo2.is_open()) {
    archivo2 << cad1.substr(1) <<endl;
    archivo2 << cadbest <<endl;
  }
    
  archivo2.close();
  
  
  //imprimirMatriz(matrix);
}

int main() {
  int valor;
  cout<<"\n 1: txt \n 2: agregarCadenas \n 3: CadenasPredefinidas: ";
  cin>>valor;
  cin.ignore();
  string c1,c2;
  
  
  if(valor == 1){
    cout<<"c1: ";cin>>c1;
    cin.ignore();
    cout<<"c2: ";cin>>c2;
    cin.ignore();
    ifstream a1(c1+".txt");
    if (a1.is_open()) { getline(a1, c1); a1.close();} 
    ifstream a2(c2+".txt");
    if (a2.is_open()) { getline(a2, c2); a2.close();} 
  }else if(valor ==2){
    cout<<"c1: ";cin>>c1;
    cin.ignore();
    cout<<"c2: ";cin>>c2;
    cin.ignore();
  }else if (valor ==3){
    c1="AAAC";
    c2="AGC";
  }else{
    return 0;
  }
  if(c1.size()<c2.size()){
    string temp=c1;
    c1=c2;
    c2=temp;
  }
  int n ; cout<<"Iter: ";cin>>n;
  c1.resize(c1.size() / 4);
  c2.resize(c2.size() / 4);
  globalAlineament(c1,c2,n);  
  
}