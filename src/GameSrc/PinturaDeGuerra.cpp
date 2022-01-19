#include "AGRVPCH.h"
#include "PinturaDeGuerra.h"

namespace PDG
{
	void PinturaDeGuerra::ApplyEffect()
	{
		//Notas: assumimos que as skills serão sempre buffs em nós mesmos, por isso também a liberdade
		//de um ponteiro const pro player. Além da propria liberdade criativa, claro
		m_SkillOwner->SetStrength((m_SkillOwner->GetStrength() + 2));
	}
	void PinturaDeGuerra::UnaplyEffect()
	{
		m_SkillOwner->SetStrength((m_SkillOwner->GetStrength() - 2));
	}
	bool PinturaDeGuerra::SkillCondition()
	{
		return true;
	}
}