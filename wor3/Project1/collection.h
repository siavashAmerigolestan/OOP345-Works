#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <string>
#include <vector>
#include "mediaItem.h"

namespace seneca {
	class Collection {
		std::string m_name{};
		std::vector<MediaItem*> m_items{};
		void (*m_observer)(const Collection& col, const MediaItem& item) = nullptr;
	public:
		Collection(const std::string& name) : m_name{ name } {}
		Collection(const Collection&) = delete;
		Collection& operator=(const Collection&) = delete;
		Collection(Collection&&) noexcept = delete;
		Collection& operator=(Collection&&) noexcept = delete;
		virtual ~Collection();
		const std::string& name() const { return m_name; }
		size_t size() const { return m_items.size(); }
		void setObserver(void (*observer)(const Collection& col, const MediaItem& item)) { m_observer = observer; }
		Collection& operator+=(MediaItem* item);
		MediaItem* operator[](size_t idx) const;
		MediaItem* operator[](const std::string& title) const;
		void removeQuotes();
		void sort(const std::string& field);
	};
	std::ostream& operator <<(std::ostream& out, const Collection& rhs);
}

#endif
