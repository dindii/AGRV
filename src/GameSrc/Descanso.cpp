#include "AGRVPCH.h"
#include "Descanso.h"

namespace PDG
{
	void Descanso::ApplyEffect()
	{
		//Notas: assumimos que as skills serão sempre buffs em nós mesmos, por isso também a liberdade
		//de um ponteiro const pro player. Além da propria liberdade criativa, claro
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