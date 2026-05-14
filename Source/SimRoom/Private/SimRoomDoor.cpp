#include "SimRoomDoor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

ASimRoomDoor::ASimRoomDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(SceneRoot);

	DoorPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorPanel"));
	DoorPanel->SetupAttachment(SceneRoot);
}

void ASimRoomDoor::BeginPlay()
{
	Super::BeginPlay();

	bIsLocked = bStartsLocked;
	ClosedLocation = DoorPanel ? DoorPanel->GetRelativeLocation() : FVector::ZeroVector;
	CurrentAlpha = bIsOpen ? 1.0f : 0.0f;
	TargetAlpha = CurrentAlpha;
}

void ASimRoomDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!DoorPanel || FMath::IsNearlyEqual(CurrentAlpha, TargetAlpha))
	{
		return;
	}

	const float Step = DeltaSeconds / FMath::Max(OpenDuration, KINDA_SMALL_NUMBER);
	CurrentAlpha = FMath::FInterpConstantTo(CurrentAlpha, TargetAlpha, DeltaSeconds, Step / FMath::Max(DeltaSeconds, KINDA_SMALL_NUMBER));
	DoorPanel->SetRelativeLocation(FMath::Lerp(ClosedLocation, ClosedLocation + OpenOffset, CurrentAlpha));
}

void ASimRoomDoor::Activate_Implementation(AActor* SourceActor)
{
	bIsLocked = false;
	OpenDoor(SourceActor);
}

void ASimRoomDoor::Deactivate_Implementation(AActor* SourceActor)
{
	if (bCloseOnDeactivate)
	{
		CloseDoor(SourceActor);
	}
}

void ASimRoomDoor::Toggle_Implementation(AActor* SourceActor)
{
	if (bIsOpen)
	{
		CloseDoor(SourceActor);
	}
	else
	{
		OpenDoor(SourceActor);
	}
}

bool ASimRoomDoor::IsActive_Implementation() const
{
	return bIsOpen;
}

void ASimRoomDoor::Interact_Implementation(AActor* Interactor)
{
	if (bIsOpen)
	{
		CloseDoor(Interactor);
	}
	else
	{
		OpenDoor(Interactor);
	}
}

bool ASimRoomDoor::CanInteract_Implementation(AActor* Interactor) const
{
	return bCanPlayerInteract && !bIsLocked;
}

FText ASimRoomDoor::GetInteractionText_Implementation() const
{
	return bIsOpen ? NSLOCTEXT("SimRoom", "CloseDoorPrompt", "Close Door") : NSLOCTEXT("SimRoom", "OpenDoorPrompt", "Open Door");
}

void ASimRoomDoor::OnFocusStart_Implementation(AActor* Interactor)
{
}

void ASimRoomDoor::OnFocusEnd_Implementation(AActor* Interactor)
{
}

void ASimRoomDoor::OpenDoor(AActor* SourceActor)
{
	if (bIsLocked)
	{
		return;
	}

	bIsOpen = true;
	TargetAlpha = 1.0f;
}

void ASimRoomDoor::CloseDoor(AActor* SourceActor)
{
	bIsOpen = false;
	TargetAlpha = 0.0f;
}
