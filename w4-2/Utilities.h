/*////////////////////////////////////////////////////////////////////////////
                               OOP345 Workshop4-2
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-12-10
Authenticity Declaration:
I declare that this submission is the result of my own work and I only copied
the code that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or
3rd party content provider.
////////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
namespace seneca {
    class Utilities {
        size_t m_widthField = 1; 
        static char m_delimiter;
        void trim(std::string& str);

    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}
#endif 