#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include <iostream>
#include "character.h"
#include "characterTpl.h"
#include "abilities.h"

namespace seneca {
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        Ability_t m_ability{};
        Weapon_t m_weapon[2]{};

    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon,
            Weapon_t secondaryWeapon) : CharacterTpl<T>(name, healthMax) {
            m_baseDefense = baseDefense;
            m_baseAttack = baseAttack;
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        Barbarian(const Barbarian< T, Ability_t, Weapon_t > & rhs) : CharacterTpl<T>(rhs) {
            m_baseAttack = rhs.m_baseAttack;
            m_baseDefense = rhs.m_baseDefense;
            m_weapon[0] = rhs.m_weapon[0];
            m_weapon[1] = rhs.m_weapon[1];
            m_ability = rhs.m_ability;
        }
    

        int getAttackAmnt() const override {
            return m_baseAttack + (static_cast<double>(m_weapon[0]) / 2) + (static_cast<double>(m_weapon[1]) / 2);
        }

        int getDefenseAmnt() const {
            return m_baseDefense;
        }

        Character* clone() const {
            return new Barbarian< T, Ability_t, Weapon_t >(*this);
        }

        void attack(Character* enemy) {
            std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
            m_ability.useAbility(this);
            int damage = getAttackAmnt();
            m_ability.transformDamageDealt(damage);
            std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;
            enemy->takeDamage(damage);
        }


        void takeDamage(int dmg) {
            std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << "." << " Reducing damage received." << std::endl;
            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;
            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif 
