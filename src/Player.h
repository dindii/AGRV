#pragma once
#include "SkillStack.h"
namespace PDG
{

//class SkillStack;

#define DEFAULT_HEALTH 25
#define DEFAULT_MANA 1
#define DEFAULT_STRENGTH 2

	struct PlayerStats
	{
		int Health	 = DEFAULT_HEALTH;
		int Mana	 = DEFAULT_MANA;
		int Strength = DEFAULT_STRENGTH;
	};

	class Player
	{
	public:
		Player();
		~Player();

		/**
		* @brief Calls Stacks Tick() function, i.e, updates every skills (cooldown, duration, turns to be active etc)
		*/
		void Tick();

		inline int GetHealth()       const { return m_Stats.Health; }
		inline int GetMana()	     const { return m_Stats.Mana; }
		inline int GetStrength()     const { return m_Stats.Strength; }
		inline std::string GetName() const { return m_CharactersName; }


		/**
		* @brief Set health and clamp it to never get below zero
		*/
		void SetHealth(int newHealth);

		/**
		* @brief Set mana and clamp it to never get below zero
		*/
		void SetMana(int newMana);

		/**
		* @brief Set strength and clamp it to never get below zero
		*/
		void SetStrength(int newStrength);

		void SetCharactersName(std::string newName) { m_CharactersName = newName; } 

		/**
		* @brief Returns a pointer to the SkillStack member class, useful to query for skills cooldown, remaining duration, mana cost etc
		*/
		SkillStack* GetPlayerSkills() { return m_Skills; }

	private:
		/**
		* @brief Base player stats.
		*/
		PlayerStats m_Stats;
		std::string m_CharactersName;

		/**
		* @brief Contain all players skills
		*/
		SkillStack* m_Skills;
	};
}