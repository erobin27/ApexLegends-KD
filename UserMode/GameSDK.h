#pragma once
#include "myMath.h"
#include "skCrypter.h"

// glow offset //
#define GLOW_ENABLE 0x3C8  // 
#define GLOW_COLORS 0x1D0    // 
#define GLOW_CONTEXT  0x3C8 //  
#define GLOW_FADE 0x388 //  
#define GLOW_INSIDE 0x2C0 // 
#define OFFSET_GLOW_THROUGH_WALLS   0x3d0 

#define GLOW_DISTANCE 0x3B4
#define GLOW_LIFE_TIME 0x3A4
#define GLOW_TYPE 0x2C4

namespace offsets
{
	uintptr_t client_render_targets = 0x1fdeea0;
	uintptr_t ibase_client_dll = 0x19e1770;
	uintptr_t iclient_entity_list = 0x1fde6b0;
	uintptr_t cprediction = 0x1fde6b8;
	uintptr_t iv_model_render = 0x128b080;
	uintptr_t vgui_system = 0x1f98620;
	uintptr_t iv_render_view = 0x7519718;
	uintptr_t iv_debug_overlay = 0x75b48a0;
	uintptr_t iv_model_info_client = 0x7519728;
	uintptr_t iv_engine_client = 0x12799d8;
	uintptr_t iv_engine_trace = 0x7519730;
	uintptr_t inetwork_string_table = 0x7519740;
	uintptr_t cnetwork_u64_table = 0x7519748;
	uintptr_t cinput = 0x1d94ea0;
	uintptr_t cengine = 0x1292410;
	uintptr_t iswapchain = 0xb911e88;
	uintptr_t cl_entitylist = 0x19fbc18;
	uintptr_t local_entity_handle = 0x127d8bc;
	uintptr_t local_player = 0x1dac9c8;
	uintptr_t global_vars = 0x135c850;
	uintptr_t name_list = 0xb9f7e40;
	uintptr_t view_render = 0x1fdffb0;
	uintptr_t view_matrix = 0x602381;
	uintptr_t client_state = 0x135cbd0;
	uintptr_t sign_on_state = 0x135cc68;
	uintptr_t level_name = 0x135cd80;
	uintptr_t glow_enable = 0x9a1;
	uintptr_t glow_type = 0x2c0;
	uintptr_t glow_color = 0x1d0;

	namespace Glow{
		uintptr_t glow_enable = 0x9a1;	//GlowContext
		uintptr_t glow_type = 0x2c0;	//<--- questionable
		uintptr_t glow_color = 0x1d0;	//correct
		uintptr_t glow_through_walls = 0x3d0;

		uintptr_t glow_distance = 0x3B4;
		uintptr_t glow_life = 0x3A4;
		uintptr_t glow_fade = 0x388;
	}

	namespace Player {
		uint64_t iHealth = 0x0438;
		uint64_t iHealthMax = 0x0578;
		uint64_t weapons = 0x1aac;	//m_latestPrimaryWeapons
		uint64_t lifeState = 0x798;
		uint64_t bleedOutState = 0x2728;
		uint64_t ammopoolCapacity = 0x259c;
		uint64_t viewAngles = ammopoolCapacity - 0x14;
		uint64_t breathAngles = viewAngles - 0x10;
		uint64_t aimpunch = 0x24a0;
		uint64_t inventory = 0x1a50;
	};

	namespace BaseEntity {
		uint64_t Team = 0x448;
		uint64_t Name = 0x589;
		uint64_t iShield = 0x170;
		uint64_t iShieldMax = 0x174;
	};
};


enum WeaponId
{
	R301 = 0,
	SENTINEL = 1,
	BOCEK = 2,
	MELEE_SURVIVAL = 14,
	ALTERNATOR = 70,
	RE45,
	CHARGE_RIFLE,
	DEVOTION,
	LONGBOW,
	HAVOC,
	EVA8_AUTO,
	FLATLINE,
	G7_SCOUT,
	HEMLOK,
	KRABER,
	LSTAR,
	MASTIFF,
	MOZAMBIQUE,
	PROWLER,
	PEACEKEEPER,
	R99,
	P2020,
	SPITFIRE,
	TRIPLE_TAKE,
	WINGMAN,
	VOLT,
	REPEATER,
};

struct glowFade
{
	int a, b;
	float c, d, e, f;
};

struct glowMode
{
	BYTE GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

struct colorRGB
{
	float r, g, b;
};


class BaseEntity {
private:
	uint64_t EntityList;
	uint64_t BaseEnt;
	uint64_t EntityHandle;

public:
	uint64_t Entity;
	std::string identifier;
	glowMode glowStyle = { 0, 102, 100, 255 }; //Default Glow is Outline

