#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"
#include <iostream>

int main() {
	// ClapTrap x("x");
	// ScavTrap y("y");

	// x.takeDamage(30);
	// y.takeDamage(30);

	// for (int i = 0; i < 15; i++) {
	// 	std::cout << "Attack number: " << i + 1 << " ";
	// 	x.attack("Goblin");
	// }

	// std::cout << "\n\n\n";

	// for (int i = 0; i < 55; i++) {
	// 	std::cout << "Attack number: " << i + 1 << " ";
	// 	y.attack("Goblin");
	// }

	// std::cout << "\n\n\n";

	// x.beRepaired(10);
	// y.beRepaired(10);

	// y.guardGate();

	// FragTrap z("z");

	// for (int i = 0; i < 105; i++) {
	// 	std::cout << "Attack number: " << i + 1 << " ";
	// 	z.attack("Goblin");
	// }

	// std::cout << "\n\n\n";

	// z.beRepaired(10);
	// z.highFivesGuys();
	DiamondTrap d("d");

	d.whoAmI();
	d.attack("LUCAS");
	return (0);
}