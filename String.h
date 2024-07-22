#ifndef __STRING_H_
#define __STRING_H_

#include <iostream>

class String
{
public:
	String(const char* source = "");
    String(size_t length);
    String(const std::string& source);
    String(const String& source);     
    String(String&& source) noexcept;    
    ~String();

    String& operator=(const String& source);
    String& operator=(String&& source) noexcept;
   
    String& operator+=(const char* source);
    String& operator+=(const String& source);
    String& operator+=(const std::string& source);

    friend String operator+(const String& firstString, const String& secondString);
    friend String operator+(const char* firstString, const String& secondString);
    friend String operator+(const String& firstString, const char* secondString);
    friend String operator+(const std::string firstString, const String& secondString);
    friend String operator+(const String& firstString, const std::string secondString);

    friend bool operator>(const String& firstString, const String& secondString);

    char operator[](size_t index);

    friend std::ostream& operator<< (std::ostream& out, const String& string);
    friend std::istream& operator>> (std::istream& is, String& source);
    
    template <typename T>
    static void copyDataToNewData(const T& oldData, const size_t oldLength, char* newData);

    template <typename T>
    static void addSourceToNewData(const T& oldData, const size_t oldLength, const size_t initialLength, char* newData);

    size_t length();

private:
    size_t m_length{};
    size_t m_capacity{};
    char* m_data{};
};

//std::istream& operator>> (std::istream& is, String& source);

#endif	// __STRING_H_
