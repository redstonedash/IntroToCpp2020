#include <iostream>
int main()
{
	char arr[1] = {0};
	for (int i = 0; i < 1053; i++)
	{
		std::cout << +arr[i];
	}
	for (int i = 0; i < 1053; i++)
	{
		arr[i] = 'a';
	}
	for (int i = 0; i < 1053; i++)
	{
		std::cout << arr[i];
	}
	return 0;
}