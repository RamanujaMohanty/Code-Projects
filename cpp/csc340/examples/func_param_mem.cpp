#include <iostream>
#include <string>

std::string sing(std::string missing, std::string writer = "Richard & Robert Sherman")
{
	if (missing.empty())
	{
		exit(1);
	}
	std::cout << "It's a " << missing << " world after all..." << std::endl;
	return writer;
}

void sing(string, int);
}
