//
// Created by MiBook on 27.02.2017.
//

#include <fstream>
#include <iomanip>
#include "fifo.h"
#include "Windows.h"

void fifo::simulate(string file)
{
    loadworkload(file);                                     // read input file
                                                            // and fill workload

    file = file.replace(file.end() - 3, file.end(), "out"); // change the file's path

    ofstream myfile;                                        // create ofstream

    myfile.open(file);                                      // open output stream

    const string tab = "      ";                            // string for tabulation style

    queue<event> arrived;                                   // queue of events, which already arrived at printer

    int total = workload.size();                            // total size of events
    int aggrLat = 0;                                        // total latency of all print jobs

    double meanLat = 0;                                     // average latency between jobs

    int count = 0;                                          // total timer
    int time = 0;                                           // timer for servicing job

    event printingEvent;                                    // servicing event

    myfile << "FIFO Simulation " << endl << endl;           // write head line

    while (!workload.empty() || !arrived.empty() || time)   // while some file is printed or queues aren't empty
    {
        if (time == count)                                  // if printed event was finished
            time = 0;                                       // set to zero

        event e = workload.front();                         // take first in queue


        while (count == e.arrival_time())                   // if the time has come for some event to arrive
        {
            arrived.push(e);                                // process arrived event
            job j = e.getjob();                             // job for the event

            myfile << tab << "Arriving: " << j;
            myfile << " at " << count << " seconds" << endl;

            workload.pop();                                 // erase event from workload queue

            e = workload.front();                           // get next event
        }


        if (!time && !arrived.empty())                      // if printer is currently free
        {
            printingEvent = arrived.front();                // get next event at arrived queue
            arrived.pop();

            // add latitude of a current event
            aggrLat += count - printingEvent.arrival_time();

            // set time for the current printing task to stop
            time = count + printingEvent.getjob().getnumpages() * seconds_per_page;

            job j = printingEvent.getjob();                 // get job of printing event

            myfile << tab << "Servicing: " << j;
            myfile << " at " << count << " seconds" << endl;

        }

        Sleep(1000);                                        // wait 1 sec
        count++;                                            // increase seconds
    }

    meanLat = (double)aggrLat / (double) total;             // calculate mean latitude

    myfile << endl;

    myfile << tab << "Total jobs: " << total << endl;

    myfile << tab << "Aggregate latency: " << aggrLat << " seconds" << endl;

    myfile << tab << "Mean latency: " << meanLat << endl;

    myfile.close();                                         // close output stream
}


