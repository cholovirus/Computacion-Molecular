import random
import networkx as nx
import plotly.graph_objects as go
import matplotlib.pyplot as plt
def complementoReverso(seq):
  complemento = {'A': 'T', 'T': 'A', 'C': 'G', 'G': 'C'}
  return ''.join(complemento.get(base, base) for base in reversed(seq))

def allSeqR(seqs):
  for i in range(len(seqs)):
    seqs[i]= complementoReverso(seqs[i])
  return seqs
    
def openFile(map,arr,txt):
  with open(txt+'.txt', 'r') as archivo:
    for linea in archivo:
      linea =linea.split()
      map[linea[0]] = linea[1]
      arr.append(linea[1])

def ensamblar(seq1,seq2):
  tam = 0
  s1 = seq1
  s2 = seq2
  solapamiento_maximo = len(s1) - 1
  for i in range(solapamiento_maximo, 0, -1):
    if s1.endswith(s2[:i]):
      s1 += s2[i:]
      tam=i
      break
  return tam,s1
  
def sortE(ar):
  matrix = []
  for i in ar:
    temp=[]
    for j in ar:
      tam,s1 = ensamblar(i,j)
      temp.append(tam)
    matrix.append(temp)

  sumar = []
  for i in matrix:
    tsum = sum(i)
    sumar.append(tsum)

  pares = zip(sumar, matrix)
  pares2 = zip(sumar,ar)
  pares_ordenados = sorted(pares, key=lambda x: x[0], reverse=True)
  pares_ordenados2 = sorted(pares2, key=lambda x: x[0], reverse=True)
  sumar = [par[0] for par in pares_ordenados]
  matrix = [par[1] for par in pares_ordenados]
  ar = [par[1] for par in pares_ordenados2]
  return ar

def PS(seq1,seq2):
  tam1,s1 =ensamblar(seq1,seq2)
  tam2,s2 =ensamblar(seq2,seq1)

  if( tam1 ==0 and tam2==0):
    return tam1,seq1 + seq2
  elif  tam1 >tam2:
    return tam1,s1
  else:
    return tam2,s2

def consenso(fragmentos):
  arr = fragmentos.copy()
  temp = fragmentos.copy()
  ensa = ""
  subcadenas = []
  for i in arr:
    max = 0
    s1 = ""
    #print("--")
    for j in arr:
      if i == j :

        continue
      if j not in temp:
        
        continue
      #print(i,j)
      tmplen,ts = PS(i,j)
      if max< tmplen:
        max = tmplen
        s1 = ts
        sub = [i,j,tmplen]
        subcadenas.append(sub)
    
    if i in temp:
      indice = temp.index(i)
      del temp[indice]
    #print(temp)
    r, ensa = PS(ensa,s1)
    #print(ensa,len(ensa))
  
  return ensa, subcadenas

def Anwser(arr):
  tam =-1
  son = ""
  subcad=[]
  for i in range(100):
    random.shuffle(arr)
    con, sub =consenso(arr)
    if tam == -1 or tam > len(con):
      tam = len(con)
      son = con
      subcad = sub

  print("Secuencia de Consenso: \n",son," Size Seq: ",tam)
  print("---------------------\n")
  print("Cadenas Overlap")
  return subcad

def nodos(datos):
  matriz = {}
  for conexion in datos:
    nodo_padre = conexion[0]
    nodo_hijo = conexion[1]
    peso = conexion[2]
    if nodo_padre not in matriz:
        matriz[nodo_padre] = {}
    matriz[nodo_padre][nodo_hijo] = peso
  
  # Imprimir la matriz
  for nodo_padre, conexiones in matriz.items():
    for nodo_hijo, peso in conexiones.items():
        print(f"{nodo_padre} -> {nodo_hijo}: {peso}")
  return matriz

def GraficarGrafo(matriz):
  grafo = nx.DiGraph()
  for nodo_padre, conexiones in matriz.items():
      for nodo_hijo, peso in conexiones.items():
          grafo.add_edge(nodo_padre, nodo_hijo, weight=peso)

  # Dibujar el grafo
  pos = nx.spring_layout(grafo)  # Posicionamiento de los nodos
  nx.draw_networkx_nodes(grafo, pos, node_size=700)  # Dibujar nodos
  nx.draw_networkx_edges(grafo, pos, width=1.0, alpha=0.5)  # Dibujar aristas
  nx.draw_networkx_labels(grafo, pos, font_size=12, font_family='sans-serif')  # Etiquetas de los nodos

  # Agregar etiquetas a las aristas (pesos)
  labels = nx.get_edge_attributes(grafo, 'weight')
  nx.draw_networkx_edge_labels(grafo, pos, edge_labels=labels)

  # Guardar el grafo como una imagen
  plt.title("Grafo desde matriz de adyacencia")
  plt.axis('off')  # Desactivar los ejes
  plt.savefig("grafo.png")  # Guardar como imagen


map = {}
arr =[]
openFile(map,arr,'seq')

arrC= allSeqR(arr.copy())

arr =sortE(arr)
datos =Anwser(arr)
matriz = nodos(datos)
GraficarGrafo(matriz)

'''arr =sortE(arrC)
datos =Anwser(arr)
matriz = nodos(datos)
GraficarGrafo(matriz)
'''
