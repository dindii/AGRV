#include "AGRVPCH.h"
#include "Meditacao.h"

namespace PDG
{
	void Meditacao::ApplyEffect()
	{
		//Notas: assumimos que as skills serão sempre buffs em nós mesmos, por isso também a liberdade
		//de um ponteiro const pro player. Além da propria liberdade criativa, claro
		m_SkillOwner->SetMana((m_SkillOwner->GetMana() + 2));
	}
	void Meditacao::UnaplyEffect()
	{

	}
	bool Meditacao::SkillCondition()
	{
		return true;
	}
}