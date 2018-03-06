//
// Created by MiBook on 27.02.2017.
//

#ifndef PRJ_FIFO_H
#define PRJ_FIFO_H

#include "simulator.h"

class fifo: public simulator
{
    public:
    /// Constructor for fifo class
    /// \param seconds_per_page seconds to print one page
    fifo(int seconds_per_page) : simulator(seconds_per_page) {}

    /// Simulation of printer's work
    /// \param file path to input file
    void simulate(string file);

    /// destructor
    ~fifo(){}
};


#endif //PRJ_FIFO_H
