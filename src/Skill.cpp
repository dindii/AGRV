#include "AGRVPCH.h"
#include "Skill.h"

namespace PDG
{
	Skill::Skill(Player* owner, int16_t manaCost, int16_t cooldown, int16_t turnsToActivate, int16_t duration) :
				m_ManaCost(manaCost), m_Cooldown(cooldown), m_TurnsToActivate(turnsToActivate), m_Duration(duration),
				m_EffectApplied(false), m_SkillOwner(owner)
	{
		m_TurnsToActivateCount = m_TurnsToActivate;
		m_DurationCount = m_Duration;
	}

	void Skill::OnSkillExpire()
	{
		//Calls child UnaplyEffect() so it can have custom behaviour
		UnaplyEffect();

		//The effect is no longer active but we used this skill.
		m_EffectApplied = false;
		m_WasSkillUsed = true;
	}

	void Skill::UseSkill()
	{
		ApplyEffect();
		m_EffectApplied = true;

		//If theres no duration count (even if we just used the skill) it means it is an active skill
		//like a health or mana restoration skill (skills that doesn't will have its effect revoked)
		//so we can start its process to remove it from the list of active skills.
		if (!m_DurationCount)
			OnSkillExpire();
	}
	void Skill::OnSkillUse()
	{
		//Usually, the end of its own round, counts as one passed round. So, if it has no turns to be active, just use it already.
		if (m_TurnsToActivateCount >= 1)
		{
			m_TurnsToActivateCount--;
		}
		else
		{
			UseSkill();
		}
	}

	void Skill::Tick()
	{
		//It is waiting to be active? If so, decrement and returns after decrement cooldown
		if (m_TurnsToActivateCount)
		{
			m_TurnsToActivateCount--;
		}
		else
		{
			//If it is ready to be used, have we used it before? If so, just decrement the Duration
			if (m_EffectApplied)
			{
				if (m_DurationCount)
				{
					m_DurationCount--;
				}
				//When the duration is over, the skill is no longer active and we can start the process to inactivate it.
				else
				{
					OnSkillExpire();
				}		
			}
			//If it is ready to be used for the first time, then use.
			else
			{
				UseSkill();
			}
		}
	}

}