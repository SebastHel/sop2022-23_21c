#include <iostream>

int main()
{
	int wysokosc;
	std::cout << "Wprowadz Wysokosc" << std::endl;
	std::cin >> wysokosc;

	for (int i = 0; i < wysokosc; i++) {

		for (int j = 0; j < wysokosc - i; j++) {
			std::cout << " ";
		}
		for (int j = 0; j < 2 * i - 1; j++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	return 0;

}
