#pragma once
#include "Player.h"

namespace PDG
{
	class Skill
	{
	public:
		Skill() = default;

		/**
		* @brief Called when the skill is use. Even though if it is not active yet (have turns to be active)
		*/
		void OnSkillUse();

		/**
		* @brief Updates cooldown, duration and certifies to check if it is ready to be active, if so, calls ApplyEffect() as well as
		* UnaplyEffect() when its duration is over.
		*/
		void Tick();

		/**
		* @brief This interface will let child classes to have custom behaviour over the player (or over itself). 
		* Called when the skills has no turns to be active anymore, this is, is ready to go.
		*/
		virtual void ApplyEffect() = 0;

		/**
		* @brief This interface will let child classes to have custom behaviour over the player (or over itself). 
		* Called when the skills duration is over.
		*/
		virtual void UnaplyEffect() = 0;

		/**
		* @brief Let every skill to define its name.
		*/
		virtual std::string GetName() = 0;

		/**
		* @brief Skills can be different conditions based on player stats, for example. 
		* each skill should override this interface with its own conditions
		* this function is checked before a skill is used.
		*/
		virtual bool SkillCondition() = 0;

		/**
		* @brief Returns base cooldown value.
		*/
		int16_t GetBaseCooldown() { return m_Cooldown; }


		/**
		* @brief Retrieves necessary mana to use this skill
		*/
		inline int16_t GetManaCost() const { return m_ManaCost; }

		/**
		* @brief Returns the lefting duration count.
		*/
		inline int16_t GetLeftDuration() const { return m_DurationCount; }
		
		/**
		* @brief Returns if the skill was used but its not active anymore.
		*/
		inline bool WasSkillUsed() const { return m_WasSkillUsed; }

		/**
		* @brief When the duration is over, this function is called. It calls UnaplyEffect() in which will be called in the child class.
		*/
		void OnSkillExpire();


		/**
		* @brief Returns a new object of its class. Used to create new object of child classes, so the Stack can have easier management
		**/
		virtual Skill* GetSkill() = 0;


	protected:
		Skill(Player* owner, int16_t manaCost, int16_t cooldown, int16_t turnsToActivate, int16_t duration);


	private:
		//base values
		const int16_t m_ManaCost, m_Cooldown, m_TurnsToActivate, m_Duration;

		//volatile values
		 int16_t m_TurnsToActivateCount, m_DurationCount;

		 /**
		* @brief Check if the skill was used. Usually this is true if a skill was used but is not active anymore
		*/
		bool m_WasSkillUsed = false; 

		/**
		* @brief Check if the skill is on effect, this is, affecting players status.
		*/
		bool m_EffectApplied = false;

		  //It would be nice to make child classes to edit this string with detailed condition info on the skill usage
		 //and then print it if the player tries to use this skill and the conditions are not met.
		// std::string m_ConditionDescription;

		/**
		* @brief Apply skill effects (calls ApplyEffect()), change m_EffectApplied flag
		* checks for it is an active skill (skill if no duration) if so, after applying its effects
		* init the process for pop the skill from active skills queue.
		*/
		void UseSkill();

	protected:
		/**
		* @brief The owner of the skills, the player who will be affected by this skill. Positively or negatively.
		*/
		Player* m_SkillOwner;
	};
}