#!/bin/bash
# Uso: ./run_tests.sh   (compila cada src/NN_*.cpp y compara con tests/NN.in / NN.out)
mkdir -p bin
for f in src/*.cpp; do
  id=$(basename $f | cut -c1-2)
  g++ -O2 -std=c++17 -o bin/$id $f || { echo "$id: ERROR DE COMPILACION"; continue; }
  if [ -f tests/$id.in ]; then
    if diff -wB <(./bin/$id < tests/$id.in) tests/$id.out > /dev/null; then echo "$id: OK"; else echo "$id: FALLA"; fi
  else echo "$id: compilado (sin test)"; fi
done
