#include "SimRoomButton.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TriggerableInterface.h"

ASimRoomButton::ASimRoomButton()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	ButtonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonBase"));
	ButtonBase->SetupAttachment(SceneRoot);

	ButtonCap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonCap"));
	ButtonCap->SetupAttachment(SceneRoot);
}

void ASimRoomButton::BeginPlay()
{
	Super::BeginPlay();
	ReleasedLocation = ButtonCap ? ButtonCap->GetRelativeLocation() : FVector::ZeroVector;
}

void ASimRoomButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!ButtonCap || FMath::IsNearlyEqual(CurrentAlpha, TargetAlpha))
	{
		return;
	}

	const float Step = DeltaSeconds / FMath::Max(PressAnimationDuration, KINDA_SMALL_NUMBER);
	CurrentAlpha = FMath::FInterpConstantTo(CurrentAlpha, TargetAlpha, DeltaSeconds, Step / FMath::Max(DeltaSeconds, KINDA_SMALL_NUMBER));
	ButtonCap->SetRelativeLocation(FMath::Lerp(ReleasedLocation, ReleasedLocation + PressedOffset, CurrentAlpha));
}

void ASimRoomButton::Interact_Implementation(AActor* Interactor)
{
	switch (ButtonMode)
	{
	case ESimRoomButtonMode::OneShot:
		SetPressed(true, Interactor);
		bHasBeenUsed = true;
		break;
	case ESimRoomButtonMode::Toggle:
		SetPressed(!bIsPressed, Interactor);
		break;
	case ESimRoomButtonMode::Hold:
		SetPressed(true, Interactor);
		break;
	default:
		break;
	}
}

bool ASimRoomButton::CanInteract_Implementation(AActor* Interactor) const
{
	return ButtonMode != ESimRoomButtonMode::OneShot || !bHasBeenUsed;
}

FText ASimRoomButton::GetInteractionText_Implementation() const
{
	return NSLOCTEXT("SimRoom", "PressButtonPrompt", "Press Button");
}

void ASimRoomButton::OnFocusStart_Implementation(AActor* Interactor)
{
}

void ASimRoomButton::OnFocusEnd_Implementation(AActor* Interactor)
{
}

void ASimRoomButton::SetPressed(bool bNewPressed, AActor* SourceActor)
{
	if (bIsPressed == bNewPressed && ButtonMode != ESimRoomButtonMode::OneShot)
	{
		return;
	}

	bIsPressed = bNewPressed;
	TargetAlpha = bIsPressed ? 1.0f : 0.0f;

	for (AActor* Target : LinkedTargets)
	{
		if (!Target || !Target->GetClass()->ImplementsInterface(UTriggerableInterface::StaticClass()))
		{
			continue;
		}

		if (bIsPressed)
		{
			ITriggerableInterface::Execute_Activate(Target, SourceActor ? SourceActor : this);
		}
		else
		{
			ITriggerableInterface::Execute_Deactivate(Target, SourceActor ? SourceActor : this);
		}
	}
}
