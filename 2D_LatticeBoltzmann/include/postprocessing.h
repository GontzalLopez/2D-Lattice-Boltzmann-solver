#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H
#include "simulation.h"


class postProcessing
{
    public:

        void saveToCSV(int itNumber, int var);
        postProcessing(simulation&);
        virtual ~postProcessing();

    protected:

    private:
        simulation simRes;
};

#endif // POSTPROCESSING_H
