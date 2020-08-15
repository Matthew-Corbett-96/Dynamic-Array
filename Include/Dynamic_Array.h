#pragma once
/*
 * Author: Matthew Corbett
 * Date Created: Febuary 2020
 * Description: This class is an object used to represent a dynamic array data structure that stores any type. This class
 *              does not sort the values stored in the array and should allow for repeated values.
 */

#include <cstddef>
#include <stdexcept>

template <typename T>
class DynamicArray
{
    private:
        // the number of items currently in the array
        size_t m_length = 0;
        // the number of available spaces in the array
        size_t m_capacity = 2;
        // the scaling factor when resizing the array (always > 1)
        double m_scaling_factor = 1.5f;
        // pointer to the array of integers
        T* m_data = nullptr;

        void Realloc(size_t new_capacity)
        {
            if (m_length > new_capacity)
                m_length = new_capacity;

            // make new array
            T* temp = new T[new_capacity];
            //Move data into array
            for (size_t i = 0; i < m_length; i++)
                temp[i] = std::move(m_data[i]);

            delete m_data;
            m_data = temp;
            m_capacity = new_capacity;
        }
    public:
        // default constructor, capacity = 0, no need to allocate an internal array yet
        DynamicArray() {}

        // default constructor with a scaling factor, creates an array with capacity = capacity
        DynamicArray(double scaling_factor, size_t capacity)
            : m_capacity(capacity), m_scaling_factor(scaling_factor) { m_data = new T[m_capacity]; }

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
        void push_back(const T& value)
        {
            // if we have no data yet --> place in value at index 0
            if(m_data == nullptr)
            {
                // need to create ints on the heap
                m_data = new T[2];
                m_capacity = 2;
                m_length = 2;

                // assign value to first index
                m_data[0] = value;
                return;
            }
            // if array is not full --> add to end
            if(m_length != m_capacity)
            {
                m_data[m_length++] = value;
                return;
            }
            // Call Realloc and grow array
            Realloc(m_length * m_scaling_factor);
            m_data[m_length++] = value;
            return;
        }

        // add a value to the end of the array (resize if necessary)
        // Rvalue Ref
        void push_back(T&& value)
        {
            // if we have no data yet --> place in value at index 0
            if(m_data == nullptr)
            {
                // need to create ints on the heap
                m_data = new T[2];
                m_capacity = 2;
                m_length = 2;

                // assign value to first index
                m_data[0] = std::move(value);
                return;
            }
            // if array is not full --> add to end
            if(m_length != m_capacity)
            {
                m_data[m_length++] = std::move(value);
                return;
            }
            // Call Realloc and grow array
            Realloc(m_length * m_scaling_factor);
            m_data[m_length++] = std::move(value);
            return;
        }

        // add a value to the beginning of the array (resize if necessary)
        void prepend(const T& value)
        {
            // if we have no data yet --> place in value at index 0
            if(m_data == nullptr)
            {
                // need to create ints on the heap
                m_data = new T[2];
                m_capacity = 2;
                m_length = 2;
                // assign value to first index
                m_data[0] = value;
                return;
            }

            // if array is larger than 1 and length is less than capacity --> create new array of same size and place value at index 0
            if (m_capacity != m_length)
            {
                // make new array
                T* temp = new T[m_capacity];
                //copy data into array
                // i + 1 --> leave first index open to be added at end
                for (size_t i = 0; i < m_capacity; i++)
                    temp[i + 1] = m_data[i];
                delete[] m_data;
                m_data = temp;
                // place new value into the array
                m_data[0] = value;
                m_length++;
                return;
            }

            // if array is larger than 1 and length is equal to capacity --> new larger array
            if (m_capacity == m_length)
            {
                // make new array
                T* temp = new T[m_capacity * m_scaling_factor];
                //copy data into array
                // i + 1 --> so index 0 is open to add new value
                for (size_t i = 0; i < m_capacity; i++)
                    temp[i + 1] = m_data[i];
                delete[] m_data;
                m_data = temp;
                m_capacity *= m_scaling_factor;
                // place new value into the array
                m_data[0] = value;
                m_length++;
                return;
            }
        }

        // add a value to the beginning of the array (resize if necessary)
        // Rvalue Ref Option
        void prepend(T&& value)
        {
            // if we have no data yet --> place in value at index 0
            if(m_data == nullptr)
            {
                // need to create on the heap
                m_data = new T[2];
                m_capacity = 2;
                m_length = 2;
                // assign value to first index
                m_data[0] = std::move(value);
                return;
            }

            // if array is larger than 1 and length is less than capacity --> create new array of same size and place value at index 0
            if (m_capacity != m_length)
            {
                // make new array
                T* temp = new T[m_capacity];
                //copy data into array
                // i + 1 --> leave first index open to be added at end
                for (size_t i = 0; i < m_capacity; i++)
                    temp[i + 1] = std::move(m_data[i]);
                delete[] m_data;
                m_data = temp;
                // place new value into the array
                m_data[0] = std::move(value);
                m_length++;
                return;
            }
            // if array is larger than 1 and length is equal to capacity --> new larger array
            if (m_capacity == m_length)
            {
                // make new array
                T* temp = new T[m_capacity * m_scaling_factor];
                //copy data into array
                // i + 1 --> so index 0 is open to add new value
                for (size_t i = 0; i < m_capacity; i++)
                    temp[i + 1] = std::move(m_data[i]);
                delete[] m_data;
                m_data = temp;
                m_capacity *= m_scaling_factor;
                // place new value into the array
                m_data[0] = std::move(value);
                m_length++;
                return;
            }
        }

        // remove the last value from the array
        void removeLast()
        {
            // if there is no data --> return
            if(m_length == 0 || m_data == nullptr)
                return;
            // if length is 1 --> call clear method
            if (m_length == 1)
            {
                clear();
                return;
            }
            // otherwise, shirk size by 1
            m_length--;
            return;
        }

        // remove the first value from the array
        void removeFirst()
        {
            // if we have an empty array --> return
            if(m_length == 0 || m_capacity == 0 || m_data == nullptr)
                return;
            // if one element is in array --> clear array
            else if (m_length == 1)
                clear();
            // else --> create new array
            else
            {
                // make new array
                T* temp = new T[m_capacity];
                //copy data into array
                for (size_t i = 0; i <= m_capacity; i++)
                    temp[i] = m_data[i + 1];
                // delete old array
                delete[] m_data;
                m_data = temp;
                m_length--;
                return;
            }
            return;
        }

        // remove all elements from the array --> deallocate all memory
        void clear()
        {
            // if there is no data --> return
            if(m_data == nullptr)
                return;
            // else --> delete array and reset object
            delete[] m_data;
            m_data = nullptr;
            m_length = 0;
            m_capacity = 0;
            return;
        }

        // overloading the [] operator for read/write access
        T& operator[](size_t index)
        {
            if(index >= m_length)
                throw std::length_error("Out of Range");

            return m_data[index];
        }
        const T& operator[](size_t index) const
        {
            if(index >= m_length)
                throw std::length_error("Out of Range");

            return m_data[index];
        }

        // assignment operator
        /* DynamicArray& operator=(const DynamicArray& other) */
        /* { */
        /*     m_length = other.m_length; */
        /*     m_capacity = other.m_capacity; */
        /*     m_scaling_factor = other.m_scaling_factor; */
        /*     m_data = new T[m_capacity]; */
        /*     std::memcpy(m_data, other.m_data, sizeof(T) * m_length); */
        /*     // this allows statements such as (a = b = c) assuming a, b, and c are all the DynamicArray type */
        /*     return (*this); */
        /* } */
};
