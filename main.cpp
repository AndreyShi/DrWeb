#include <iostream>
#include <string>

#include "KeyNotFoundException.h"
#include "ConcurrentDictionary.h"


int main()
{
	try
	{
		MyDictionary<int, std::string> dict;
		dict.Set(0, "value 0");
		dict.Set(1, "2");
		dict.Set(2, "2");
		dict.Set(2, "3");
		std::cout << std::boolalpha << dict.IsSet(0) << ' ' << dict.Get(4) << '\n';
		std::cout << std::boolalpha << dict.IsSet(1) << ' ' << dict.Get(1) << '\n';
		std::cout << std::boolalpha << dict.IsSet(2) << ' ' << dict.Get(2) << '\n';
	}
	catch (const KeyNotFoundException<int>& ex)
	{
		std::cerr << ex.what() << '\n';
		std::cerr << ex.GetKey() << '\n';
	}
}