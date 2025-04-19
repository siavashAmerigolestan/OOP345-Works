/*////////////////////////////////////////////////////////////////////////////
                               OOP345 Workshop4-1
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-12-09
Authenticity Declaration:
I declare that this submission is the result of my own work and I only copied
the code that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or
3rd party content provider.
////////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
#include <iostream>

namespace seneca {
    class Station {
        int m_id;
        std::string m_name;
        std::string m_description;
        size_t m_serialNumber;
        size_t m_numberOfItem;
        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif

