#pragma once

#include "../utility/mem.h"
#include "CClientClass.h"

enum ClientFrameStage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,

	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,

	FRAME_RENDER_START,
	FRAME_RENDER_END,

	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE
};

class IBaseClientDll
{
public:
	constexpr CClientClass* GetAllClasses() noexcept
	{
		return mem::Call<CClientClass*>(this, 8);
	}
};