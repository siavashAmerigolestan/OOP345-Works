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

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <chrono>
#include <string>
#include "event.h"

namespace seneca {
	class TimeMonitor {
		std::chrono::time_point<std::chrono::steady_clock> m_start, m_end;
		std::string m_nameOfEvents;
	public:
		// Initiates an event with the specified name and records its start time.
		void startEvent(const char* name);
		// Stops the currently running event and returns its details as an Event object.
		Event stopEvent();
	};
}

#endif
