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

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Utilities.h"
#include "Station.h"
namespace seneca {
	class CustomerOrder {
		struct Item {
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name; 
		std::string m_product; 
		size_t m_cntItem{ 0 }; 
		Item** m_lstItem{ nullptr };
		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string& rhs);
		CustomerOrder(const CustomerOrder& rhs);
		CustomerOrder& operator=(const CustomerOrder& rhs) = delete;
		CustomerOrder(CustomerOrder&& rhs) noexcept;
		CustomerOrder& operator=(CustomerOrder&& rhs) noexcept;
		virtual ~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif 
