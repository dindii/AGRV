#pragma once
#include "Skill.h"

namespace PDG
{
#define PINTURA_DE_GUERRA_MANA_COST 1
#define PINTURA_DE_GUERRA_COOLDOWN 2
#define PINTURA_DE_GUERRA_TURNS_TO_ACTIVE 0
#define PINTURA_DE_GUERRA_DURATION 3

	class PinturaDeGuerra : public Skill
	{
	public:
		PinturaDeGuerra(Player* owner) : Skill(owner, PINTURA_DE_GUERRA_MANA_COST, PINTURA_DE_GUERRA_COOLDOWN,
			PINTURA_DE_GUERRA_TURNS_TO_ACTIVE, PINTURA_DE_GUERRA_DURATION) {};

		virtual void ApplyEffect()  override;
		virtual void UnaplyEffect() override;

		virtual bool SkillCondition() override;

		virtual Skill* GetSkill() override { return new PinturaDeGuerra(m_SkillOwner); }

		virtual std::string GetName() override { return "Pintura De Guerra"; }
	};
}