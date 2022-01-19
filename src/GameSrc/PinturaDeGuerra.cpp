#include "AGRVPCH.h"
#include "PinturaDeGuerra.h"

namespace PDG
{
	void PinturaDeGuerra::ApplyEffect()
	{
		//Notas: assumimos que as skills ser�o sempre buffs em n�s mesmos, por isso tamb�m a liberdade
		//de um ponteiro const pro player. Al�m da propria liberdade criativa, claro
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