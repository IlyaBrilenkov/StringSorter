#include "String.h"
#include <cstring> 
#include <ctype.h>
#include <string.h>
#include <assert.h> 

String::String(const char* source)
    : m_length(strlen(source)),
      m_capacity(m_length +1),
      m_data(new char[m_capacity])
{
    for (size_t i = 0; i < m_capacity; ++i)
        m_data[i] = source[i];
}

String::String(size_t length)
    : m_length(length),
      m_capacity(m_length + 1),
      m_data(new char[m_capacity])
{}

String::String(const std::string& source)
{
    if (!source.empty())
    {
        m_length = source.length();
        m_capacity = m_length + 1;
        m_data = new char[m_capacity];

        for (size_t i = 0; i < m_capacity; ++i)
            m_data[i] = source[i];
    }        
}

String::String(const String& source)
{
    if (source.m_data)
    {
        m_length = source.m_length;
        m_capacity = source.m_capacity;
        m_data = new char[m_capacity];

        for (size_t i = 0; i < m_capacity; ++i)
            m_data[i] = source.m_data[i];
    }
}

String::String(String&& source) noexcept
    : m_length(source.m_length),
      m_capacity(source.m_capacity),
      m_data(source.m_data)
{
    source.m_data = nullptr;
}

String::~String()
{
    delete[] m_data;
}

String& String::operator=(const String& source)
{
    if (this != &source)
    {
        delete[] m_data;
        m_length = source.m_length;
        m_capacity = source.m_capacity;

        if (source.m_data)
        {
            m_data = new char[m_capacity];

            for (size_t i = 0; i < m_capacity; ++i)
                m_data[i] = source.m_data[i];
        }
        else
            m_data = nullptr;
    }
    return *this;
}

String& String::operator=(String&& source) noexcept
{
    if (this != &source)
    {
        delete[] m_data;
        m_length = source.m_length;
        m_capacity = source.m_capacity;

        m_data = source.m_data;
        source.m_data = nullptr;
    }

    return *this;
}

String& String::operator+=(const String& source)
{
    if (source.m_data)
    {
        char* newData{ new char[m_length + source.m_capacity] };
        
        copyDataToNewData(m_data, m_length, newData);
        addSourceToNewData(source.m_data, source.m_length, m_length, newData);
                
        delete[] m_data;
        m_data = newData;
        m_length += source.m_length;
        m_capacity += source.m_length;
    }
    return *this;
}

String& String::operator+=(const char* source)
{
    size_t sourceLength{ strlen(source) };
    if (sourceLength)
    {
        size_t sourceCapacity{ sourceLength + 1 };

        char* newData{ new char[m_length + sourceCapacity] };

        copyDataToNewData(m_data, m_length, newData);
        addSourceToNewData(source, sourceLength, m_length, newData);

        delete[] m_data;
        m_data = newData;
        m_length += sourceLength;
        m_capacity += sourceLength;
    }
    return *this;
}

String& String::operator+=(const std::string& source)
{
    size_t sourceLength{ source.length() };
    if (sourceLength)
    {
        size_t terminateChar{ 1 };
        char* newData{ new char[m_length + sourceLength + terminateChar]};
        
        copyDataToNewData(m_data, m_length, newData);
        addSourceToNewData(source, sourceLength, m_length, newData);
        newData[m_length + source.length()] = '\n';

        delete[] m_data;
        m_data = newData;
        m_length += sourceLength;
        m_capacity += sourceLength;
    }
    return *this;
}

char String::operator[](size_t index)
{
    assert(index < m_length);
    
    return m_data[index];
}

size_t String::length()
{
    return m_length;
}

String operator+(const String& firstString, const String& secondString)
{
    String newString{ firstString.m_length + secondString.m_length };

    String::copyDataToNewData(firstString.m_data, firstString.m_length, newString.m_data);
    String::addSourceToNewData(secondString.m_data, secondString.m_capacity, firstString.m_length, newString.m_data);

    return newString;
}

String operator+(const char* firstString, const String& secondString)
{
    size_t firstStringLength{ strlen(firstString) };

    String newString{ firstStringLength + secondString.m_length };

    String::copyDataToNewData(firstString, firstStringLength, newString.m_data);
    String::addSourceToNewData(secondString.m_data, secondString.m_capacity, firstStringLength, newString.m_data);

    return newString;
}

String operator+(const String& firstString, const char* secondString)
{
    size_t secondStringLength{ strlen(secondString) };

    String newString{ firstString.m_length + secondStringLength };

    String::copyDataToNewData(firstString.m_data, firstString.m_length, newString.m_data);
    String::addSourceToNewData(secondString, secondStringLength, firstString.m_length, newString.m_data);
    newString.m_data[firstString.m_length + secondStringLength] = '\n';

    return newString;
}

String operator+(const std::string firstString, const String& secondString)
{
    size_t firstStringLength{ firstString.length()};

    String newString{ firstStringLength + secondString.m_length };

    String::copyDataToNewData(firstString, firstStringLength, newString.m_data);
    String::addSourceToNewData(secondString.m_data, secondString.m_capacity, firstStringLength, newString.m_data);

    return newString;
}

String operator+(const String& firstString, const std::string secondString)
{
    size_t secondStringLength{ secondString.length()};

    String newString{ firstString.m_length + secondStringLength };

    String::copyDataToNewData(firstString.m_data, firstString.m_length, newString.m_data);
    String::addSourceToNewData(secondString, secondStringLength, firstString.m_length, newString.m_data);
    newString.m_data[firstString.m_length + secondStringLength] = '\n';

    return newString;
}

template <typename T>
void String::copyDataToNewData(const T& oldData, const size_t oldLength, char* newData)
{
    for (size_t i = 0; i < oldLength; ++i)
        newData[i] = oldData[i];
}

template <typename T>
void String::addSourceToNewData(const T& oldData, const size_t oldLength, const size_t initialLength, char* newData)
{
    for (size_t i = 0; i < oldLength; ++i)
        newData[i + initialLength] = oldData[i];
}


bool operator>(const String& firstString, const String& secondString)
{
    size_t minLength{};
    bool isFirstShorter{false};
    if (firstString.m_length >= secondString.m_length)
    {
        minLength = firstString.m_length;
        isFirstShorter = true;
    }
    else
        minLength = secondString.m_length;
    
    for (size_t i = 0; i < minLength; ++i)
    {
        if (tolower(firstString.m_data[i]) > tolower(secondString.m_data[i]))
            return true;
        else if (tolower(firstString.m_data[i]) < tolower(secondString.m_data[i]))
            return false;
    }
    return isFirstShorter;
}

std::ostream& operator<< (std::ostream& out, const String& string)
{
    out << string.m_data;
    return out;
}

std::istream& operator>> (std::istream& is, String& source)
{   
    String newString(127);
    size_t counter{ 0 };
    bool isFirst{ true };

    while (is)
    {
        char c = is.get();
        
        if (isFirst)
        {
            if (!isspace(c))
            {
                newString.m_data[counter] = c;
                ++counter;
                isFirst = false;
            }
        }
        else
        {
            if (isspace(c) && iscntrl(c))
                break;
            else
            {
                newString.m_data[counter] = c;
                ++counter;
            }
            if (counter > 126)
                break;
        }
    }
    
    newString.m_data[counter] = 0;

    newString.m_length = counter;
    newString.m_capacity = counter + 1;

    source = newString;

    return is;
}
