#pragma once
#include <exception>


template<class TKey>
class NotFoundException : public std::exception
{
public:
virtual const TKey & GetKey() const noexcept = 0;
};