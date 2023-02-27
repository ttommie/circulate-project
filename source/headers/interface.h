#pragma once

// interfaces
#include "sdk/IBaseClientDll.h"
#include "sdk/IClientEntityList.h"

namespace interfaces
{
	// Call once to capture all interface pointers
	void Setup() noexcept;

	// Capture an individual interface by name & module
	template <typename Interface>
	Interface* GetInterface(const char* moduleName, const char* interfaceName) noexcept;

	// Interface pointers
	inline IBaseClientDll* baseClient = nullptr;
	inline IClientEntityList* entityList = nullptr;
	//inline IVModelInfo* modelInfo = nullptr;
	//inline IInputSystem* inputSystem = nullptr;

}