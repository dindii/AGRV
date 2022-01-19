#include "AGRVPCH.h"
#include "GameManager.h"
#include "Core.h"

namespace PDG
{
	GameManager::GameManager() : m_IsMatchRunning(true)
	{
		m_PlayerOne.SetCharactersName("Jogador 1");
		m_PlayerTwo.SetCharactersName("Jogador 2");

		m_AttackingPlayer = &m_PlayerOne;
		m_TargetedPlayer =  &m_PlayerTwo;
	}


	////////////////////////////////////////////////////////////////////////////////// CORE

	void GameManager::Tick()
	{
		m_AttackingPlayer->Tick();
	}

	void GameManager::StartGame()
	{
		PrintStartGameMessage();

		while (m_IsMatchRunning)
		{
			//Update the player as well as its skills (on its own)
			Tick();

			ClearConsole();

			PrintPlayerStatus(m_PlayerOne);
			PrintPlayerActiveSkills(m_PlayerOne);

			PrintPlayerStatus(m_PlayerTwo);
			PrintPlayerActiveSkills(m_PlayerTwo);

			//Show, Get, Validate (looks for bad input) and process actions. Skill usage is also an action.
			EActions chosenAction;
			do { chosenAction = GetActions(); }
			while(!ProcessActions(chosenAction));

			IncrementPlayerInTurnMana();

			CheckDeath();


			SwapSides();
		}

	}
////////////////////////////////////////////////////////////////////////////////// CORE


////////////////////////////////////////////////////////////////////////////////// ACTIONS
	void GameManager::ShowActions()
	{
		std::cout << std::endl;

		std::cout << m_AttackingPlayer->GetName() << ", qual será a sua ação?\n"
			<< "Ações disponíveis: \n" << EActions::BackAction << " - Pular turno \n" << EActions::BasicAttack << " - Ataque Básico\n"
			<< EActions::Skill << " - Habilidades\n"
			<< "Ação: ";
	}
	const EActions GameManager::GetActions()
	{
		EActions action;
		int16_t aux = 0;

		//we only leave here when a good input is given
		do
		{
			ShowActions();
			std::cin >> aux;
			action = static_cast<EActions>(aux);
		} while (!ValidateActions(action));

		return action;
	}

	bool GameManager::ValidateActions(const EActions action)
	{
		EActions checkedAction = action;

		if (checkedAction <= EActions::MinimumNone || checkedAction >= EActions::MaximumNone)
		{
			std::cout << "Ação invalida, por favor tente novamente: " << std::endl;
			return false;
		}

		return true;
	}

