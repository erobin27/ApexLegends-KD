#include "UM-Memory.h"
#include "GameSDK.h"
#include <codecvt>
#include "skCrypter.h"
#include "Entity.h"

//game structs
//[Base + g_BN_Steam] + oEntityRealm] + oClientEntitiesList] + oClientEntitiesValues]
//client entities = read()
bool ReadBuffer(uint64_t address, uint64_t* buffer, int size) {
	for (int i = 0; i < size; i++) {
		buffer[i] = mem->Read<uint64_t>(address + i * sizeof(uint64_t));
	}

	return true;
}

std::string readCharString(DWORD64 address, int length) {
	std::string str = "";
	for (int i = 0; i < length; i++) {
		str += mem->Read<char>(address + i);
	}

	return str;
}

float randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void printVector3(Vector3 vec) {
	std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

void printQAngle(QAngle vec) {
	std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

bool printViewAngles() {
	LocalEntity lPlayer = LocalEntity();
	if (!lPlayer.Entity) return false;
	Vector3 vView = lPlayer.GetViewAngles();
	printVector3(vView);
}

bool NoRecoil(bool shouldReset) {
	LocalEntity lPlayer = LocalEntity();
	if (!lPlayer.Entity) return false;

	int held = lPlayer.getWeapon();
	switch (held) {
		
		case bow:		 return false;
		case melee_survival: return false;
		case scout:		return false;
		//shotgun
		case peacekeeper: return false;
		case mastiff: return false;
		case eva8: return false;
		case mozambique: return false;
		//Sniper
		case chargerifle: return false;
		case longbow:	 return false;
		case kraber:	 return false;
		case sentinel:	 return false;
		//light
		case p2020:		return false;
		//heavy
		case repeater:	return false;
		case hemlock:	return false;
		case prowler:	return false;
		case wingman:	 return false;
	}

	static Vector3 LastPunchAngle = Vector3(0.0f, 0.0f, 0.0f);
	if (shouldReset) {
		LastPunchAngle = Vector3(0.0f, 0.0f, 0.0f);
	}
	if (lPlayer.IsAlive() && !lPlayer.IsKnocked())
	{
		Vector3 ViewAngle = lPlayer.GetViewAngles();
		Vector3 PunchAngle = lPlayer.GetRecoilA();

		Vector3 OriginalVA = ViewAngle;
		//std::cout << skCrypt("Original Viewangle:"); printVector3(OriginalVA);
		ViewAngle += LastPunchAngle;
		//std::cout << skCrypt("Actual AfterShooting Viewangle:"); printVector3(OriginalVA);
		//std::cout << skCrypt("Predicted AfterShooting Viewangle:"); printVector3(ViewAngle);
		//std::cout << skCrypt("Punch:"); printVector3(PunchAngle);
		//PunchAngle *= .8;
		ViewAngle -= PunchAngle;
		//std::cout << skCrypt("Predicted AfterCorrection Viewangle:"); printVector3(ViewAngle);
		NormalizeAngles(ViewAngle);
		//std::cout << skCrypt("Normalized Viewangle:"); printVector3(ViewAngle);
		if (ViewAngle.y >= 180 || ViewAngle.y <= -180) {
			std::cout << skCrypt("HUUUUUUUUUUUUUUUUUUUUUUMONGOUS ERROR:"); printVector3(ViewAngle);
			return false;
		}
		//std::cout << "\n\n\n";
		lPlayer.SetViewAngles(ViewAngle);
		LastPunchAngle = PunchAngle;
	}
}
/*
void enableHighlight(uint64_t Entity, float r, float b, float g) {
	std::cout << "\tEnableG-: " << mem->Read<bool>(Entity + offsets::glow_enable) << std::endl;
	std::cout << "\tEnableG-: " << mem->Read<int>(Entity + offsets::glow_type) << std::endl;
	std::cout << "\tR: " << mem->Read<float>(Entity + offsets::glow_color) << std::endl;
	std::cout << "\tG: " << mem->Read<float>(Entity + offsets::glow_color + 0x4) << std::endl;
	std::cout << "\tB: " << mem->Read<float>(Entity + offsets::glow_color + 0x8) << std::endl;

	for (int offset = 0x2B0; offset <= 0x2C8; offset += 0x4) {
		std::cout << "\tG-Duration: " << mem->Read<float>(Entity + offset) << std::endl;
	}
	std::cout << "\tG-Distance: " << mem->Read<float>(Entity + 0x2DC) << std::endl;
}
*/
void disableGlow() {
	for (int i = 0; i < 100; i++) {
		BaseEntity player(i);

		if (player.Entity == 0 || !player.IsAlive()) continue;

		if (player.IsPlayer()) {
			player.Glow(0.f, 0.f, 0.f);
		}
	}
}

void Glow() {
	LocalEntity lP = LocalEntity();
	if (!lP.Entity) return;
	int locTeam = lP.GetTeam();

	for (int i = 0; i < 100; i++) {
		BaseEntity player(i);

		if (player.Entity == 0 || !player.IsAlive() || !player.IsPlayer() || player.GetTeam() == locTeam) continue;	//if null, dead, not player, or teammate        dont glow

		int totalHealth = player.iHealth() + player.iShield();

		if (totalHealth <= 300 && totalHealth > 200)	//Red Shields
		{
			player.Glow(8.f, 0.f, 0.f); //red
		}
		else if (totalHealth <= 200 && totalHealth > 175)	//Purple/Gold Shields
		{
			player.Glow(4.f, 2.f, 7.f); //purple
		}
		else if (totalHealth <= 175 && totalHealth > 150)	//Blue Shields
		{
			player.Glow(0.f, 8.f, 8.f); //blue
		}
		else if (totalHealth <= 150 && totalHealth > 100)	//White Shields
		{
			player.Glow(8.f, 8.f, 8.f); //white
		}
		else if (totalHealth <= 100 && totalHealth > 50)	//Cracked
		{
			player.Glow(8.f, 8.f, 0.f); //cracked
		}
		else if (totalHealth <= 50 && totalHealth > 0)
		{
			player.Glow(8.f, 0.f, 8.f); //oneshot
		}
		else if (player.IsKnocked())	//knocked
		{
			player.Glow(2.f, 2.f, 2.f); //downed
		}
	}
}

uint64_t getLocalPlayer() {
	return mem->Read<uint64_t>(base_address + offsets::local_player);
}

/*
bool getPlayers() {
	uint64_t EntityList = base_address + offsets::cl_entitylist;
	uint64_t BaseEntity = mem->Read<uint64_t>(EntityList);
	if (!BaseEntity) return false;

	for (int i = 0; i < 128; i++) {
		uint64_t localEntity = mem->Read<uint64_t>(base_address + offsets::local_player); //double check this
		if (!localEntity) return false;

		localPlayer.player_entity = localEntity;
		localPlayer.player_id = 0;

		uint64_t currEntity = mem->Read<uint64_t>(EntityList + ((uint64_t)i << 5));
		//if (!isPlayer(currEntity)) return false;

	}
}
*/

bool GetEntityById(int id) {
	uint64_t EntitlyList = base_address + offsets::cl_entitylist;
	uint64_t BaseEntity = mem->Read<uint64_t>(EntitlyList);

}