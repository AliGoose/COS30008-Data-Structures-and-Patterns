#include <iostream>

int main()
{
	for (int i = 0; i < 256; i++)
	{
		std::cout << static_cast<unsigned char>(i);
	}
	return 0;
}