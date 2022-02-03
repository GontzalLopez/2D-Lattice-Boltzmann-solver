#include <iostream>
#include "domain.h"
#include <cstring>
#include <cmath>
#include <cstdlib>



using namespace std;

domain::domain(){}

void domain::createObstacle(int Nx, int Ny, char *obstacleType)
{

    double r=Ny/8; //  Ny/3/2

    ObstacleNodes = new int*[Nx];
    for (int i=0;i<Nx;i++)
    {
      ObstacleNodes[i] = new int[Ny];
    }

    if(strcmp("cylinder",obstacleType)==0)
    {
        for (int i=0;i<Nx;i++)
        {
            for(int j=0;j<Ny;j++)
            {
              if(((i-(Nx/4))*(i-(Nx/4))+(j-(Ny/2))*(j-(Ny/2)))<(r*r))
              {
                ObstacleNodes[i][j]=1;
              }else
              {
                ObstacleNodes[i][j]=0;
              }
            }
        }
        cout<<"Obstacle created"<<endl;
    }
    else if(strcmp("squares",obstacleType)==0)
    {

        bool a;
        bool b;
        bool c;
        bool d;
        bool e;
            for (int i=0;i<Nx;i++)
            {
                    for(int j=0;j<Ny;j++)
                    {
                        //position of each square can be modified (Nx/x Ny/y)
                            a=(abs(i-(Nx/6)+j-(Ny/2))+abs(i-(Nx/6)-j+(Ny/2)))<r;
                            b=(abs(i-(Nx/2.5)+j-(Ny/2))+abs(i-(Nx/2.5)-j+(Ny/2)))<r;
                            c=(abs(i-(Nx/1.5)+j-(Ny/2))+abs(i-(Nx/1.5)-j+(Ny/2)))<r;
                            d=(abs(i-(Nx/1.5)+j-(Ny/4))+abs(i-(Nx/1.5)-j+(Ny/4)))<r;
                            e=(abs(i-(Nx/1.5)+j-(Ny*0.75))+abs(i-(Nx/1.5)-j+(Ny*0.75)))<r;
                            if(a||b||c||d||e)
                        {
                            ObstacleNodes[i][j]=1;
                        }
                        else
                        {
                            ObstacleNodes[i][j]=0;
                        }
                    }
            }
        cout<<"Obstacle created"<<endl;
    }
    else if(strcmp("rectangle",obstacleType)==0)
    {
        for (int i=(Nx/4);i<(Nx/2);i++)     //Modify the limits of i and j to change the shape of the floor rectangle
        {
            for(int j=(Ny*0.75);j<Ny;j++)
            {
                ObstacleNodes[i][j]=1;
            }
        }
        cout<<"Obstacle created"<<endl;
    }
    else
    {
    cout<<"Error creating obstalce object"<<endl;
    }
}



domain::~domain()
{
    //dtor
}
