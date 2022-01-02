#include <iostream>
#include <thread>
#include "main.h"

using namespace restinio;

int main()
{
	std::thread t1([&]()
		{
			multiple_app_instances(8080);
		});
	std::thread t2([&]()
		{
			multiple_app_instances(8081);
		});
	t1.join();
	t2.join();
}
