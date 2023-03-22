#include <iostream>
#include "skins.h"
#include "vars.h"
#include "../../headers/globals.h"
#include "../../headers/interface.h"

bool skinFeatures::ApplySkin() noexcept
{
	// Check if player is alive & in-game
	if (!globals::localPlayer->IsAlive() || !interfaces::engine->IsInGame()) return false;
	
	// Loop through player current weapon
	for (const auto& wHandle : globals::localPlayer->GetWeapons())
	{
		// Grab Weapon Attribute
		BaseAttributableItem* pWeapon = (BaseAttributableItem*)interfaces::entityList->GetClientEntityFromHandle(wHandle);

		// Check if its an actual weapon
		if (!pWeapon) continue;

		// Grab weapon definition 
		int nWeaponIndex = pWeapon->GetItemDefinitionIndex();

		// Set weapon id high to apply fallback
		pWeapon->GetItemIDHigh() = -1;

		if (nWeaponIndex == 9)
		{
			pWeapon->GetFallbackPaintKit() = 344;
			pWeapon->GetFallbackWear() = 0.00000001f;
		}
	}

	return true;
}