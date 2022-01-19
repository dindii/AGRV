#pragma once
#include "Skill.h"

namespace PDG
{
#define ESPADA_AFIADA_MANA_COST 4
#define ESPADA_AFIADA_COOLDOWN 3
#define ESPADA_AFIADA_TURNS_TO_ACTIVE 0
#define ESPADA_AFIADA_DURATION 2

	class EspadaAfiada : public Skill
	{
	public:
		EspadaAfiada(Player* owner) : Skill(owner, ESPADA_AFIADA_MANA_COST, ESPADA_AFIADA_COOLDOWN, ESPADA_AFIADA_TURNS_TO_ACTIVE,
			ESPADA_AFIADA_DURATION) {};

		virtual void ApplyEffect()  override;
		virtual void UnaplyEffect() override;
		virtual bool SkillCondition() override;

		virtual std::string GetName() override { return "Espada Afiada"; }
		
		virtual Skill* GetSkill() override { return new EspadaAfiada(m_SkillOwner); }
	private:
		int16_t m_OldPlayerStrength = 0;
	};
}