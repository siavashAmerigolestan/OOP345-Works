/*////////////////////////////////////////////////////////////////////////////
							   OOP345 Workshop4-3
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
#include "Workstation.h"

namespace seneca {
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const std::string& recordStr) : Station(recordStr) {}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool moved = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (!p_nextStation) {
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(std::move(m_orders.front()));
					else
						g_incomplete.push_back(std::move(m_orders.front()));
				}
				else {
					*p_nextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				moved = true;
			}
		}
		return moved;
	}

	void Workstation::setNextStation(Workstation* station) {
		p_nextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return p_nextStation;
	}

	void Workstation::display(std::ostream& os) const {
		os << getItemName() << " --> " << (p_nextStation ? p_nextStation->getItemName() : "End of Line") << "\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}