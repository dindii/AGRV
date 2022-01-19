#pragma once
#include "Skill.h"

namespace PDG
{
#define MEDITACAO_MANA_COST 0
#define MEDITACAO_COOLDOWN 0
#define MEDITACAO_TURNS_TO_ACTIVE 1
#define MEDITACAO_DURATION 0

	class Meditacao : public Skill
	{
	public:
		Meditacao(Player* owner) : Skill(owner, MEDITACAO_MANA_COST, MEDITACAO_COOLDOWN, MEDITACAO_TURNS_TO_ACTIVE, MEDITACAO_DURATION) {};

		virtual void ApplyEffect()  override;
		virtual void UnaplyEffect() override;

		virtual bool SkillCondition() override;

		virtual std::string GetName() override { return "Meditação"; }

		virtual Skill* GetSkill() override { return new Meditacao(m_SkillOwner); }
	};
}