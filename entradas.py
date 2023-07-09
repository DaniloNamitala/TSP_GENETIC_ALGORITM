from random import randint as rand
import sys

n = int(sys.argv[1])
entradas = {}
print(n)
for i in range(n):
  e = (rand(0, 50), rand(0, 50))
  while e in entradas:
    e = (rand(0, 50), rand(0, 50))
  entradas[i] = e
  print(f"{e[0]} {e[1]}")