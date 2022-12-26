#include<memory>
#include"Core/App.h"

int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>("Blaze", 1000, 600);
	app->Run();

	return EXIT_SUCCESS;
}