	explicit BaseEntity(int index) {
		EntityList = base_address + offsets::cl_entitylist;
		BaseEnt = mem->Read<uint64_t>(EntityList);
		Entity = mem->Read<uint64_t>(EntityList + (index << 5)); //Returns Entity Address

		if (Entity != 0) {
			EntityHandle = mem->Read<DWORD64>(Entity + offsets::BaseEntity::Name); //Entity + iName
			identifier = mem->ReadString(EntityHandle,64);
		}
	}

	bool IsPlayer()
	{
		uint64_t name = mem->Read<uint64_t>(Entity + offsets::BaseEntity::Name);
		return (name == 125780153691248);
	}
	bool IsAlive()
	{
		return mem->Read<int>(Entity + offsets::Player::lifeState) == 0;
	}
	bool IsKnocked()
	{
		return mem->Read<int>(Entity + offsets::Player::bleedOutState) > 0;
	}
	int GetTeam()
	{
		return mem->Read<int>(Entity + offsets::BaseEntity::Team);
	}
	bool IsDummy()
	{
		uint64_t team = mem->Read<uint64_t>(Entity + offsets::BaseEntity::Team);
		return (team == 97);
	}

	int iHealth() {
		return mem->Read<int>(Entity + offsets::Player::iHealth);
	}

	int iHealthMax() {
		return mem->Read<int>(Entity + offsets::Player::iHealthMax);
	}

	int iShield() {
		return mem->Read<int>(Entity + offsets::BaseEntity::iShield);
	}

	int iShieldMax() {
		return mem->Read<int>(Entity + offsets::BaseEntity::iShieldMax);
	}

	void Glow(float r, float g, float b) {
		if (r == 0.f && g == 0.f && b == 0.f) {
			colorRGB color = { r, g, b };
			mem->write<colorRGB>(Entity + offsets::Glow::glow_color, color);	//colors -- good
			mem->write<float>(Entity + offsets::Glow::glow_distance, 10000.f);	//glowdistance -- good
			mem->write<int>(Entity + offsets::Glow::glow_enable, 2);
			mem->write<int>(Entity + OFFSET_GLOW_THROUGH_WALLS, 5);
			return;
		}

		float time = 5000.f;
		colorRGB color = { r, g, b };
		glowMode glowStyle = { 0, 102, 100, 255 }; //Default Glow is Outline


		//mem->write<glowMode>(Entity + GLOW_TYPE, glowStyle);
		mem->write<colorRGB>(Entity + offsets::Glow::glow_color, color);	//colors -- good
		mem->write<float>(Entity + offsets::Glow::glow_distance, 40000.f);	//glowdistance -- good
		
		mem->write<float>(Entity + GLOW_LIFE_TIME, time);
		time -= 1.f;
		
		mem->write<int>(Entity + offsets::Glow::glow_enable, 7);
		mem->write<int>(Entity + offsets::Glow::glow_through_walls, 2);
		mem->write<int>(Entity + GLOW_CONTEXT, 1);
		mem->write<glowFade>(Entity + GLOW_FADE, { 872415232, 872415232, time, time, time, time });

		//mem->write<int>(Entity + OFFSET_GLOW_T1, 16256);
		//mem->write<int>(Entity + OFFSET_GLOW_T2, 1193322764);
	}

};

class LocalEntity {
public:
	uint64_t Entity;
	std::string identifier;

	LocalEntity() {
		Entity = mem->Read<uint64_t>(base_address + offsets::local_player); //Returns Entity Address
	}
	bool IsAlive()
	{
		return mem->Read<int>(Entity + offsets::Player::lifeState) == 0;
	}
	bool IsKnocked()
	{
		return mem->Read<int>(Entity + offsets::Player::bleedOutState) > 0;
	}
	int GetTeam()
	{
		return mem->Read<int>(Entity + offsets::BaseEntity::Team);
	}
	Vector3 GetViewAngles()
	{
		return mem->Read<Vector3>(Entity + offsets::Player::viewAngles);
	}
	Vector3 GetSwayAngles()
	{
		return mem->Read<Vector3>(Entity + offsets::Player::breathAngles);
	}
	Vector3 GetRecoilA()
	{
		return mem->Read<Vector3>(Entity + offsets::Player::aimpunch);
	}
	void SetViewAngles(Vector3 angles)
	{
		mem->write<Vector3>(Entity + offsets::Player::viewAngles, angles);
	}

	int getWeapon() {
		uint64_t wepHandle = mem->Read<uint64_t>(Entity + offsets::Player::weapons);
		//std::cout << ""
		wepHandle &= 0xffff;
		uint64_t heldWeapon = mem->Read<uint64_t>(base_address + offsets::cl_entitylist + (wepHandle << 5));
		int heldWeaponId = mem->Read<int>(heldWeapon + 0x16c4); //held + m_weaponNameIndex in [RecvTable.DT_WeaponX]


		return heldWeaponId;
	}
};