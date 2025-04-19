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

#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "CustomerOrder.h"
using namespace std;

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str) {
		if (!str.empty()) {
			Utilities utilities;
			size_t next_pos = 0;
			bool more = true;
			m_name = utilities.extractToken(str, next_pos, more);
			m_product = utilities.extractToken(str, next_pos, more);
			m_cntItem = std::count(str.begin(), str.end(), utilities.getDelimiter()) - 1;
			m_lstItem = new Item * [m_cntItem];
			size_t i = 0;

			while (i < m_cntItem) {
				m_lstItem[i] = new Item(utilities.extractToken(str, next_pos, more));
				i++;
			}

			if (m_widthField < utilities.getFieldWidth()) {
				m_widthField = utilities.getFieldWidth();
			}
		}
		else {
			throw "The record is empty";
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& rhs) {
		throw "Copy constructor is not allowed here";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& rhs) noexcept {
		m_name = std::move(rhs.m_name);
		m_product = std::move(rhs.m_product);
		m_cntItem = rhs.m_cntItem;
		m_lstItem = rhs.m_lstItem;
		rhs.m_cntItem = 0;
		rhs.m_lstItem = nullptr;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rhs) noexcept {
		if (this != &rhs) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = std::move(rhs.m_name);
			m_product = std::move(rhs.m_product);
			m_cntItem = rhs.m_cntItem;
			m_lstItem = rhs.m_lstItem;
			rhs.m_cntItem = 0;
			rhs.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				isFilled = false;
			}
		}
		return isFilled;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				isFilled = false;
			}
		}
		return isFilled;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool isFilled = false;
		for (size_t i = 0; i < m_cntItem && !isFilled; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() >= 1) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << "] "
				<< setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - ";
				if (m_lstItem[i]->m_isFilled) {
					os << "FILLED" << endl;
				}
				else {
					os << "TO BE FILLED" << endl;
				}
		}
	}

}
