#include "Game.h"

int main()
{
	printf("Hello world!\nWhat noise generator would you like to use(1-6)?\n");


	int result = 0;
	do
	{
		restart = false;
		result = Run();
	} while (restart);

	printf("Goodbye!\n");
	return result;
}