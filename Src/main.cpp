#include <iostream>
#include "../Include/Dynamic_Array.h"

/* Print Statment */
template <class T>
void print_array(const DynamicArray<T>& array)
{
    for (size_t i = 0; i < array.length(); i++)
        std::cout << array[i] << '\n';
    std::cout << "----------------------------------\n";
}

/* Main Function */
int main()
{
    DynamicArray<int> array;
    array.push_back(1);
    print_array(array);
    array.push_back(2);
    print_array(array);
    array.push_back(3);
    print_array(array);
    array.push_back(4);
    print_array(array);
    array.push_back(5);
    print_array(array);

    print_array(array);
    return 0;
}
