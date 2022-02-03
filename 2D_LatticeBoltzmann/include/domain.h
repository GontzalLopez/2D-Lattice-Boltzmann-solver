#ifndef DOMAIN_H
#define DOMAIN_H

using namespace std;


class domain
{
    public:
        int **ObstacleNodes;     
        void createObstacle(int Nx, int Ny, char *obstacleType);

        domain();
        virtual ~domain();

};

#endif // DOMAIN_H
