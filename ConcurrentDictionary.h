#pragma once
#include <cstddef>
#include <exception>
#include <shared_mutex>
#include <unordered_map>
#include "Dictionary.h"

template <class TKey, class TValue>
class MyDictionary final : public Dictionary<TKey, TValue>
{
public:
	MyDictionary() = default;
	MyDictionary(const MyDictionary&) = delete;
	MyDictionary(MyDictionary&&) = delete;
	MyDictionary& operator=(const MyDictionary&) = delete;
	MyDictionary& operator=(MyDictionary&&) = delete;
	~MyDictionary() override = default;

	const TValue& Get(const TKey& key) const override;
	void Set(const TKey& key, const TValue& value) override;
	bool IsSet(const TKey& key) const override;
	std::size_t Size() const noexcept;
private:
	//unordered_map ,быстрее поиск/удаление /вставка по нему O(1) в map log(n)
	std::unordered_map<TKey, TValue> _data;

	//Начиная с C++17, std::shared_mutex формирует доступ двух типов :
	//Общий доступ : потоки вместе могут владеть мьютексом и иметь доступ
	//к одному и тому же ресурсу.Доступ такого типа можно запросить с помощью std::shared_lock(lock guard для общего мьютекса).
	//При таком доступе любой эксклюзивный доступ блокируется.
	//Эксклюзивный доступ : доступ к ресурсу есть только у одного потока.
	//Запрос этого типа осуществляется с помощью класса unique lock.
	mutable std::shared_mutex _mtx;
};

template<class TKey, class TValue>
inline const TValue& MyDictionary<TKey, TValue>::Get(const TKey& key) const
{
	//Общий доступ : читать могут несколько потоков ,но доступ на запись запрещена
	std::shared_lock < std::shared_mutex > lck(_mtx);
	const auto search = _data.find(key);
	if (search == std::end(_data))
	{
		throw KeyNotFoundException<TKey>(key);
	}
	return search->second;
}

template<class TKey, class TValue>
inline void MyDictionary<TKey, TValue>::Set(const TKey& key, const TValue& value)
{
	//Эксклюзивный доступ :читать никто не может,но запись только для одного потока
	std::unique_lock < std::shared_mutex > lck(_mtx);
	const auto search = _data.find(key);
	const auto search1 = std::end(_data);
	if (search == search1)
	{
		_data.emplace(key, value);
	}
	else
	{
		search->second = value;
	}
}

template<class TKey, class TValue>
inline bool MyDictionary<TKey, TValue>::IsSet(const TKey& key) const
{
	//Общий доступ : читать могут несколько потоков ,но доступ на запись запрещена
	std::shared_lock < std::shared_mutex > lck(_mtx);
	const auto search = _data.find(key);
	return search != std::end(_data);
}

template<class TKey, class TValue>
inline std::size_t MyDictionary<TKey, TValue>::Size() const noexcept
{
	//Общий доступ : читать могут несколько потоков ,но доступ на запись запрещена
	std::shared_lock < std::shared_mutex > lck(_mtx);
	return std::size(_data);
}
