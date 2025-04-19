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
#include <utility>
#include "logger.h"
#include "event.h"
using namespace std;

namespace seneca {

	// Default constructor 
	Logger::Logger() {
		m_event = nullptr;
		m_numberOfEvents = 0;
	}

	// Destructor 
	Logger::~Logger() {
		delete[] m_event;
	}

	// Move constructor
	Logger::Logger(Logger&& rhs) noexcept {
		*this = std::move(rhs);
	}

	// Move assignment operator
	Logger& Logger::operator = (Logger&& rhs) noexcept {
		if (this != &rhs) {
			m_numberOfEvents = rhs.m_numberOfEvents;
			m_event = rhs.m_event;
			rhs.m_event = nullptr;
			rhs.m_numberOfEvents = 0;
		}
		return *this;
	}

	// Adds an event to the logger's collection of events.
	void Logger::addEvent(const Event& event) {
		Event* events = new Event[m_numberOfEvents + 1];
		for (size_t i = 0; i < m_numberOfEvents; i++) {
			events[i] = m_event[i];
		}
		events[m_numberOfEvents] = event;
		delete[] m_event;
		m_event = events;
		m_numberOfEvents++;
	}

	// Friend function to output the logger's details
	std::ostream& operator<<(std::ostream& ostr, const Logger& logger) {
		for (size_t i = 0; i < logger.m_numberOfEvents; i++) {
			ostr << logger.m_event[i] << endl;
		}
		return ostr;
	}
}