#pragma once
#include "Skill.h"

namespace PDG
{
#define DESCANSO_MANA_COST 1
#define DESCANSO_COOLDOWN 4
#define DESCANSO_TURNS_TO_ACTIVE 0
#define DESCANSO_DURATION 0

	class Descanso : public Skill
	{
	public:
		Descanso(Player* owner) : Skill(owner, DESCANSO_MANA_COST, DESCANSO_COOLDOWN, DESCANSO_TURNS_TO_ACTIVE,
			DESCANSO_DURATION) {};

		virtual void ApplyEffect()  override;
		virtual void UnaplyEffect() override;
		virtual bool SkillCondition() override;

		virtual Skill* GetSkill() override { return new Descanso(m_SkillOwner); }

		virtual std::string GetName() override { return "Descanso"; }
	};
}