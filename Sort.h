#ifndef __SORT_H_
#define __SORT_H_

#include "String.h"
#include <vector>

class Sort
{
public:
    static void mergeSort(std::vector<String>& v, unsigned int start, unsigned int end);
    static void printInvercedSortedVector(std::vector<String>& v);

private:
    static void merge(std::vector<String>& v, unsigned int start, unsigned int midpoint, unsigned int end);
};


#endif	// __SORT_H_
