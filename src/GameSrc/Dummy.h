#pragma once
#include "Skill.h"

namespace PDG
{
#define MEDITACAO_MANA_COST 0
#define MEDITACAO_COOLDOWN 0
#define MEDITACAO_TURNS_TO_ACTIVE 0
#define MEDITACAO_DURATION 0


	//Dummy is a skill that does nothing. This is because index ZERO is reserved to back action
	//the back action will always be triggered first by the GameManager
	//as well as the validate function of SkillStack will never
	//process the value zero (giving an out of range error).
	//So, having dummy is important because we can start skills by value 1 and have to change it in only one place
	//making it less error prone than putting a +1 in every for loop.
	class Dummy : public Skill
	{
	public:
		Dummy(Player* owner) : Skill(owner, MEDITACAO_MANA_COST, MEDITACAO_COOLDOWN, MEDITACAO_TURNS_TO_ACTIVE, MEDITACAO_DURATION) {};

		virtual void ApplyEffect()  override;
		virtual void UnaplyEffect() override;

		virtual bool SkillCondition() override;

		virtual std::string GetName() override { return "Dummy"; }

		virtual Skill* GetSkill() override { return new Dummy(m_SkillOwner); }
	};
}