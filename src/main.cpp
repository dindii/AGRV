#include "AGRVPCH.h"
#include "GameManager.h"
#include <locale.h>


int main()
{
	setlocale(LC_ALL, "Portuguese");

	PDG::GameManager game;
	game.StartGame();
}

