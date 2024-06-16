import numpy as np
from Bio import AlignIO

def build_profile(sequences):
  num_sequences = len(sequences)
  seq_len = len(sequences[0])
  match_states = []
  for i in range(seq_len):
      column = [seq[i] for seq in sequences]
      if column.count('-') / num_sequences < 0.5:
          match_states.append(column)
  return match_states

def calculate_probabilities(profile):
  num_states = len(profile)
  symbol_counts = {}
  transition_counts = {'match': {'match': 0, 'insert': 0, 'delete': 0},
                       'insert': {'match': 0, 'insert': 0, 'delete': 0},
                       'delete': {'match': 0, 'insert': 0, 'delete': 0}}

  for state in profile:
      for symbol in state:
          if symbol not in symbol_counts:
              symbol_counts[symbol] = 0
          symbol_counts[symbol] += 1

  total_symbols = sum(symbol_counts.values())
  emission_probs = {symbol: count / total_symbols for symbol, count in symbol_counts.items()}

  return emission_probs, transition_counts

def build_hmm(sequences):
  profile = build_profile(sequences)
  emission_probs, transition_probs = calculate_probabilities(profile)
  return profile, emission_probs, transition_probs

sequences = [
  "VGA--HAGEY",
  "V----NVDEV",
  "VEA--DVAGH",
  "VKG------D",
  "VYS--TYETS",
  "FNA--NIPKH",
  "IAGADNGAGY"
]

profile, emission_probs, transition_probs = build_hmm(sequences)

print(" HMM:")
for state in profile:
  print(state)

print("\nProbabilidades:")
for symbol, prob in emission_probs.items():
  print(f"{symbol}: {prob:.2f}")

print("\n Probabilidades de Transicion:")
for from_state, to_states in transition_probs.items():
  for to_state, count in to_states.items():
      print(f"{from_state} -> {to_state}: {count}")

def calculate_transition_probabilities(profile, sequences):
  transition_counts = {'match': {'match': 0, 'insert': 0, 'delete': 0},
                       'insert': {'match': 0, 'insert': 0, 'delete': 0},
                       'delete': {'match': 0, 'insert': 0, 'delete': 0}}

  for seq in sequences:
    for i in range(len(seq)):
      if seq[i] != '-':
          if i == 0 or seq[i-1] == '-':
              transition_counts['match']['insert'] += 1
          elif seq[i-1] != '-':
              transition_counts['match']['match'] += 1
      else:
          if i == 0 or seq[i-1] == '-':
              transition_counts['insert']['delete'] += 1
          elif seq[i-1] != '-':
              transition_counts['insert']['insert'] += 1

  total_transitions = sum(sum(counts.values()) for counts in transition_counts.values())
  for from_state in transition_counts:
    for to_state in transition_counts[from_state]:
      transition_counts[from_state][to_state] = transition_counts[from_state][to_state] / total_transitions

  return transition_counts


transition_probs = calculate_transition_probabilities(profile, sequences)

print("\nProbabilidades ajustadas:")
for from_state, to_states in transition_probs.items():
  for to_state, prob in to_states.items():
      print(f"{from_state} -> {to_state}: {prob:.2f}")
