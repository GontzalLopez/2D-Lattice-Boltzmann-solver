//Author: 	Gontzal López Ruiz 
//Date: 	01/2022

#include <iostream>
#include "simulation.h"
#include "boundaryconditions.h"
#include "postprocessing.h"

using namespace std;

int main()
{

//    int saveInterval=S.saveInterval;
//    int lim=S.firstSaved;

    simulation S;  //simulation S(domain)
    boundaryConditions BC(S);
    postProcessing Post(S);
    S.initialization();

    for(int i=1;i<=S.iterNum;i++) 
    {
        if(i%100==0)
        {
            cout<<"Solving LBM -- Iteration "<<i<<endl;
            cout<<"..."<<endl;
        }

        S.collision();
        BC.bounceBackObstacle();
        if(S.walls)
        {
            BC.bottomWall();
            BC.topWall();
        }
        S.streaming();
        BC.outFlow();
        BC.inlet();
        S.calcMacroscopic();
        S.calcFeq();

        if(i==S.firstSaved)
        {
            Post.saveToCSV(i,0); //0: x velocity, 1: y velocity, 2: density
            Post.saveToCSV(i,1);
            S.firstSaved=S.saveInterval+i;
        }
    }

    cout<<""<<endl;
    cout<<"End of calculation"<<endl;

    S.deleteMem();

    return 0;
}
