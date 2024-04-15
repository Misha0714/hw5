#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

//add day and worker parameter to see if there the worker working that day is valid 
bool isValid(const AvailabilityMatrix& avail, const DailySchedule& sched, size_t day, Worker_T worker, size_t dailyNeed, size_t maxShifts) {
    // Check if the worker is available on the current day
    if (!avail[day][worker]) {

        return false;
    }
    // for (size_t i = 0; i < sched.size(); ++i) {
    //     const std::vector<Worker_T>& daySchedule = sched[i];
    //     for (Worker_T w : daySchedule) {
    //         if (w == worker) {
    //             shifts++;
    //             if (shifts > maxShifts) return false;
    //         }
    //     }
    // Check if the worker has already reached the maximum shifts
    //use a map 
    size_t shifts = 0;
    std::map<Worker_T, int> workerShifts;
    shifts = workerShifts[worker]; 

    if(shifts >= maxShifts) {
        return false; 
    
    } else {
        shifts++;
        workerShifts[worker] = shifts; 
        return true;
    }
}

//add day parameter and used parameter 
bool scheduleHelper(const AvailabilityMatrix& avail, size_t day, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::map<Worker_T, int>& workerShifts) {
    size_t numWorkers = avail[0].size();
    size_t numDays = avail.size();

    // Base case: all days scheduled
    if (day == numDays) return true;

    // Try assigning workers for the current day
    for (size_t worker = 0; worker < numWorkers; ++worker) {
        //if the worker is not used and it is valid to scheudule them for day 
        if (workerShifts[worker] < maxShifts && isValid(avail, sched, day, worker, dailyNeed, maxShifts)) {
            // Then Assign the worker
            sched[day].push_back(worker);
            //used[worker] = 1; //modify 
            workerShifts[worker] += 1; 

            // If enough workers are scheduled for the day, proceed to the next day
            if (sched[day].size() == dailyNeed) {
                if (scheduleHelper(avail, day + 1, dailyNeed, maxShifts, sched, workerShifts)) {
                    return true;  // Valid schedule found
                }
            } else {
                // Otherwise, continue assigning workers for the current day
                if (scheduleHelper(avail, day, dailyNeed, maxShifts, sched, workerShifts)) {
                    return true;  // Valid schedule found
                }
            }

            // Backtrack if no solution found
            sched[day].pop_back();
            workerShifts[worker] -= 1; 
        }
    }

    // No valid assignment found for this day
    return false;

}

// Add your implementation of schedule() and other helper functions here
bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched)
{
    // Check if availability matrix is empty
    if (avail.empty()) {
        return false;
    }

    // Calculate the number of workers and days
    size_t numWorkers = avail[0].size();
    size_t numDays = avail.size();

    // Initialize the schedule with empty slots
    sched.clear();
    sched.resize(numDays);
    
    // Initialize a vector to track the number of shifts each worker has worked
    int shifts = 0; 
    //std::map<int, int> used(numWorkers, shifts);

    std::map<Worker_T, int> workerShifts;
    // Initialize a map to track whether each worker has been used
    //std::map<Worker_T, int> used;

    // Start backtracking from the first day
    return scheduleHelper(avail, 0, dailyNeed, maxShifts, sched, workerShifts);


}

