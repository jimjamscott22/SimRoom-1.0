#include "SimRoomInteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"

USimRoomInteractionComponent::USimRoomInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USimRoomInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	RefreshFocus();
}

void USimRoomInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTraceEveryTick)
	{
		RefreshFocus();
	}
}

void USimRoomInteractionComponent::Interact()
{
	AActor* Actor = FocusedActor.Get();
	AActor* Owner = GetOwner();
	if (!Actor || !Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		return;
	}

	if (IInteractableInterface::Execute_CanInteract(Actor, Owner))
	{
		IInteractableInterface::Execute_Interact(Actor, Owner);
		RefreshFocus();
	}
}

void USimRoomInteractionComponent::RefreshFocus()
{
	AActor* Owner = GetOwner();
	UWorld* World = GetWorld();
	UCameraComponent* Camera = FindViewCamera();

	if (!Owner || !World || !Camera)
	{
		SetFocusedActor(nullptr, FText::GetEmpty());
		return;
	}

	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + Camera->GetForwardVector() * InteractionRange;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(SimRoomInteractionTrace), false, Owner);
	FHitResult Hit;

	AActor* NewFocusedActor = nullptr;
	FText NewText = FText::GetEmpty();

	if (World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, Params))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			if (IInteractableInterface::Execute_CanInteract(HitActor, Owner))
			{
				NewFocusedActor = HitActor;
				NewText = IInteractableInterface::Execute_GetInteractionText(HitActor);
			}
		}
	}

	SetFocusedActor(NewFocusedActor, NewText);
}

void USimRoomInteractionComponent::SetFocusedActor(AActor* NewFocusedActor, const FText& NewInteractionText)
{
	AActor* OldActor = FocusedActor.Get();
	if (OldActor == NewFocusedActor && FocusedInteractionText.EqualTo(NewInteractionText))
	{
		return;
	}

	AActor* Owner = GetOwner();
	if (OldActor && OldActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		IInteractableInterface::Execute_OnFocusEnd(OldActor, Owner);
	}

	FocusedActor = NewFocusedActor;
	FocusedInteractionText = NewInteractionText;

	if (NewFocusedActor && NewFocusedActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		IInteractableInterface::Execute_OnFocusStart(NewFocusedActor, Owner);
	}

	OnFocusChanged.Broadcast(NewFocusedActor, FocusedInteractionText);
}

UCameraComponent* USimRoomInteractionComponent::FindViewCamera() const
{
	const AActor* Owner = GetOwner();
	return Owner ? Owner->FindComponentByClass<UCameraComponent>() : nullptr;
}
