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
#include <chrono>
#include "timeMonitor.h"
using namespace std;
namespace seneca {
	// Initiates an event with the specified name and records its start time
	void TimeMonitor::startEvent(const char* name) {
		m_start = std::chrono::steady_clock::now();
		m_nameOfEvents = name;
	}
	// Stops the currently running event and returns its details as an Event object.
	Event TimeMonitor::stopEvent() {
		m_end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end - m_start);
		return Event(m_nameOfEvents.c_str(), duration);
	}
}