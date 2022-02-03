#include "lbm.h"
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

LBM::LBM()
{
    LBM::readConditions();
    Omega=1/(3*(nuLB)+0.5);
}

void LBM::readConditions()
{
    float X[6];
    char c[15];
    char wallBC[4];
    walls=false;

    ifstream fin("InitialConditions", ios::in);

    if (fin.is_open()){
        int i=0;
        fin>>c>>X[i];
            while(!fin.eof())
            {
                i++;
                if(i<7)
                    {fin>>c>>X[i];}
                else if(i==7)
                    {fin>>c>>obstacleType;}
                else
                    {
                        fin>>c>>wallBC;
                        if(strcmp("yes",wallBC)==0)
                            {
                                walls=true;
                                cout<<"walls BC true"<<endl;
                            }
                    }
            }
            fin.close();

        iterNum=    	X[0];
        uLB=        	X[1];
        nuLB=       	X[2];
        Re=         	X[3];
        aspectRatio=	X[4];
		saveInterval=	X[5];
		firstSaved=		X[6];
    }
    else{cout<<"Error reading initial conditions"<<endl;}
}


LBM::~LBM(){}