	bool GameManager::ProcessActions(const EActions action)
	{
		switch (action)
		{
			case EActions::BackAction:
			{
				return true;
			}break;

			case EActions::BasicAttack:
			{
				ProcessPlayerAttack();
				return true;
			}break;

			case EActions::Skill:
			{
				//Checks if the input skill is valid (if it exists)
				//then check if the user has mana, if the skill is in cooldown
				//and, by last, check if the skill conditions are met
				//until a good input, stuck us here.
				int16_t chosenSkill = -1;
				do 
				{ 
					chosenSkill = GetSkills(); //show skills and gather input
					if (chosenSkill == EActions::BackAction) //if the user change its mind and wants to land an attack, he can back to the action menu.
						return false;
				}
				while(!ProcessSkills(chosenSkill)); //but lets keep to search for valid skill inputs

				return true;
			}break;

			default:
			{
				//we never get to here
				std::cerr << "Ação Invalida!" << std::endl;
				return false;
			}
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////// ACTIONS


	////////////////////////////////////////////////////////////////////////////////// SKILLS
	void GameManager::ShowPlayerSkills()
	{
		std::cout << "\nPressione 0 para voltar ao menu de ações.\n" << std::endl;

		std::cout << "Skills disponíveis: \n";

		std::vector<std::string> SkillNames = m_AttackingPlayer->GetPlayerSkills()->GetAvaiableSkillNames();

		for (int x = 1; x < SkillNames.size(); x++)
			std::cout << x << " - " << SkillNames[x] << "\n";
		
		std::cout << "Ação: ";
	}

	int16_t GameManager::GetSkills()
	{
		int16_t chosenSkill = -1;

		//we only leave here when a good input is given
		do
		{
			ShowPlayerSkills();
			std::cin >> chosenSkill;

			if (chosenSkill == EActions::BackAction) return EActions::BackAction;

		} while (!ValidateSkills(chosenSkill));

		return chosenSkill;
	}

	bool GameManager::ValidateSkills(int16_t chosenSkill)
	{
		int16_t checkedSkill = chosenSkill;

		//The given skill do even exist?
		if (!m_AttackingPlayer->GetPlayerSkills()->ValidateSkill(checkedSkill))
		{
			std::cout << "Habilidade invalida, por favor, tente novamente: " << std::endl;
			return false;
		}

		return true;
	}

	bool GameManager::ProcessSkills(int16_t checkedSkill)
	{
		if (!CheckSkillMana(checkedSkill))
		{
			std::cout << "Você não tem mana para usar esta habilidade, por favor, tente novamente." << std::endl;
			return false;
		}

		if (CheckSkillCooldown(checkedSkill))
		{
			std::cout << "Esta habilidade está em cooldown, por favor, tente novamente." << std::endl;
			return false;
		}

		//If everything is ok, this is, if the skill is a valid skill, the player does have mana and the skill is not on cooldown, we need to check
		//if the player has the conditions the selected skill wants. 
		//The only possibility of UseSkill returns false are if the conditions are not met. We always feed an already checked value to it.
		if (!m_AttackingPlayer->GetPlayerSkills()->UseSkill(checkedSkill))
		{
			std::cout << "Esta habilidade não pode ser usada, por favor, cheque as condições de uso." << std::endl;
			return false;
		}

		//decrement players mana
		int16_t skillManaCost = m_AttackingPlayer->GetPlayerSkills()->GetSkillManaCost(checkedSkill);
		m_AttackingPlayer->SetMana(m_AttackingPlayer->GetMana() - skillManaCost);

		return true;
	}



	bool GameManager::CheckSkillCooldown(int16_t checkedSkill)
	{
		auto PlayerSkills = m_AttackingPlayer->GetPlayerSkills();
		return PlayerSkills->CheckSkillCooldown(checkedSkill);
	}

	bool GameManager::CheckSkillMana(int16_t checkedSkill)
	{
		auto PlayerSkills = m_AttackingPlayer->GetPlayerSkills();
		int16_t skillManaCost = PlayerSkills->GetSkillManaCost(checkedSkill);

		return (m_AttackingPlayer->GetMana() >= skillManaCost);
	}

	////////////////////////////////////////////////////////////////////////////////// SKILLS

	////////////////////////////////////////////////////////////////////////////////// GAMEPLAY MECHANIC

	void GameManager::ProcessPlayerAttack()
	{
		//The main mechanic. Subtract players life by the attacking strength.
		int16_t damage = m_AttackingPlayer->GetStrength();
		int16_t targetActualLife = m_TargetedPlayer->GetHealth();

		m_TargetedPlayer->SetHealth(targetActualLife - damage);
	}

	void GameManager::CheckDeath()
	{
		if (!m_TargetedPlayer->GetHealth())
		{
			std::cout << m_AttackingPlayer->GetName() << " Venceu a partida!" << std::endl;
			m_IsMatchRunning = false;

			std::cout << "Aperte qualquer tecla para sair." << std::endl;
			std::cin.get();
		}
	}

	void GameManager::SwapSides()
	{
		//turns the attacking player into the targeted and vice versa
		Player* aux = m_AttackingPlayer;
		m_AttackingPlayer = m_TargetedPlayer;
		m_TargetedPlayer = aux;
	}

	//at the end of every round, the attacking player gains +1 mana
	void GameManager::IncrementPlayerInTurnMana()
	{
		m_AttackingPlayer->SetMana(m_AttackingPlayer->GetMana() + 1);
	}

	////////////////////////////////////////////////////////////////////////////////// GAMEPLAY MECHANIC


	////////////////////////////////////////////////////////////////////////////////// PRINT
	void GameManager::PrintPlayerStatus(const Player & player) const
	{
		std::cout << std::endl;

		std::cout << player.GetName() << " tem: "
			<< "\nVida  - " << player.GetHealth()
			<< "\nMana  - " << player.GetMana()
			<< "\nForca - " << player.GetStrength() << std::endl;
	}

	void GameManager::PrintPlayerActiveSkills(Player & player)
	{
		std::cout << std::endl;

		std::vector<std::string> activeSkillsName = player.GetPlayerSkills()->GetOnEffectSkillNames();
		std::vector<int16_t> activeSkillsDuration = player.GetPlayerSkills()->GetOnEffectSkillsDuration();



		std::cout << "Skills ativas: \n";

		for (int16_t i = 0; i < activeSkillsDuration.size(); i++)
		{
			if (activeSkillsDuration[i] > 0)
			{
				std::cout << activeSkillsName[i] << " (" << activeSkillsDuration[i] <<
					(activeSkillsDuration[i] > 1 ? " Turnos restantes de duração)\n" : " Turno restante de duração)\n");
			}
			else
			{
				std::cout << activeSkillsName[i] << " (" << "ultimo turno de duração)\n";
			}
		}

		std::cout << std::endl;
	}

	void GameManager::PrintStartGameMessage()
	{
		std::cout << "A partida se inicia! O jogador o qual a vida chegar a zero primeiro, perde!" << std::endl;
	}

	////////////////////////////////////////////////////////////////////////////////// PRINT
}