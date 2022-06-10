#!/bin/bash
for i in {1..10}
do
  ./bin/main > ./resultados/resultado_${i}
  echo "resultado ${i} completado" 
done