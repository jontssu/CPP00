#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public virtual ClapTrap {
	private:

	public:
	void highFivesGuys(void);

	FragTrap();
	FragTrap(std::string name);
	~FragTrap();
};

#endif