#include <iostream>
#include <fstream>
#include <string>

int main()
{
	char text;
	char lista[1024];
	int i = 0;
	std::ifstream plik("plik.txt");

	while (getline(plik, text)) {
		i += 1;
		lista[i] = text;
	}
	for (int g = 0; g <= sizeof(lista)-g; g++) {
		std::cout << lista[(sizeof(lista) - g)];
	}

	plik.close();
}
