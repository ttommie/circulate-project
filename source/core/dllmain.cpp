#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <thread>
#include <cstdint>
#include "../headers/hooks.h"

// Setup Function
void Setup(const HMODULE instance)
{
	FILE* file;
	try
	{
		mem::Setup();
		interfaces::Setup();
		netvars::Setup();
		gui::Setup();
		hooks::Setup();

		AllocConsole();
		freopen_s(&file, "CONOUT$", "w", stdout);
	}
	catch (const std::exception& error)
	{
		MessageBeep(MB_ICONERROR);
		MessageBox(
			0,
			error.what(),
			"Calculate Error",
			MB_OK | MB_ICONEXCLAMATION
		);

		goto UNLOAD;
	}

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	if (file)
		fclose(file);

	FreeConsole();

UNLOAD:
	hooks::Destroy();
	gui::DestoryMenu();
	FreeLibraryAndExitThread(instance, 0);	
}

// Entry Point
BOOL WINAPI DllMain(
	const HMODULE instance,
	const std::uintptr_t reason,
	const void* reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const auto thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup),
			instance,
			0,
			nullptr
		);

		if (thread)
			CloseHandle(thread);
	}

	return TRUE;
}