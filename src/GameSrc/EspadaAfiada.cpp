#include "AGRVPCH.h"
#include "EspadaAfiada.h"

namespace PDG
{
	void EspadaAfiada::ApplyEffect()
	{
		m_OldPlayerStrength = m_SkillOwner->GetStrength();
		m_SkillOwner->SetStrength((m_SkillOwner->GetStrength() + m_OldPlayerStrength));
	}
	void EspadaAfiada::UnaplyEffect()
	{
		m_SkillOwner->SetStrength((m_SkillOwner->GetStrength() - m_OldPlayerStrength));
	}
	bool EspadaAfiada::SkillCondition()
	{
		return true;
	}
}