#pragma once
/*
 * Author: Matthew Corbett
 * Date Created: Febuary 2020
 * Description: This class is an object used to represent a dynamic array data structure that stores integers. This class
 *              does not sort the values stored in the array and should allow for repeated values.
 */

#include <cstddef>
#include <string>

template <typename T>
class DynamicArray
{
    private:
        // the number of items currently in the array
        size_t m_length = 0;
        // the number of available spaces in the array
        size_t m_capacity = 2;
        // the scaling factor when resizing the array (always > 1)
        double m_scaling_factor = 0.5f;
        // pointer to the array of integers
        T* m_data = nullptr;
    public:
        // default constructor, capacity = 0, no need to allocate an internal array yet
        DynamicArray() {}

        // default constructor with a scaling factor, creates an array with capacity = capacity
        DynamicArray(double scaling_factor, size_t capacity)
            : m_length(0), m_capacity(capacity), m_scaling_factor(scaling_factor) { m_data = new T[m_capacity]; }

        // copy constructor
        DynamicArray(const DynamicArray& other) { (*this) = other; }

/* Todo: Move constructor */

        // default destructor, free memory of the array here
        ~DynamicArray() { delete[] m_data; }

        // get the number of elements in the array
        const size_t& getLength() const { return m_length; }

        // get the capacity of the array
        const size_t& getCapacity() const { return m_capacity; }

        // get scaling factor Needed by GUI
        const double& getScalingFactor() const { return m_scaling_factor; }

        // set the scaling factor of the array
        void setScalingFactor(double value) { m_scaling_factor = value; }

        void setScalingFactor(double&& value) { m_scaling_factor = std::move(value); }

        // convert the vector into a printable string
        /* std::string toString(); */

        // find the first occurrence of "value" in the array. Return false if the value is not found
        bool findFirstOf(T value, size_t* index);

        // find the last occurrence of "value" in the array. Return false if the value is not found
        bool findLastOf(T value, size_t* index);

        // add a value to the end of the array (resize if necessary)
        void append(T value);

        // add a value to the beginning of the array (resize if necessary)
        void prepend(T value);

        // remove the last value from the array
        void removeLast();

        // remove the first value from the array
        void removeFirst();

        // remove all elements from the array
        // allocated memory should be deleted and the array pointer should now point to NULL
        // capacity and length should be reset to zero
        void clear();

        // overloading the [] operator for read/write access
        T& operator[](size_t index);

        // assignment operator
        DynamicArray& operator=(const DynamicArray &other);
};
