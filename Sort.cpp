#include "Sort.h"

void Sort::merge(std::vector<String>& v, unsigned int start, unsigned int midpoint, unsigned int end)
{
    std::vector<String> left_subarray{ v.begin() + start, v.begin() + midpoint + 1 };
    std::vector<String> right_subarray{ v.begin() + midpoint + 1, v.begin() + end + 1 };

    unsigned int smallest_left{ 0 };
    unsigned int smallest_right{ 0 };
    unsigned int location_in_main{ start };

    while (smallest_left < left_subarray.size() && smallest_right < right_subarray.size())
    {
        if (left_subarray[smallest_left] > right_subarray[smallest_right])
        {
            v[location_in_main] = right_subarray[smallest_right];
            smallest_right += 1;
        }
        else
        {
            v[location_in_main] = left_subarray[smallest_left];
            smallest_left += 1;
        }
        location_in_main += 1;
    }

    while (smallest_left < left_subarray.size())
    {
        v[location_in_main] = left_subarray[smallest_left];
        smallest_left += 1;
        location_in_main += 1;
    }

    while (smallest_right < right_subarray.size())
    {
        v[location_in_main] = right_subarray[smallest_right];
        smallest_right += 1;
        location_in_main += 1;
    }
}

void Sort::mergeSort(std::vector<String>& v, unsigned int start, unsigned int end)
{
    if (end <= start) return;

    unsigned int midpoint = (start + end) / 2;

    mergeSort(v, start, midpoint);
    mergeSort(v, midpoint + 1, end);

    merge(v, start, midpoint, end);
}

void Sort::printInvercedSortedVector(std::vector<String>& v)
{
    size_t counter{ 0 };

    for (size_t i = v.size(); i > 0; --i)
    {
        std::cout << counter << ": " << v[i-1] << '\n';
        ++counter;
    }
}
