/*/////////////////////////////////////////////////////////////////////////
							   OOP345 Workshop1
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-10-01
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "event.h"
#include "settings.h"
using namespace std;

namespace seneca {
	// default constructor
	Event::Event() : m_name{ "" }, m_duration(0) {
	
	}

	// Constructs an Event with a specified name and duration in nanoseconds.
	Event::Event(const char* name, const std::chrono::nanoseconds& duration) : m_name(name),m_duration(duration) {
	
	}

	// Friend function that outputs the event's details to an output stream.
	ostream& operator<<(std::ostream& ostr, const Event& event) {
		static int counter = 0;
		
		 counter++;
		ostr << std::right << std::setw(2) << counter << ": " << std::right << std::setw(40) << event.m_name << " -> ";
        if (counter <= 9) {
            ostr << std::right << std::setw(11) << std::chrono::duration_cast<std::chrono::nanoseconds>(event.m_duration).count() << " nanoseconds";
        }
		else if (counter <= 18) {
            ostr << std::right << std::setw(8) << std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration).count() << " microseconds";
		}
		else if (counter <= 27) {
            ostr << std::right << std::setw(5) << std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration).count() << " milliseconds";
		}

		else {
            ostr << std::right << std::setw(2) << std::chrono::duration_cast<std::chrono::seconds>(event.m_duration).count() << " seconds";
		}
		return ostr;
	}
}