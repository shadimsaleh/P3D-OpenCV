#include "LayoutMapper.h"

TypeId LayoutMapper::counter = 0;
std::map<TypeId, BufferLayoutPtr> LayoutMapper::map;