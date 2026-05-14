#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "TriggerableInterface.h"
#include "SimRoomDoor.generated.h"

class UStaticMeshComponent;

UCLASS(Blueprintable)
class SIMROOM_API ASimRoomDoor : public AActor, public ITriggerableInterface, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ASimRoomDoor();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Activate_Implementation(AActor* SourceActor) override;
	virtual void Deactivate_Implementation(AActor* SourceActor) override;
	virtual void Toggle_Implementation(AActor* SourceActor) override;
	virtual bool IsActive_Implementation() const override;

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual bool CanInteract_Implementation(AActor* Interactor) const override;
	virtual FText GetInteractionText_Implementation() const override;
	virtual void OnFocusStart_Implementation(AActor* Interactor) override;
	virtual void OnFocusEnd_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable, Category = "Door")
	void OpenDoor(AActor* SourceActor);

	UFUNCTION(BlueprintCallable, Category = "Door")
	void CloseDoor(AActor* SourceActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bStartsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bCanPlayerInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bCloseOnDeactivate = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FVector OpenOffset = FVector(0.0f, 0.0f, 220.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (ClampMin = "0.01"))
	float OpenDuration = 0.75f;

	UPROPERTY(BlueprintReadOnly, Category = "Door")
	bool bIsOpen = false;

	UPROPERTY(BlueprintReadOnly, Category = "Door")
	bool bIsLocked = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	FVector ClosedLocation;

	UPROPERTY(Transient)
	float CurrentAlpha = 0.0f;

	UPROPERTY(Transient)
	float TargetAlpha = 0.0f;
};
