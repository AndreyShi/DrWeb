
/*Андрей, по нашей предварительной договоренности 
высылаю Вам тестовое задание.

Необходимореализовать класс контейнера, 
реализующий интерфейс Dictionary и 
способныйвыбросить исключение,
реализующее интерфейс NotFoundException.
Приразработке допускается использовать STL.
Кроме этого, внутренняя реализацияничем не ограничена.
template<classTKey, class TValue>
classDictionary
{
public:
virtual ~Dictionary() = default;

virtual const TValue& Get(const TKey& key) const = 0;
virtual void Set(const TKey& key, const TValue& value) = 0;
virtual bool IsSet(const TKey& key) const = 0;
};

template<classTKey>
classNotFoundException : public std::exception
{
public:
virtual const TKey& GetKey() const noexcept = 0;
};*/

#pragma once
template<class TKey, class TValue>
class Dictionary{
public:
virtual ~Dictionary() = default;

virtual const TValue& Get(const TKey & key) const = 0;
virtual void Set(const TKey & key, const TValue & value) = 0;
virtual bool IsSet(const TKey & key) const = 0;
};