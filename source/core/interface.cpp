#define WIN32_LEAN_AND_MEAN

#include "../headers/interface.h"

#include <Windows.h>
#include <stdexcept>
#include <format>

void interfaces::Setup() noexcept
{
	// Get interfaces
	baseClient = GetInterface<IBaseClientDll>("client.dll", "VClient018");
	entityList = GetInterface<IClientEntityList>("client.dll", "VClientEntityList003");
	clientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<unsigned int**>(baseClient))[10] + 5);
	engine = GetInterface<IVEngineClient>("engine.dll", "VEngineClient014");
}

// Help: https://www.youtube.com/watch?v=C0wGdwnaArA
template <typename Interface>
Interface* interfaces::GetInterface(const char* moduleName, const char* interfaceName) noexcept
{
	// Get handle to module
	const HINSTANCE handle = GetModuleHandle(moduleName);

	if (!handle) return nullptr;

	const auto functionAddress = GetProcAddress(handle, "CreateInterface");

	if (!functionAddress) return nullptr;

	// Get exported "CreateInterface" function from CSGO
	using CreateInterfaceFn = Interface*(__cdecl*)(const char*, int*);
	const CreateInterfaceFn createInterface = 
		reinterpret_cast<CreateInterfaceFn>(functionAddress);

	// Return the interface pointer by calling the function
	return createInterface(interfaceName, nullptr);
}