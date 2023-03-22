namespace cheatVars
{
	struct Skins
	{
		bool statTrak = false;
		char nameTag[256];
		float weaponWear = 0.000f;
		int weaponSeed = 0;
	};
	inline auto skins = Skins{ };
}