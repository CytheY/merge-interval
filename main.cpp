/**
 * Author: Julian Schneider, 2019
 * 
 * This programs implements an algorithm which takes a list of intervals
 * and returns a result set of overlapping intervals merged into each other based on their lower 
 * and upper boundaries. All non overlapping intervals remain untouched.
 **/

#include <utility>
#include <iostream>
#include <vector>
#include <algorithm> 
#include <assert.h>

/**
 * Represents an interval with a lower boundary min and an upper boundary max.
 **/
class Interval 
{
    public:
        Interval(int min, int max):min(min), max(max){}
        int min;
        int max;
};

/**
 * Utility function which pretty prints interval vectors.
 **/
void printIntervals(std::vector<Interval> intervals)
{
    for(Interval interval : intervals) 
    {
        std::cout << "[" << interval.min << "," << interval.max << "]" << std::endl;
    }
}

/**
 * The merge function takes a std::vector<Interval> as argument containing 
 * intervals ranges. It merges the different intervals into each other.
 * It returns a std::vector<Interval> containing the merged intervals.
 * 
 * To detect overlapping intervals the boundaries of an interval are compared 
 * to the boundaries of all other intervals. This is done by reverse iterating 
 * through the input set and then comparing the "last" interval to all other 
 * intervals by iterating forward through the set.
 * 
 * When some interval is a subset of some compared interval it is simply deleted 
 * from the input set. In this case the last element of the input set is 
 * deleted and it continues with the next interval from the back.
 *  
 * When the currently visited interval is overlapping with a compared interval, 
 * the currently visited interval (last element in set) is deleted and the other 
 * interval (somewhere else in the set) is updated with the new boundary information.
 **/ 
std::vector<Interval> merge(std::vector<Interval> list)
{ 
    for(auto it = list.end() - 1; it >= list.begin(); --it) 
    {
        auto currentInterval = (*it);
        for(std::vector<Interval>::iterator iter = list.begin(); iter < list.end(); ++iter)
        {
            if(it == iter)
            {
                // skip if currentInterval == compInterval
                continue;
            }

            auto compInterval = (*iter);
            if(currentInterval.min >= compInterval.min && currentInterval.max <= compInterval.max)
            {
                // Currently visited interval is complete subset of some other interval.
                // Can be ignored -> delete it.
                list.erase(it);
                break;
            }

            if(compInterval.min <= currentInterval.max && currentInterval.max <= compInterval.max
                && currentInterval.min < compInterval.min)
            {
                // Overlaps with some other interval.
                // Update the compared interval
                (*iter).min = currentInterval.min;
                (*iter).max = compInterval.max;
                
                // Delete currently visited interval
                list.erase(it);
                break;
            }
        }  
    }

    return list;
}

/**
 * Simple test function which executes the merge function and compares the resulting 
 * interval vector with an expected vector. Uses std::equal to compare result with expected value.
 * First parameter is the set of intervals going to be merged.
 * Second parameter is the expected result set of intervals.
 * Third parameter is a verbose boolean flag to enable pretty printing.
 **/
bool testMerge(std::vector<Interval> input, std::vector<Interval> expected, bool verbose)
{
    std::cout << "************ Start Test ************" << std::endl;
    std::vector<Interval> result = merge(input);

    if(verbose)
    {
        std::cout << "----------- Input ----------" << std::endl;
        printIntervals(input);
        std::cout << "----------- Result ----------" << std::endl;
        printIntervals(result);
        std::cout << "----------- Expected ----------" << std::endl;
        printIntervals(expected);
    }
    
    bool equal = std::equal(result.begin(), result.end(), expected.begin(), 
    [](const Interval& a, const Interval& b)
                { return a.min == b.min && a.max == b.max; });

    if(result.size() != expected.size())
    {
        std::cout << "************ Test Failed ************" << std::endl;
        std::cout << "Result set size: " << result.size() << ", Expected set size: " << expected.size() << std::endl;
        std::cout << "*************************************" << std::endl;
    }else if(!equal)
    {
        std::cout << "************ Test Failed ************" << std::endl;
        std::cout << "Result set is not equal to the expected set" << std::endl;
        std::cout << "*************************************" << std::endl;
    }else
    {
        std::cout << "************ Test Successfull ************" << std::endl;
    }
}

/**
 * Main class for testing the merge function for different input sets.
 **/
int main()
{
    bool verbose = true;

    std::vector<Interval> intervalList;

    intervalList.push_back(Interval(25,30)); // result should be [25,30] [2,23]
    intervalList.push_back(Interval(2,19));
    intervalList.push_back(Interval(14,23));
    intervalList.push_back(Interval(4,8));
    testMerge(intervalList, std::vector<Interval>{Interval(25,30), Interval(2,23)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,5));  // result should be [1:10]
    intervalList.push_back(Interval(5,10)); 
    testMerge(intervalList, std::vector<Interval>{Interval(1,10)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,4));  // result should be [1:4] [5,10]
    intervalList.push_back(Interval(5,10)); 
    testMerge(intervalList, std::vector<Interval>{Interval(1,4), Interval{5,10}}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,4));  // result should be [1:4]
    intervalList.push_back(Interval(2,4)); 
    testMerge(intervalList, std::vector<Interval>{Interval(1,4)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,4));  // result should be [1:5]
    intervalList.push_back(Interval(2,5)); 
    testMerge(intervalList, std::vector<Interval>{Interval(1,5)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,3));  // result should be [1:4]
    intervalList.push_back(Interval(1,4)); 
    testMerge(intervalList, std::vector<Interval>{Interval(1,4)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,4));  // result should be [1:4]
    intervalList.push_back(Interval(1,4)); 
    testMerge(intervalList, std::vector<Interval>{Interval(1,4)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(1,3));  // result should be [1:5]
    intervalList.push_back(Interval(2,4)); 
    intervalList.push_back(Interval(3,5));
    testMerge(intervalList, std::vector<Interval>{Interval(1,5)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(3,30));  // result should be [1:2] [3,40]
    intervalList.push_back(Interval(10,20));
    intervalList.push_back(Interval(3,30));
    intervalList.push_back(Interval(1,2));
    intervalList.push_back(Interval(27,40));
    testMerge(intervalList, std::vector<Interval>{Interval(1,2), Interval(3,40)}, verbose);

    intervalList.clear();
    intervalList.push_back(Interval(3,30));  // result should be [3:30]
    testMerge(intervalList, std::vector<Interval>{Interval(3,30)}, verbose);

    return 0;
}