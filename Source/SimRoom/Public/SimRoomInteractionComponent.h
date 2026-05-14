#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimRoomInteractionComponent.generated.h"

class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractionFocusChangedSignature, AActor*, FocusedActor, const FText&, InteractionText);

UCLASS(ClassGroup = (SimRoom), Blueprintable, meta = (BlueprintSpawnableComponent))
class SIMROOM_API USimRoomInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USimRoomInteractionComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RefreshFocus();

	UFUNCTION(BlueprintPure, Category = "Interaction")
	AActor* GetFocusedActor() const { return FocusedActor.Get(); }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FText GetFocusedInteractionText() const { return FocusedInteractionText; }

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FInteractionFocusChangedSignature OnFocusChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "50.0"))
	float InteractionRange = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bTraceEveryTick = true;

private:
	void SetFocusedActor(AActor* NewFocusedActor, const FText& NewInteractionText);
	UCameraComponent* FindViewCamera() const;

	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> FocusedActor;

	UPROPERTY(Transient)
	FText FocusedInteractionText;
};
