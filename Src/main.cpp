#include <iostream>
#include <string>
#include "../Include/Dynamic_Array.h"

/* Print Statment */
template <class T>
void print_array(const DynamicArray<T>& array)
{
    std::cout << "\nLength: " << array.length() << std::endl;
    std::cout << "Cap: " << array.capacity() << std::endl;
    for (size_t i = 0; i < array.length(); i++)
        std::cout << array[i] << '\n';
    std::cout << "----------------------------------\n";
}

/* Main Function */
int main()
{
    DynamicArray<std::string> array;
    array.prepend("Matthew");
    print_array(array);
    array.push_back("Corbett");
    print_array(array);


    return 0;
}
