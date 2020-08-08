#include "Dynamic_Array.h"
#include <cstring>
#include <iostream>

// Constructors-------------------------------------------------------
DynamicArray::DynamicArray() //default
    : m_length(0), m_capacity(0), m_scaling_factor(2.0), m_data(nullptr)
{
}

DynamicArray::DynamicArray(double scaling_factor, unsigned int capacity) //scaling factor & capacity
    : m_length(0), m_capacity(capacity), m_scaling_factor(scaling_factor)
{
    // create memory on the heap
    m_data = new int[m_capacity];
}

DynamicArray::DynamicArray(double scaling_factor, unsigned int length, int default_value) //scaling factor, length, & a value to fill all spaces
    : m_length(length), m_capacity(length), m_scaling_factor(scaling_factor)
{

    // create memory on the heap
    m_data = new int[m_capacity];

    //go through array and assign default values
    for( unsigned int i = 0; i < m_length; i++ )
    {
        m_data[i] = default_value;
    }
}
//copy constructor
DynamicArray::DynamicArray(const DynamicArray& other)
{
    // use the assignment operator
    (*this) = other;
}

DynamicArray::~DynamicArray()
{
    delete[] m_data;
}

// Getters------------------------------------------------------------
unsigned int DynamicArray::getLength()
{
    return m_length;
}

unsigned int DynamicArray::getCapacity()
{
    return m_capacity;
}

double DynamicArray::getScalingFactor()
{
    return m_scaling_factor;
}

// Setters-----------------------------------------------------------
void DynamicArray::setScalingFactor(double value)
{
    m_scaling_factor = value;
}

// Convert Array to type std::string --------------------------------
std::string DynamicArray::toString()
{
    std::string str("{");
    for (unsigned int i = 0 ; i < m_length ; i++)
    {
        str.append(std::to_string(m_data[i]));
        if (i < m_length - 1) {
            str.push_back(' ');
        }
    }
    str.push_back('}');
    return str;
}

bool DynamicArray::findFirstOf(int value, unsigned int *index)
{

    // assign variable to false
    bool found = false;

    // search the array for the value
    for(unsigned int i = 0; i < m_length; i++)
    {
        if(m_data[i] == value)
        {
            found = true;
            *index = i;
            return found;
        }
    }
    // if value is not found --> return false
    return found;
}

bool DynamicArray::findLastOf(int value, unsigned int *index)
{

    // assign variable to false
    bool found = false;

    // search the array for the value from reverse
    for(unsigned int i = m_length - 1; i >= 0; i--)
    {
        if(m_data[i] == value)
        {
            found = true;
            *index = i;
            return found;
        }
    }
    // if value is not found --> return false
    return found;
}

void DynamicArray::append(int value)
{
    // if we have no data yet --> place in value at index 0
    if(m_data == nullptr)
    {
        // need to create ints on the heap
        m_data = new int[1];
        m_capacity = 1;

        // assign value to first index
        m_data[0] = value;

        // increase length
        m_length = 1;
        return;
    }
    // if array is not full --> add to end
    if(m_length != m_capacity)
    {
        m_data[m_length] = value;
        m_length++;
        return;
    }
    else
    {
        // make new array
        int size = m_capacity * m_scaling_factor;
        int* temp = new int[size];
        //copy data into array
        for (unsigned int i = 0; i < m_capacity; i++)
        {
            temp[i] = this->m_data[i];
        }
        delete this->m_data;
        this->m_data = temp;
        this->m_capacity = size;

        // place new value into the array
        this->m_data[m_length] = value;
        m_length++;
        return;
    }


}

void DynamicArray::prepend(int value)
{

    // if we have no data yet --> place in value at index 0
    if(m_data == nullptr)
    {
        // need to create ints on the heap
        m_data = new int[1];
        m_capacity = 1;

        // assign value to first index
        m_data[0] = value;

        // increase length
        m_length = 1;
        return;
    }

    // if arrray is larger than 1 and length is less than capacity --> create new array of same size and place value at index 0
    if (m_length >= 1 && m_capacity != m_length)
    {
        // make new array
        int* temp = new int[m_capacity];
        //copy data into array
        for (unsigned int i = 0; i < m_capacity; i++)
        {
            // i + 1 --> leave first index open to be added at end
            temp[i + 1] = this->m_data[i];
        }
        delete this->m_data;
        this->m_data = temp;

        // place new value into the array
        this->m_data[0] = value;
        m_length++;
        return;
    }

    // if array is larger than 1 and length is equal to capacity --> new larger array
    if (m_length >= 1 && m_capacity == m_length)
    {
        // make new array
        int size = m_capacity * m_scaling_factor;
        int* temp = new int[size];
        //copy data into array
        for (unsigned int i = 0; i < m_capacity; i++)
        {
            // i + 1 --> so index 0 is open to add new value
            temp[i + 1] = this->m_data[i];
        }
        delete[] this->m_data;
        this->m_data = temp;
        this->m_capacity = size;

        // place new value into the array
        this->m_data[0] = value;
        m_length++;
        return;
    }

}

void DynamicArray::removeLast()
{
    if(m_length == 0)
    {
        return;
    }
    else if (m_length == 1)
    {
        this->clear();
        return;
    }
    else
    {
        m_length--;
        return;
    }
}

void DynamicArray::removeFirst()
{
    // if we have an empty array --> return
    if(m_length == 0 || m_capacity == 0 || m_data == nullptr)
    {
        return;
    }
    // if one element is in array --> clear array
    else if (m_length == 1)
    {
        this->clear();
    }
    // else --> create new array
    else if (m_length > 1)
    {
        // make new array
        int* temp = new int[m_capacity];
        //copy data into array
        for (unsigned int i = 0; i <= m_capacity; i++)
        {
            // i + 1 --> keep index 0 from entering new array
            temp[i] = this->m_data[i + 1];
        }
        // delete old array
        delete[] this->m_data;
        this->m_data = temp;
        m_length--;
        return;
    }



}

void DynamicArray::clear()
{
    // if there is no data --> return
    if(m_data == nullptr)
    {
        return;
    }
    // else --> delete array and reset object
    else
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
        m_capacity = 0;
        return;
    }

}

int& DynamicArray::operator[](unsigned int index)
{
    return m_data[index];
}

DynamicArray& DynamicArray::operator=(const DynamicArray &other)
{
    m_length = other.m_length;
    m_capacity = other.m_capacity;
    m_scaling_factor = other.m_scaling_factor;
    m_data = new int[m_capacity];
    std::memcpy(m_data, other.m_data, sizeof(int) * m_length);
    // this allows statements such as (a = b = c) assuming a, b, and c are all the DynamicArray type
    return (*this);


}
