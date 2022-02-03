#include "boundaryconditions.h"
#include <iostream>
using namespace std;


boundaryConditions::boundaryConditions(simulation& s_):simRes(s_)
{
    //ctor
}

void boundaryConditions::outFlow()
{

    int Prev=(simRes.Nx)-2;
    int Last=(simRes.Nx)-1;

    for(int i=0;i<simRes.Ny;i++)
    {
        for(int j=6;j<9;j++)
        {
            simRes.Fin[Last][i][j]=simRes.Fin[Prev][i][j];

        }
    }
//        cout<<"Outflow BC.....done"<<endl;
}

void boundaryConditions::inlet()
{
    double A,B;

    for(int j=0;j<simRes.Ny;j++)
    {

        simRes.u[0][j][0]=simRes.uLB;
        simRes.u[0][j][1]=0.0;

        A=simRes.Fin[0][j][5]+simRes.Fin[0][j][0]+simRes.Fin[0][j][1]; //rho2
        B=simRes.Fin[0][j][6]+simRes.Fin[0][j][7]+simRes.Fin[0][j][8]; //rho3
        simRes.rho[0][j]=1/(1-simRes.u[0][j][0])*(A+2*B);

        simRes.Fin[0][j][2]=simRes.Feq[0][j][2]+simRes.Fin[0][j][6]-simRes.Feq[0][j][6];
        simRes.Fin[0][j][3]=simRes.Feq[0][j][3]+simRes.Fin[0][j][7]-simRes.Feq[0][j][7];
        simRes.Fin[0][j][4]=simRes.Feq[0][j][4]+simRes.Fin[0][j][8]-simRes.Feq[0][j][8];
    }

//    cout<<"Inlet BC.....done"<<endl;
}

void boundaryConditions::bounceBackObstacle()
{
    for(int i=0;i<simRes.Nx;i++)
    {
    for(int j=0;j<simRes.Ny;j++)
        {
            if(simRes.Domain.ObstacleNodes[i][j]==1)
                {
                    for(int k=0;k<9;k++)
                    {
                        if(k==0)
                        {
                            simRes.Fout[i][j][k]=simRes.Fin[i][j][k];
                        }else if((k>0)&&(k<5))
                        {
                            simRes.Fout[i][j][k]=simRes.Fin[i][j][k+4];
                        }else
                        {
                            simRes.Fout[i][j][k]=simRes.Fin[i][j][k-4];
                        }
                    }
                }
        }
    }
//    cout<<"Obstacle BC.....done"<<endl;
}


void boundaryConditions::bottomWall()
{
        for(int i=0;i<simRes.Nx;i++)
        {
            if(simRes.Domain.ObstacleNodes[i][simRes.Ny-1]==0)
            {

                simRes.Fout[i][simRes.Ny-1][8]=simRes.Fin[i][simRes.Ny-1][4];
                simRes.Fout[i][simRes.Ny-1][1]=simRes.Fin[i][simRes.Ny-1][5];
                simRes.Fout[i][simRes.Ny-1][2]=simRes.Fin[i][simRes.Ny-1][6];
                //simRes.u[i][simRes.Ny-1][0]=0.0;
                //simRes.u[i][simRes.Ny-1][1]=0.0;
            }
        }
}

void boundaryConditions::topWall()
{
        for(int i=0;i<simRes.Nx;i++)
        {
     //   for(int j=0;j<simRes.Ny;j++)
      //      {
            if(simRes.Domain.ObstacleNodes[i][0]==0)
            {

                simRes.Fout[i][0][4]=simRes.Fin[i][0][8];
                simRes.Fout[i][0][5]=simRes.Fin[i][0][1];
                simRes.Fout[i][0][6]=simRes.Fin[i][0][2];
                //simRes.u[i][0][0]=0.0;
                //simRes.u[i][0][1]=0.0;
            }
         //   }
        }
}


boundaryConditions::~boundaryConditions()
{}
