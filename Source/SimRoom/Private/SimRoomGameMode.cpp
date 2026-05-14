#include "SimRoomGameMode.h"

#include "SimRoomCharacter.h"
#include "SimRoomHUD.h"
#include "SimRoomPlayerController.h"

ASimRoomGameMode::ASimRoomGameMode()
{
	DefaultPawnClass = ASimRoomCharacter::StaticClass();
	PlayerControllerClass = ASimRoomPlayerController::StaticClass();
	HUDClass = ASimRoomHUD::StaticClass();
}
