#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include "character.h"
namespace seneca {
    class Guild {
        std::string m_name{};
        Character** m_contain{};
        size_t m_size{};
        int find(const std::string& c);
    public:
        Guild();
        Guild(const char* name);
        Guild(const Guild& rhs);
        Guild& operator=(const Guild& rhs);
        virtual ~Guild();
        Guild(Guild&& rhs) noexcept;
        Guild& operator=(Guild&& rhs) noexcept;
        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}

#endif
