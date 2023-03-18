#pragma once

#include "../utility/mem.h"
#include "../utility/netvars.h"

#include "CClientClass.h"

class CEntity
{
public:
	enum EFlags : std::int32_t
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};

	// Netvars
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", std::int32_t);
	NETVAR(ViewModel, "CBasePlayer->m_hViewModel[0]", unsigned long)
	NETVAR(GetWeapons, "CBaseCombatCharacter->m_hMyWeapons", unsigned long[48])

public:
	constexpr CClientClass* GetClientClass() noexcept
	{
		return mem::Call<CClientClass*>(this + 0x8, 2);
	}

	constexpr bool IsAlive() noexcept
	{
		return mem::Call<bool>(this, 156);
	}
};

class BaseCombatWeapon : public CEntity
{
public:
	NETVAR(ViewModelIndex, "CBaseCombatWeapon->m_iViewModelIndex", int)
	NETVAR(WorldModelIndex, "CBaseCombatWeapon->m_iWorldModelIndex", int)
	NETVAR(WorldDroppedModelIndex, "CBaseCombatWeapon->m_iWorldDroppedModelIndex", int)
	NETVAR(WeaponWorldModel, "CBaseCombatWeapon->m_hWeaponWorldModel", unsigned long)
};

class BaseAttributableItem : public BaseCombatWeapon
{
public:
	NETVAR(GetModelIndex, "CBaseVewModel->m_nModelIndex", unsigned long)
	NETVAR(GetAccountID, "CBaseAttributableItem->m_iAccountID", int)
	NETVAR(GetItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", short)
	NETVAR(GetItemIDHigh, "CBaseAttributableItem->m_iItemIDHigh", int)
	NETVAR(GetEntityQuality, "CBaseAttributableItem->m_iEntityQuality", int)
	NETVAR(GetCustomName, "CBaseAttributableItem->m_szCustomName", char[32])
	NETVAR(GetFallbackPaintKit, "CBaseAttributableItem->m_nFallbackPaintKit", int)
	NETVAR(GetFallbackSeed, "CBaseAttributableItem->m_nFallbackSeed", unsigned)
	NETVAR(GetFallbackWear, "CBaseAttributableItem->m_flFallbackWear", float)
	NETVAR(GetFallbackStatTrak, "CBaseAttributableItem->m_nFallbackStatTrak", unsigned)
};