#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H
#include "simulation.h"


class boundaryConditions
{
    public:
        boundaryConditions(simulation&);
        virtual ~boundaryConditions();

        void outFlow();
        void inlet();
        void bounceBackObstacle();
        void bottomWall();
        void topWall();

    protected:

    private:
        simulation simRes;

};

#endif // BOUNDARYCONDITIONS_H
