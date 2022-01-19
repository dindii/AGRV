#include "AGRVPCH.h"
#include "Meditacao.h"

namespace PDG
{
	void Meditacao::ApplyEffect()
	{
		//Notas: assumimos que as skills ser�o sempre buffs em n�s mesmos, por isso tamb�m a liberdade
		//de um ponteiro const pro player. Al�m da propria liberdade criativa, claro
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