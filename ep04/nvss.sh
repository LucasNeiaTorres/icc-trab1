#!/bin/bash

# Defina o vetor ARRAY
ARRAY=(64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000)

# Itere sobre os valores no vetor
for valor in "${ARRAY[@]}"; do
    echo "Valor: $valor"
done