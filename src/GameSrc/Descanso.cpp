#include "AGRVPCH.h"
#include "Descanso.h"

namespace PDG
{
	void Descanso::ApplyEffect()
	{
		//Notas: assumimos que as skills ser�o sempre buffs em n�s mesmos, por isso tamb�m a liberdade
		//de um ponteiro const pro player. Al�m da propria liberdade criativa, claro
		int16_t userStrength = m_SkillOwner->GetStrength();
		int16_t userHealth = m_SkillOwner->GetHealth();

		m_SkillOwner->SetStrength(userStrength - 2);
		m_SkillOwner->SetHealth(userHealth + 4);
		
	}
	void Descanso::UnaplyEffect()
	{

	}
	bool Descanso::SkillCondition()
	{
		int16_t userStrength = m_SkillOwner->GetStrength();
		return (userStrength >= 2);
	}
}