#pragma once
#include <vector>
#include <algorithm>
#include <Events\IObserver.h>

template <typename T>
class Subject
{
public:
	void Attach(IObserver<T>* observer);
	void Detach(IObserver<T>* observer);
	void Notify(T arg);

	Subject& operator+=(IObserver<T>& observer) {
		observers.push_back(&observer);
		return *this;
	}

private:
	std::vector<IObserver<T>*> observers;
};

template<typename T>
inline void Subject<T>::Notify(T arg)
{
	for (size_t i = 0; i < observers.size(); i++)
	{
		observers[i]->OnNotify(arg);
	}
}

template<typename T>
inline void Subject<T>::Attach(IObserver<T>* observer)
{
	observers.push_back(observer);
}

template<typename T>
inline void Subject<T>::Detach(IObserver<T>* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
