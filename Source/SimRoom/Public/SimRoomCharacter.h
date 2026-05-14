#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimRoomCharacter.generated.h"

class UCameraComponent;
class USimRoomInteractionComponent;

UCLASS(Blueprintable)
class SIMROOM_API ASimRoomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASimRoomCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USimRoomInteractionComponent> InteractionComponent;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void Interact();
};
