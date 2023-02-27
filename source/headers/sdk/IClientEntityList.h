#pragma once
#include "CEntity.h"

class IClientEntityList
{
public:
	constexpr CEntity* GetEntityFromIndex(const std::int32_t index) noexcept
	{
		return mem::Call<CEntity*>(this, 3, index);
	}

	inline CEntity* GetClientEntityFromHandle(unsigned long Handle) {
		return mem::Call<CEntity*>(this, 4, Handle);
	}
};
