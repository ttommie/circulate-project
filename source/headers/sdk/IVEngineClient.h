#pragma once

#include "../utility/mem.h"

class IVEngineClient
{
public:
	constexpr std::int32_t GetLocalPlayerIndex() noexcept
	{
		return mem::Call<std::int32_t>(this, 12);
	}

	constexpr bool IsInGame() noexcept
	{
		return mem::Call<bool>(this, 26);
	}
};