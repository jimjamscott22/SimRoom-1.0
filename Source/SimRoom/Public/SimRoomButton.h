#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "SimRoomButton.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class ESimRoomButtonMode : uint8
{
	OneShot,
	Toggle,
	Hold
};

UCLASS(Blueprintable)
class SIMROOM_API ASimRoomButton : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	ASimRoomButton();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual bool CanInteract_Implementation(AActor* Interactor) const override;
	virtual FText GetInteractionText_Implementation() const override;
	virtual void OnFocusStart_Implementation(AActor* Interactor) override;
	virtual void OnFocusEnd_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetPressed(bool bNewPressed, AActor* SourceActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonCap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	ESimRoomButtonMode ButtonMode = ESimRoomButtonMode::OneShot;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Button")
	TArray<TObjectPtr<AActor>> LinkedTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FVector PressedOffset = FVector(0.0f, 0.0f, -12.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (ClampMin = "0.01"))
	float PressAnimationDuration = 0.12f;

	UPROPERTY(BlueprintReadOnly, Category = "Button")
	bool bIsPressed = false;

	UPROPERTY(BlueprintReadOnly, Category = "Button")
	bool bHasBeenUsed = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	FVector ReleasedLocation;

	UPROPERTY(Transient)
	float CurrentAlpha = 0.0f;

	UPROPERTY(Transient)
	float TargetAlpha = 0.0f;
};
