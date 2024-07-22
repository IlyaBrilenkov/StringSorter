#include "String.h"
#include "Sort.h"
#include <vector>

#include <thread>
#include <chrono>

int main()
{    
    std::vector<String> listOfStrings{};
    bool repeat{ true };

    std::cout << "Enter as many strings as you want. Enter 'q' to see a sorted list of the entered strings\n";

    while (repeat)
    {       
        String newString{};
        std::cin >> newString;

        if (newString[0] == 'q' && newString.length() == 1)
        {
            std::cout << "\nSorted strings: \n";
            Sort::mergeSort(listOfStrings, 0, listOfStrings.size()-1);
            Sort::printInvercedSortedVector(listOfStrings);
            repeat = false;
        }
        else
            listOfStrings.push_back(newString);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

