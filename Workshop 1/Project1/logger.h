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

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include <iostream>
#include "event.h"

namespace seneca {
	class Logger {
		Event* m_event;
		size_t m_numberOfEvents;
	public:
		// Default constructor 
		Logger();
		// Destructor 
		~Logger();
		// Deleted copy constructor to prevent copying of Logger instances.
		Logger(const Logger& rhs) = delete;
		// Deleted copy assignment operator to prevent copying of Logger instances.
		Logger& operator = (const Logger& rhs) = delete;
		// Move constructor
		Logger(Logger&& rhs) noexcept;
		// Move assignment operator
		Logger& operator = (Logger&& rhs) noexcept;
		// Adds an event to the logger's collection of events.
		void addEvent(const Event& event);
		// Friend function to output the logger's details
		friend std::ostream& operator<<(std::ostream& ostr, const Logger& logger);
	};
}
#endif
