#ifndef LBM_H
#define LBM_H

class LBM
{
   public:
        int iterNum;            //Number of iterations
        double aspectRatio;	//Domain shape
        double Omega;           //Omega
        double uLB;             //Lattice velocity
        double nuLB;            //Lattice viscosity
        int Re;                 //Reynolds number
	int saveInterval;	
	int firstSaved;
        char obstacleType[10];
        bool walls;

        LBM();
        virtual ~LBM();

   private:
        void readConditions();


};

#endif // LBM_H
