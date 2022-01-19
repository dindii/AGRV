#include "AGRVPCH.h"
#include "Player.h"
#include "SkillStack.h"


namespace PDG
{
	Player::Player() : m_CharactersName("Default")
	{
		m_Skills = new SkillStack(this);
	}
	Player::~Player()
	{
		delete m_Skills;
	}
	void Player::Tick()
	{
		//Updates skills cooldown, duration etc
		m_Skills->Tick();
	}
	void Player::SetHealth(int newHealth)
	{
		//Set health and clamp it to never get below zero
		m_Stats.Health = clampMin<int>(0, newHealth);
	}

	void Player::SetMana(int newMana)
	{
		//Set mana and clamp it to never get below zero
		m_Stats.Mana = clampMin<int>(0, newMana);
	}

	void Player::SetStrength(int newStrength)
	{
		//Set strength and clamp it to never get below zero
		m_Stats.Strength = clampMin<int>(0, newStrength);
	}
}