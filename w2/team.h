#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include <iostream>
#include <string>
#include "character.h"
namespace seneca {
    class Team {
        std::string m_name{};
        Character** m_contain{};
        size_t m_size{};
        int find(const std::string& c);
    public:
        Team();
        Team(const char* name);
        Team(const Team& rhs);
        Team& operator=(const Team& rhs);
        ~Team();
        Team(Team&& rhs) noexcept;
        Team& operator=(Team&& rhs) noexcept;
        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}


#endif // SENECA_TEAM_H
