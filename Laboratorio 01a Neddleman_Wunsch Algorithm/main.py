import matplotlib.pyplot as plt
import numpy as np

def diagonal():
  coordenadas = np.loadtxt("pares.txt", delimiter=",")
  
  x = [coord[1] for coord in coordenadas]
  y = [coord[0] for coord in coordenadas]
  
  sq="influenza"
  sq2="Sarc_cov"
  plt.plot(x, y, 'bo', markersize=1,linewidth=1, markerfacecolor='b')  
  plt.title('Dot Matrix')
  plt.xlabel(sq)
  plt.ylabel(sq2)
  plt.gca().invert_yaxis()
  for i in range(len(x)-1):
    dx = x[i+1] - x[i]
    dy = y[i+1] - y[i]
    plt.arrow(x[i], y[i], dx, dy, head_width=0.2, head_length=0.2, fc='r', ec='r')
  plt.grid(True)
  plt.xticks([])
  plt.yticks([])
  #plt.show()

def complete_sequence(seq, length):
  if len(seq) < length:
      seq += '#' * (length - len(seq))
  return seq


def dotMatrix():
  with open('cadenas.txt', 'r') as archivo:
    seq1=archivo.readline()
    seq2=archivo.readline()
  max_length = max(len(seq1), len(seq2))
  seq1 = complete_sequence(seq1, max_length)
  seq2 = complete_sequence(seq2, max_length)
 
  matrix = [[1 if seq1[i] == seq2[j] else 0 for j in range(len(seq2))] for i in range(len(seq1))]
  
  # Trazar el dot matrix con puntos
  plt.imshow(matrix, cmap='gray', aspect='auto', interpolation='none')
  plt.title('Dot Matrix Sarc_Cov y Influenza')
  plt.xlabel('Influenza')
  plt.ylabel('Sarc_cov')
  plt.gca().invert_yaxis()  # Invertir el eje y para que coincida con la orientación de la 
  plt.xticks([])
  plt.yticks([])
  #plt.show()


dotMatrix()
diagonal()
plt.tight_layout()
plt.savefig('grafico.png')
plt.show()



