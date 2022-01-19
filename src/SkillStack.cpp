#include "AGRVPCH.h"
#include "SkillStack.h"

#include "GameSrc/Dummy.h"
#include "GameSrc/Meditacao.h"
#include "GameSrc/EspadaAfiada.h"
#include "GameSrc/Descanso.h"
#include "GameSrc/PinturaDeGuerra.h"
#include "Player.h"
#include "Skill.h" 


namespace PDG
{
	SkillStack::SkillStack(Player* owner) : m_SkillsOwner(owner)
	{
		//Those skills are permanent. The user will provide an index and we will take the Skill* from this index
		//and use those permanent objects to return a brand new object of the selected skill. 
		//This is better, more organized and cleaner than branch everytime the enum.
		//Plus, when you are adding a new skill, you just have to #include it here and add in the list below!
		m_AvaiableSkills = { new Dummy(m_SkillsOwner), new Meditacao(m_SkillsOwner), new EspadaAfiada(m_SkillsOwner),
							 new Descanso(m_SkillsOwner), new PinturaDeGuerra(m_SkillsOwner) };

		m_SkillCooldown.resize(m_AvaiableSkills.size(), 0);
	}

	SkillStack::~SkillStack()
	{
		for (Skill* permanentSkill : m_AvaiableSkills)
			delete permanentSkill;
		

		for (Skill* activeSkill : m_ActiveSkills)
		{
			if (activeSkill) 
				delete activeSkill;;
		}
	}

	bool SkillStack::UseSkill(int16_t desiredSkill)
	{
		Skill* skill = nullptr;

		if (m_AvaiableSkills[desiredSkill]->SkillCondition())
			skill = m_AvaiableSkills[desiredSkill]->GetSkill();

		//Probably, we don't met the skill conditions
		if (!skill)
			return false;

		m_SkillCooldown[desiredSkill] = skill->GetBaseCooldown();
		m_ActiveSkills.push_back(skill);
		skill->OnSkillUse();

		return true;
	}
	void SkillStack::Tick()
	{
		for (int x = 0; x < m_ActiveSkills.size(); x++)
		{	
			m_ActiveSkills[x]->Tick();
			
			//If the skill was used, it is not active anymore, this is, the effect is not applied.
			//so we can pop this skill from the active queue and keep its cooldown management on the outside.
			if (m_ActiveSkills[x]->WasSkillUsed())
			{
				PopSkill(x);
				x--;
			}
		}

		//If theres is a cooldown, decrement it.
		for (int x = 1; x < m_AvaiableSkills.size(); x++)
			if(m_SkillCooldown[x])
				m_SkillCooldown[x]--;
	}
	
	void SkillStack::PopSkill(int16_t index)
	{
		delete m_ActiveSkills[index];
		m_ActiveSkills.erase(m_ActiveSkills.begin() + index);
	}

	bool SkillStack::ValidateSkill(int16_t skill)
	{
		if (skill <= 0 || skill >= m_AvaiableSkills.size())
			return false;

		return true;
	}

	bool SkillStack::CheckSkillCooldown(int16_t skill)
	{
		return (m_SkillCooldown[skill] > 0);
	}

	/////////////////////////////////////////////////////////// GETTERS

	std::vector<std::string> SkillStack::GetOnEffectSkillNames()
	{
		std::vector<std::string> activeSkillNames;

		for (Skill* skill : m_ActiveSkills)
				activeSkillNames.push_back(skill->GetName());

		return activeSkillNames;
	}
	std::vector<int16_t> SkillStack::GetOnEffectSkillsDuration()
	{
		std::vector<int16_t> leftDuration;

		for (Skill* skill : m_ActiveSkills)
				leftDuration.push_back(skill->GetLeftDuration());
		

		return leftDuration;
	}
	std::vector<std::string> SkillStack::GetAvaiableSkillNames()
	{
		std::vector<std::string> AvaiableSkilNames;

		for (Skill* skill : m_AvaiableSkills)
			AvaiableSkilNames.push_back(skill->GetName());

		return AvaiableSkilNames;
	}
	
	int16_t SkillStack::GetSkillManaCost(int16_t skillIndex)
	{
		return m_AvaiableSkills[skillIndex]->GetManaCost();
	}

	/////////////////////////////////////////////////////////// GETTERS
}