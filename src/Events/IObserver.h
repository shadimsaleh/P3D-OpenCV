#pragma once

template <typename T>
struct IObserver
{
	virtual void OnNotify(T t) = 0;
};