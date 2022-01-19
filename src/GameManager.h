#pragma once
#include "Player.h"

namespace PDG
{
	enum EActions : int8_t
	{
		MinimumNone = -1,
		BackAction = 0,

		BasicAttack,
		Skill,

		MaximumNone
	};

	class GameManager
	{
	public:
		/**
		* @brief Constructor, set member variables, create both default players and set the round order
		* by choosing who will start being the Attacking and the Target. 
		*/
		GameManager();

		/**
		* @brief Start the game by initializing the game loop, it only returns when one of the players die.
		* update the players and its skills every iteration. Asks for new actions as well as death check.	
		*/
		void StartGame();

	private:

		/**
		* @brief Print player stats (health, mana and strength)
		* @param Player  - the player in which the stats will be print
		*/
		void PrintPlayerStatus(const Player& player) const;

		/**
		* @brief Print player active skills inside it
		* @param Player  - the player in which the active skills will be shown
		*/
		void PrintPlayerActiveSkills(Player& player);

		/**
		* @brief Ask the player for the next action as well as show the avaiable actions.
		*/
		void ShowActions();

		/**
		* @brief Get the users action input until ValidateActions(EAction) is satisfied. 
		*/
		const EActions GetActions();

		/**
		* @brief Looks for bad action values, returns false if a bad value is found, and true if is valid.
		* @param EActions - The action in which will be checked.
		*/
		bool ValidateActions(const EActions action);
		
		/**
		* @brief Branchs the action, calls attack or a skill action, based on the user action input.
		* @param EActions - The action in which will be branched. At this point, can be normal Attack or Skill action
		*/
		bool ProcessActions(const EActions action);
		
		/**
		* @brief Retrieve and print the avaiable players skills names (based on its added skills)
		*/
		void ShowPlayerSkills();

		/**
		* @brief Get the users skill input until ValidateSkills(int16_t skillIndex) is satisfied.
		*/
		int16_t GetSkills();

		/**
		* @brief Looks for bad skills values, checking if the chosen skill index is above users avaiable skills or below zero.
		* @param int16_t - Skill index that will be checked. This matches to the printed skills and its index
		*/
		bool ValidateSkills(int16_t chosenSkill);

		/**
		* @brief Check if the selected skill is in cooldown
		* @param int16_t - The skill index in which will be asked for its cooldown
		* @return bool - returns true if the skill IS on cooldown
		*/
		bool CheckSkillCooldown(int16_t checkedSkill);

		/**
		* @brief Check if the player has mana to use this skill
		* @param int16_t - The skill index in which will be asked for its mana cost.
		* @return bool - returns false if the player does not have enough mana to use this skill 
		*/
		bool CheckSkillMana(int16_t checkedSkill);

		/**
		* @brief Last stage to use a selected skill.
		* Use the selected skill by its index. At this point, the value is largely checked.
		* Subtract the users mana by the skill required mana.
		* @param int16_t - The skill index in which will be used.
		* @return bool - returns false if the player cannot use this skill at all.
		*/
		bool ProcessSkills(int16_t checkedSkill);


		/**
		* @brief Makes the Attacking player (player in turn) to hit the Target player. 
		* Subtract the Target players life by the Attacking players strength.
		*/
		void ProcessPlayerAttack();

		/**
		* @brief Check if the Target players life is zero, if so, the game ends and the Attacking player win.
		* the Target player will always be the hitted one, so it will be always the dead.
		*/
		void CheckDeath();

		/**
		* @brief Print start game message and explain the rules.
		*/
		void PrintStartGameMessage();

		/**
		* @brief At the end of the turn, turns Attacking player into the Target and vice-versa
		*/
		void SwapSides();

		/**
		* @brief Update the players. 
		* Players have important stuff to update, like their skills (cooldowns, durations etc)
		*/
		void Tick();

		/**
		* @brief In the end of the turn, the attacking player gain one of mana. This function adds it to it
		*/
		void IncrementPlayerInTurnMana();

	private:
		Player m_PlayerOne;
		Player m_PlayerTwo;

		/**
		* @brief Player that will attack, it swaps between the Player One and Player Two.
		*/
		Player* m_AttackingPlayer;

		/**
		* @brief Player that will be attacked, it swaps between the Player One and Player Two.
		*/
		Player* m_TargetedPlayer;

		/**
		* @brief Condition to keep the match running. It becomes false when one of the players die.
		*/
		bool m_IsMatchRunning;
	};
}