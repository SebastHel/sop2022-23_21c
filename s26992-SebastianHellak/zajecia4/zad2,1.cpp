#include <iostream>
#include <fstream>
#include <string>

int main()
{
	string text;

	std::ifstream plik("plik.txt");


	while (getline(plik, text)) {
		std::cout << text;

	plik.close();
}
