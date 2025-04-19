/*/////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace seneca {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const std::string& record) {

		if (!record.empty()) {
			Utilities utilities;
			m_id = ++id_generator;
			size_t next_pos = 0;
			bool more = true;

			m_name = utilities.extractToken(record, next_pos, more);
			m_serialNumber = std::stoul(utilities.extractToken(record, next_pos, more));
			m_numberOfItem = std::stoul(utilities.extractToken(record, next_pos, more));

			if (m_widthField < utilities.getFieldWidth()) {
				m_widthField = utilities.getFieldWidth();
			}

			m_description = utilities.extractToken(record, next_pos, more);
		}
		else {
			throw "There is no record";
		}
	}

	const std::string& Station::getItemName() const {
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		return m_numberOfItem;
	}

	void Station::updateQuantity() {
		if (m_numberOfItem > 0) {
			--m_numberOfItem;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		os << setw(3) << right << setfill('0') << m_id << " | "
			<< setfill(' ') << setw(Station::m_widthField) << left << Station::getItemName() << " | "
			<< setw(6) << setfill('0') << right << m_serialNumber << " | " << setfill(' ');

		if (full) {
			os << setw(4) << setfill(' ') << m_numberOfItem << " | " << m_description;
		}
		os << endl;
	}
}