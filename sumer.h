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

#ifndef _SUMER_H_
#define _SUMER_H_

class Hamurabi {
	private:
		// Internal game variables
		int year = 1;		// Year counter
		int plague = 0;		// Plague chance
		int starved = 0;	// People who died due to starvation
		int population = 100;	// City population
		int immigrants = 5;	// Number of immigrants to the city
		int harvest = 0;	// Number of harvested bushels for a year
		int harvest_ratio = 3;	// Bushel per acre harvest ratio
		int eaten = 0;		// Number of bushels eaten by rats
		int storage = 2800;	// Number of bushels in storage
		int acres =3000;		// Number of owned acres
		int land_price = 0;	// Land price (bushels per acre)
		int bought_acres = 0;	// Number of bought acres
		int sold_acres = 0;	// Number of sold acres
		int fed_bushels = 0;	// Number of fed bushels
		int acres_planted = 0;	// Number of planted acres
		int hfactor = 0;	// Harvest factor
		int people_fed = 0;	// Number of fed people.
		int total_deaths = 0;	// Number of deaths during the entire game session.
		int acres_per_person = 0;	// Acres per person
		double starved_avg = 0.0;	// Average percentage of starved people

		void YearStart(void) {
			std::cout << "Hamurabi: I beg to report to you,\n";
			std::cout << "In year " << year << ", " << starved << " people starved, " << immigrants << " came to the city.\n";
			population += immigrants;
		}

		void CityInfo(void) {
			std::cout << "Population is now " << population << ".\n";
			std::cout << "The city now owns " << acres << " acres.\n";
			std::cout << "You harvested " << harvest_ratio << " bushels per acre.\n";
			std::cout << "Rats ate " << eaten << " bushels.\n";
			std::cout << "You now have " << storage << " bushels in storage.\n";
		}

		void BuyLand(void) {
			land_price = (std::rand() % 10) + 17;
			std::cout << "Land is trading at " << land_price << " bushels per acre.\n";
			while (true) {
				std::cout << "How many acres do you wish to buy? ";
				std::cin >> bought_acres;

				if (bought_acres < 0) {
					CannotDoWish();
					continue;
				}

				if (bought_acres == 0)
					break;

				if (bought_acres * land_price <= storage) {
					acres += bought_acres;
					storage -= bought_acres * land_price;
					break;
				} else
					ThinkAgainBushels();
			}
		}

		void SellLand(void) {
			while (true) {
				std::cout << "How many acres do you want to sell? ";
				std::cin >> sold_acres;

				if (sold_acres < 0) {
					CannotDoWish();
					continue;
				}

				if (sold_acres <= acres) {
					acres -= sold_acres;
					storage += sold_acres * land_price;
					break;
				} else
					ThinkAgainAcres();
			}
		}

		void FeedPeople(void) {
			while (true) {
				std::cout << "How many bushels do you wish to feed your people? ";
				std::cin >> fed_bushels;

				if (fed_bushels < 0) {
					CannotDoWish();
					continue;
				}

				if (fed_bushels <= storage) {
					storage -= fed_bushels;
					break;
				} else
					ThinkAgainBushels();
			}
		}

		void PlantAcres(void) {
			while (true) {
				std::cout << "How many acres do you wish to plant with seed? ";
				std::cin >> acres_planted;

				if (acres_planted < 0) {
					CannotDoWish();
					continue;
				}

				if (acres_planted == 0)
					break;

				if (acres_planted > acres) {
					ThinkAgainAcres();
					continue;
				}

				if ((acres_planted / 2) > storage) {
					ThinkAgainBushels();
					continue;
				}

				if (acres_planted > population * 10) {
					std::cout << "But you have only " << population << " people to tend the fields!\n";
					continue;
				}

				storage -= acres_planted / 2;
				break;
			}
		}

		void PrepareNextYear(void) {
			hfactor = (std::rand() % 5) + 1;
			harvest_ratio = hfactor;
			harvest = acres_planted * harvest_ratio;

			eaten = 0;
			if (harvest_ratio % 2 == 0)
				eaten = storage / hfactor;	// Rats are running wild!!

			storage = storage - eaten + harvest;
		}

		void Immigration(void) {
			immigrants = (std::rand() % 5 + 1) * (20 * acres + storage) / population / 100 + 1;
		}

		void CheckPlague(void) {
			plague = std::rand() % 100;
			if (plague < 15) {
				population = population / 2;
				std::cout << "A horrible plague struck! Half the people died.\n";
			}
		}

		void Starvation(void) {
			people_fed = fed_bushels / 20;
			if (people_fed >= population)
				starved = 0;
			else {
				starved = population - people_fed;
				population = people_fed;
				if (starved > population * 45 / 100) {
					std::cout << "You starved " << starved << " people in one year!!!\n";
					std::cout << "Due to this extreme mismanagement you have been impeached and thrown out of office.\n";
					exit(1);
				}
			}

			total_deaths += starved;
			starved_avg = ((year - 1) * starved_avg + (100.0 * starved / population)) / year;
		}

		void FinalResults(void) {
			std::cout << "\nIn your 10-year term of office, an average of " << starved_avg << "% of the population starved per year.\n";
			std::cout << "A total of " << total_deaths << " people died.\n";

			acres_per_person = acres / population;

			if (starved_avg > 33 || acres_per_person < 7)
				std::cout << "Due to poor management, you have been declared a national fink!\n";
			else if (starved_avg > 10 || acres_per_person < 9)
				std::cout << "Your heavy-handed approach smacks of Nero and Ivan IV.\n";
			else if (starved_avg > 3 || acres_per_person < 10)
				std::cout << "Your performance could have been somewhat better, but wasn't bad at all.\n";
			else
				std::cout << "A fantastic performance! Charlemagne, Disraeli, and Jefferson could not have done better!\n";
		}

		void CannotDoWish(void) {
			std::cout << "Hamurabi: I cannot do what you wish. Try again.\n";
		}

		void ThinkAgainBushels(void) {
			std::cout << "Hamurabi: Think again. You have only " << storage << " bushels of grain.\n";
		}

		void ThinkAgainAcres(void) {
			std::cout << "Hamurabi: Think again. You own only " << acres << " acres.\n";
		}

	public:
		void HamurabiLoop(void);	// Main game loop.
};

#endif // _SUMER_H_
