#pragma once
#include <vector>

template <typename T>
class LimitedQueue
{
public:
	LimitedQueue(int maximum) : maximum(maximum), count(0) { }

	void Push(T value)
	{
		if (count >= maximum)
			data.erase(data.begin());

		data.push_back(value);
		count = data.size();
	}

	int Size()
	{
		return data.size();
	}

	int Count()
	{
		return count;
	}

	int Maximum()
	{
		return maximum;
	}

	T* Data()
	{
		return data.data();
	}

	T& operator[](int i)
	{
		return data[i];
	}

private:
	std::vector<T> data;
	int count;
	int maximum;
};
