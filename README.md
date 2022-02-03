# 2D-Lattice-Boltzmann-solver

A Simple 2D Implementation of Lattice Boltzmann Method in Python. Allows the user to simulate the flow over a cylinder, array of squares or a rectangular obstacle. 
Top and bottom boundaries can be modelled as walls or periodic. The code was written for educational purposes as a basic introduction to the LBM models. The next step would be to write the code in order to parallelise the calculation and include turbulent LES models.

References: 
	A. A. Mohamad, Lattice Boltzmann Method - Fundamentals and Engineering Applications with Computer Codes (2019)

Build project:
```
chmod u+x Make.sh
./Make.sh
```
Run:
```
./LBMsolver
```
Post-processing:
```
cd Results
python2 postScript.py
```

![](2D_LatticeBoltzmann/Results/Results_20000.png| width=100)
