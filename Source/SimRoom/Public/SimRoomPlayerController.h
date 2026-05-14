#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimRoomPlayerController.generated.h"

UCLASS(Blueprintable)
class SIMROOM_API ASimRoomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASimRoomPlayerController();
};
