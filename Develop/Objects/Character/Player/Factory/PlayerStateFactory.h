#pragma once

#include "../State/PlayerStateBase.h"

class PlayerStateFactory
{
	//シングルトン用　ここから
private:
	static PlayerStateFactory* instance;

private:
	PlayerStateFactory() = default;
	PlayerStateFactory(const PlayerStateFactory&) = default;
	PlayerStateFactory& operator = (const PlayerStateFactory&) = default;
	//シングルトン用　ここまで

private:
	class Nomal* nomal;
	class Super* super;
	class Fire* fire;

private:
	void Initialize(class Player& player);

public:
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	static void Finalize();
};
