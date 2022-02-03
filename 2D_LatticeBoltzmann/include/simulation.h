#ifndef SIMULATION_H
#define SIMULATION_H
#include "lbm.h"
#include "domain.h"


class simulation: public LBM
{
    public:

        domain Domain;
        int Nx;
        int Ny;
        double **rho;           //Density
        double ***Fin;          //Distribution function (in)
        double ***Fout;         //Distribution function (out)
        double ***Feq;          //Equilibrium distribution function
        double ***u;            //Macroscopic Velocity

        void printField();
        void calcFeq();
        void collision();
        void allocateMem();
        void initialization();
        void streaming();
        void calcMacroscopic();
        void deleteMem();

        simulation();
        virtual ~simulation();


    private:

        void calculateNxNy();
};

#endif // SIMULATION_H
