#pragma once
#include "Pool.h"

struct ISystem
{
	friend class Pool;

	virtual void OnInitialize(Pool& pool) = 0;
	virtual void OnExecute() = 0;
	virtual void OnDispose() = 0;
};