#pragma once

#include "../State/PlayerStateBase.h"

class PlayerStateFactory
{
	//�V���O���g���p�@��������
private:
	static PlayerStateFactory* instance;

private:
	PlayerStateFactory() = default;
	PlayerStateFactory(const PlayerStateFactory&) = default;
	PlayerStateFactory& operator = (const PlayerStateFactory&) = default;
	//�V���O���g���p�@�����܂�

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
