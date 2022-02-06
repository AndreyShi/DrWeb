#pragma once
#include "NotFoundException.h"
template <class TKey>
//final означает что от этого класса нельзя наследоваться
class KeyNotFoundException final : public NotFoundException<TKey>
{
public:
	//explicit невозможно неявное конструирование
	//KeyNotFoundException a = b - невозможно при explicit
	explicit KeyNotFoundException(const TKey& key)
		: key(key)
	{
		std::cout << "ctor";
	}
	//override показывает переопределена функция или нет
	const TKey& GetKey() const noexcept override
	{
		return key;
	}

	const char* what() const noexcept override
	{
		return "unknow key";
	}

private:
	TKey key;
};