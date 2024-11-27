/*/////////////////////////////////////////////////////////////////////////
							   OOP345 Workshop3
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-11-24
/////////////////////////////////////////////////////////////////////////*/

#include <algorithm>
#include "collection.h"

namespace seneca {
	Collection::~Collection() {
		m_observer = nullptr;
		for (auto& item : m_items)
			delete item;
	}

	Collection& Collection::operator+=(MediaItem* item) {
		bool found = false;
		for (size_t i = 0; i < this->size() && !found; i++) {
			if (m_items[i]->getTitle() == item->getTitle()) {
				found = true;
			}
		}

		if (!found) {
			m_items.push_back(item);
			if (m_observer) {
				m_observer(*this, *item);
			}
		}
		else {
			delete item;
		}

		return *this;
	}

	MediaItem* Collection::operator[](size_t idx) const {
		if (idx < 0 || idx > m_items.size()) {
			throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
		}

		return m_items[idx];
	}

	MediaItem* Collection::operator[](const std::string& title) const {
		auto index = std::find_if(m_items.begin(), m_items.end(), [=](MediaItem* item) {
			return item->getTitle() == title;
			});

		return index != m_items.end() ? *index : nullptr;
	}

	void Collection::removeQuotes() {

		std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
			auto quoteTrimmer = [](const std::string& content) -> std::string {
				if (content.empty()) {
					return content;
				}
				size_t start = (content.front() == '"') ? 1 : 0;
				size_t end = (content.back() == '"') ? content.size() - 1 : content.size();
				return content.substr(start, end - start);
			};

			std::string title = quoteTrimmer(item->getTitle());
			item->setTitle(title);

			std::string summary = quoteTrimmer(item->getSummary());
			item->setSummary(summary);
			});
	}

	void Collection::sort(const std::string& field) {
		if (field == "title") {
			std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
				return a->getTitle() < b->getTitle();
				});
		}
		else if (field == "summary") {
			std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
				return a->getSummary() < b->getSummary();
				});
		}
		else {
			std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
				return a->getYear() < b->getYear();
				});
		}
	}

	std::ostream& operator<<(std::ostream& out, const Collection& rhs) {
		 size_t i = 0;
		while (i < rhs.size()) {
			out << *rhs[i];
			++i;
		}
		return out;
	}
}