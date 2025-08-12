/*
 * HamurabiCPP - A modern C++ rewrite of the original text-based game.
 * Copyright (c) 2025 Stefanos Stefanidis. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "sumer.h"

int
main(void)
{
	Hamurabi game;

	std::cout << "Try your hand at governing ancient Sumeria\n";
	std::cout << "for a ten-year term of office.\n\n";

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	game.HamurabiLoop();
}

void
Hamurabi::HamurabiLoop(void)
{
	while (year <= 10) {
		YearStart();
		CityInfo();
		BuyLand();
		SellLand();
		FeedPeople();
		PlantAcres();

		PrepareNextYear();	// Harvest + Rat loss
		CheckPlague();		// 15% chance to wipe half of the population
		Starvation();		// Handle deaths from lack of food
		Immigration();		// New people arrive

		year++;
	}

	FinalResults();
}
