#include <stdexcept>
#include <intrin.h>

#include "features/vars.h"
#include "../../ext/minhook/minhook.h"
#include "../../ext/imgui/imgui.h"
#include "../../ext/imgui/imgui_impl_win32.h"
#include "../../ext/imgui/imgui_impl_dx9.h"

#include "../headers/hooks.h"

#include "features/skins.h"	

void hooks::Setup()
{
	// Init MinHook Lib
	if (MH_Initialize())
		throw std::runtime_error("Unable to init minhook.");

	// End Scene Hook
	if (MH_CreateHook(
		VirtualFunction(gui::device, 42),
		&EndScene,
		reinterpret_cast<void**>(&EndSceneOriginal)
	)) throw std::runtime_error("Unable to hook EndScene().");

	//
	if (MH_CreateHook(
		mem::Get(interfaces::keyValuesSystem, 1),
		&AllocKeyValuesMemory,
		reinterpret_cast<void**>(&AllocKeyValuesMemoryOriginal)
	)) throw std::runtime_error("Unable to hook AllocKeyValuesMemory().");

	// Create Move Hook
	if (MH_CreateHook(
		VirtualFunction(interfaces::clientMode, 24),
		&CreateMove,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	)) throw std::runtime_error("Unable to hook CreateMove().");

	// Frame Stage Notify Hook
	if (MH_CreateHook(
		VirtualFunction(interfaces::baseClient, 37),
		&FrameStageNotify,
		reinterpret_cast<void**>(&FrameStageNotifyOrginal)
	)) throw std::runtime_error("Unable to hook FrameStageNotify().");

	// Reset Hook
	if (MH_CreateHook(
		VirtualFunction(gui::device, 16),
		&Reset,
		reinterpret_cast<void**>(&ResetOriginal)
	)) throw std::runtime_error("Unable to hook Reset().");

	// Enable all hooks
	if (MH_EnableHook(MH_ALL_HOOKS))
		throw std::runtime_error("Unable to enable hooks.");

	gui::DestroyDirectX();
}

void hooks::Destroy() noexcept
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

void* __stdcall hooks::AllocKeyValuesMemory(const std::int32_t size) noexcept
{
	// if function is returning to speficied addresses, return nullptr to "bypass"
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress());
		address == reinterpret_cast<std::uint32_t>(mem::allocKeyValuesEngine) ||
		address == reinterpret_cast<std::uint32_t>(mem::allocKeyValuesClient))
		return nullptr;

	// return original
	return AllocKeyValuesMemoryOriginal(interfaces::keyValuesSystem, size);
}

bool __stdcall hooks::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	const bool result = CreateMoveOriginal(interfaces::clientMode, frameTime, cmd);

	if (!cmd || !cmd->commandNumber)
		return result;

	if (CreateMoveOriginal(interfaces::clientMode, frameTime, cmd))
		interfaces::engine->SetViewAngles(cmd->viewAngles);

	// get our local player here
	globals::UpdateLocalPlayer();

	return false;
}

void __stdcall hooks::FrameStageNotify(ClientFrameStage stage)
{
	switch (stage)
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		skinFeatures::ApplySkin();
		break;
	}

	FrameStageNotifyOrginal(interfaces::baseClient, stage);
}

long __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept
{
	static const auto returnAddress = _ReturnAddress();

	const auto result = EndSceneOriginal(device, device);

	// Stop endscene getting called twice 
	if (_ReturnAddress() == returnAddress) return result;

	if (!gui::setup)
		gui::SetupMenu(device);

	if (gui::open)
		gui::Render();

	return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}