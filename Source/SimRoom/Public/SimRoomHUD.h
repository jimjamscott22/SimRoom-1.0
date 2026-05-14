#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SimRoomHUD.generated.h"

UCLASS(Blueprintable)
class SIMROOM_API ASimRoomHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FLinearColor CrosshairColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FLinearColor PromptColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	float CrosshairHalfSize = 6.0f;
};
