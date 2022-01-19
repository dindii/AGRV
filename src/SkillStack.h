#pragma once


namespace PDG
{
	//avoiding circular dependency
	class Player;
	class Skill;

	class SkillStack
	{
	public:
		/**
		* @brief Constructor, set member variables, reserve space on m_Skills and m_ActiveSkills vectors as well as init it with nullptr.
		*/
		SkillStack(Player* owner);

		
		/**
		* @brief Destructor, destroys the skills that now are owned by us.
		*/
		~SkillStack();

		/**
		* @brief Calls the skill OnSkillUse() function as well as add the skill in the m_ActiveSkills. A queue for the active (busy) skills.
		* @return Returns false if the skill conditions are not met.
		*/
		bool UseSkill(int16_t desiredSkill);

		/**
		* @brief Calls Tick() in every skill. This let it to mantain its own cooldown, duration, turns to be active etc
		*/
		void Tick();


		/**
		* @brief Returns the selected skills mana cost
		*/
		int16_t GetSkillManaCost(int16_t skillIndex);

		/**
		* @brief Returns the selected skill is on cooldown.
		* @return true if is on cooldown and false otherwise.
		*/
		bool CheckSkillCooldown(int16_t skill);

		/**
		* @brief Check if the skill is on the registered skills list. This is, if the skill exists
		* @return true if it does exist and false otherwise.
		*/
		bool ValidateSkill(int16_t skill);

		/**
		* @brief Get the name of all skills that are currently affecting players stats
		*/
		std::vector<std::string> GetOnEffectSkillNames();

		/**
		* @brief Get the lefting duration of all skills that are currently affecting players stats
		*/
		std::vector<int16_t> GetOnEffectSkillsDuration();

		/**
		* @brief Get the name of all registered skills.
		*/
		std::vector<std::string> GetAvaiableSkillNames();

	private:
		/**
		* @brief Remove a skill from the active skills vector.
		*/
		void PopSkill(int16_t index);

		std::vector<Skill*> m_AvaiableSkills;

		/**
		* @brief Store all the skills that currently are affecting player stats
		*/
		std::vector<Skill*> m_ActiveSkills;

		/**
		* @brief Keep track of the cooldown of all skills.
		*/
		std::vector<int16_t> m_SkillCooldown;

		/**
		* @brief Player reference. It is passed to the skills on creation.
		*/
		Player* m_SkillsOwner;



	};
}