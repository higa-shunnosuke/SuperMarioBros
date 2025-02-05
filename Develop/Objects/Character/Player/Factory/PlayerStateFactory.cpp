#include "PlayerStateFactory.h"

#include "../State/Nomal.h"
#include "../State/Super.h"
#include "../State/Fire.h"
#include "../State/Tibi.h"

#include "../Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

void PlayerStateFactory::Initialize(class Player& player)
{
	nomal = new Nomal(&player);
	super = new Super(&player);
	fire = new Fire(&player);
	tibi = new Tibi(&player);
}

void PlayerStateFactory::Finalize()
{
	instance->nomal->Finalize();
	instance->super->Finalize();
	instance->fire->Finalize();
	instance->tibi->Finalize();

	delete instance->nomal;
	delete instance->super;
	delete instance->fire;
	delete instance->tibi;

	instance = nullptr;
}

PlayerStateBase* PlayerStateFactory::Get(class Player& player, ePlayerState state)
{
	if (instance == nullptr)
	{
		instance = new PlayerStateFactory();
		instance->Initialize(player);
	}

	PlayerStateBase* ret = nullptr;
	switch (state)
	{
	case ePlayerState::NOMAL:
		instance->nomal->Initialize();
		ret = instance->nomal;
		break;
	case ePlayerState::SUPER:
		instance->super->Initialize();
		ret = instance->super;
		break;
	case ePlayerState::FIRE:
		instance->fire->Initialize();
		ret = instance->fire;
		break;
	case ePlayerState::TIBI:
		instance->tibi->Initialize();
		ret = instance->tibi;
		break;
	case ePlayerState::NONE:	//•Ô‚·‚à‚Ì‚È‚µ
	default:
		break;
	}

	return ret;
}