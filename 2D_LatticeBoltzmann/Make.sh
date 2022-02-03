#!/bin/bash

#--------------
echo "Compiling..."
g++ -Wall -fexceptions -g -Iinclude -c main.cpp -o obj/main.o
g++ -Wall -fexceptions -g -Iinclude -c src/boundaryconditions.cpp -o obj/boundaryconditions.o
g++ -Wall -fexceptions -g -Iinclude -c src/domain.cpp -o obj/domain.o
g++ -Wall -fexceptions -g -Iinclude -c src/lbm.cpp -o obj/lbm.o
g++ -Wall -fexceptions -g -Iinclude -c src/postprocessing.cpp -o obj/postprocessing.o
g++ -Wall -fexceptions -g -Iinclude -c src/simulation.cpp -o obj/simulation.o
g++  -o LBMsolver obj/main.o obj/boundaryconditions.o obj/domain.o obj/lbm.o obj/postprocessing.o obj/simulation.o   
echo "Done"
exit 0