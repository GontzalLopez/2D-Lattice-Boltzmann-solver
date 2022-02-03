#include "postprocessing.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

postProcessing::postProcessing(simulation& s_):simRes(s_)
{
    //ctor
}


void postProcessing::saveToCSV(int itNumber, int var)
{
    FILE *fdata;
    double res;
    char mag[50];
    if(var==0){strcpy(mag,"./Results/Ux/Uxmag_");}
    else if(var==1){strcpy(mag,"./Results/Uy/Uymag_");}
    else if(var==2){strcpy(mag,"./Results/density/density_");}

    char num[8+sizeof(char)];
    sprintf(num, "%d", itNumber);
    strcat (mag,num);
    strcat (mag,".dat");

    fdata = fopen(mag,"w+t");

    if ( fdata == NULL )
    {
        printf("\nERROR when opening file\n");
        fclose( fdata );
    }
    else
    {
        printf("\nSaving to file...\n");

        for (int j = 0;j<((simRes.Ny));j++)
        {
            for (int i = 0;i<(simRes.Nx);i++)
            {
                if(simRes.Domain.ObstacleNodes[i][j]==1)
                {
                    simRes.u[i][j][0]=0.0;
                    simRes.u[i][j][1]=0.0;
                }
                if(var==0){res=simRes.u[i][j][0];}             //x velocity
                else if(var==1){res=simRes.u[i][j][1];}        //y velocity
                else if(var==2){res=simRes.rho[i][j];}   //density

                fprintf( fdata, "%5.8lf\t",res);
                fprintf( fdata, "\t");
//              fprintf( fdata, "%d\t",simRes.Domain.ObstacleNodes[i][j]);
//              fprintf( fdata, "%lf\t",simRes.Fin[i][j][0]);
            }
            fprintf( fdata, "\n");
        }
    }

    fclose(fdata);
}

postProcessing::~postProcessing()
{
}
