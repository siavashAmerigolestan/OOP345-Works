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

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <chrono>
#include <string>


namespace seneca {
	class Event {
		std::string m_name;
		std::chrono::nanoseconds m_duration;

	public:
		// default constructor
		Event();
		// Constructs an Event with a specified name and duration in nanoseconds.
		Event(const char* name, const std::chrono::nanoseconds& duration);
		// Friend function that outputs the event's details to an output stream.
		friend std::ostream& operator<<(std::ostream& ostr, const Event& event);
	};
}

#endif
