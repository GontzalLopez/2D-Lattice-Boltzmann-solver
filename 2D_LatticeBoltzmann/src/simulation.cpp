#include "simulation.h"
#include "d2q9.h"
#include <iostream>

using namespace std;



simulation::simulation():LBM()
{
    simulation::calculateNxNy();
    simulation::allocateMem();
    Domain.createObstacle(Nx, Ny, obstacleType);
}

void simulation::calculateNxNy()
{
    Ny=4*(Re*nuLB)/uLB;     //two cylinder distance each side
    Nx=Ny*aspectRatio;
    cout<<"..."<<endl;
    cout<<"Nx="<<Nx<<endl;
    cout<<"Ny="<<Ny<<endl;
    cout<<"..."<<endl;
}

void simulation::allocateMem()
{
    Fin = new double**[Nx]; Fout = new double**[Nx]; Feq = new double**[Nx];
    for (int i=0;i<Nx;i++)
    {
      Fin[i] = new double*[Ny];
      Fout[i] = new double*[Ny];
      Feq[i] = new double*[Ny];
        for(int j=0;j<Ny;j++)
        {
          Fout[i][j] = new double[9];
          Fin[i][j] = new double[9];
          Feq[i][j] = new double[9];
        }
    }

    rho = new double*[Nx]; u = new double**[Nx];
    for(int i=0;i<Nx;i++)
    {
        rho[i] = new double[Ny];
        u[i] = new double*[Ny];
        for (int j=0;j<Ny;j++)
        {
          u[i][j] = new double[2];
        }
    }
    cout<<"Creating variables.....done"<<endl;
}


void simulation::initialization()
{
    double rho0 = 1.0;

    for(int i = 0; i < Nx; i++)
    {
        for(int j = 0; j < Ny; j++)
        {
            for(int k = 0; k < 9; k++)
            {
                rho[i][j] = rho0;
                u[i][j][0] = uLB;
                u[i][j][1] = 0.0;
            }
        }
    }

   simulation::calcFeq();
   for(int i = 0; i < Nx; i++)
    {
        for(int j = 0; j < Ny; j++)
        {
            for(int k = 0; k < 9; k++)
            {
                Fin[i][j][k]=Feq[i][j][k];
            }
        }
    }
    cout<<"Initialization done."<<endl;
    cout<<"..."<<endl;
    cout<<"..."<<endl;
    cout<<"..."<<endl;
    cout<<"..."<<endl;
}

void simulation::calcMacroscopic()
{
    for(int i=0; i<Nx;i++)
    {
        for(int j=0;j<Ny;j++)
        {
            u[i][j][0]=0.0;
            u[i][j][1]=0.0;
            rho[i][j]=0.0;

            for(int k=0;k<9;k++)
            {
                rho[i][j]+=Fin[i][j][k]; //macroscopic density
                u[i][j][0]+=c[k][0]*Fin[i][j][k];
                u[i][j][1]+=c[k][1]*Fin[i][j][k];
            }
            u[i][j][0]/=rho[i][j];
            u[i][j][1]/=rho[i][j];
        }
    }
//    cout<<"Macroscopic calculation.....done"<<endl;
}

void simulation::calcFeq()
{
    for(int i = 0; i < Nx; i++)
    {
        for(int j = 0; j < Ny; j++)
        {
            for(int k = 0; k < 9; k++)
            {
                double uci = c[k][0]*u[i][j][0] + c[k][1]*u[i][j][1];
                double uu = u[i][j][0]*u[i][j][0] + u[i][j][1]*u[i][j][1];
                Feq[i][j][k] = w[k]*rho[i][j]*(1.0 + 3.0*uci + 4.5*uci*uci - 1.5*uu);
            }
        }
    }
//    cout<<"Calculating Feq.....done"<<endl;
}

void simulation::collision()
{
    for(int i = 0; i < Nx; i++)
    {
        for(int j = 0; j < Ny; j++)
        {
            for(int k = 0; k < 9; k++)
            {
                Fout[i][j][k]=Fin[i][j][k]-Omega*(Fin[i][j][k]-Feq[i][j][k]);
            }
        }
    }
//    cout<<"Collision step.....done"<<endl;
}

void simulation::streaming()
{
    int next_x;
    int next_y;

    for(int i = 0; i < Nx; i++)
    {
        for(int j = 0; j < Ny; j++)
        {
            for(int k = 0; k < 9; k++)
            {
                next_x=i+c[k][0];
                if(next_x<0){next_x=Nx-1;};
                if(next_x>=Nx){next_x=0;};

                next_y=j+c[k][1];
                if(next_y<0){next_y=Ny-1;};
                if(next_y>=Ny){next_y=0;};

                Fin[next_x][next_y][k]=Fout[i][j][k];
            }
        }
    }
//    cout<<"Streaming step.....done"<<endl;
}



void simulation::printField()
{
        for(int i = 0; i < Nx; i++)
        {
            for(int j = 0; j < Ny; j++)
            {
                cout<<u[i][j][0];
                cout<<" ";
            }
            cout<<endl;
        }
}

void simulation::deleteMem()
{
    for(int i = 0; i < Nx; ++i)
    {
        for(int j=0;j<Ny;j++)
        {
            delete[] Fin[i][j];
            delete[] Fout[i][j];
            delete[] Feq[i][j];
            delete [] u[i][j];
        }
        delete[] rho[i];
        delete[] Fin[i];
        delete[] Fout[i];
        delete[] Feq[i];
        delete[] u[i];
    }

    delete[] rho;
    delete[] Fin;
    delete[] Fout;
    delete[] Feq;
    delete[] u;
}

simulation::~simulation()
{
}
