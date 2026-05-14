#include "SimRoomCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimRoomInteractionComponent.h"

ASimRoomCharacter::ASimRoomCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-10.0f, 0.0f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<USimRoomInteractionComponent>(TEXT("InteractionComponent"));

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ASimRoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASimRoomCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASimRoomCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASimRoomCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASimRoomCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ASimRoomCharacter::Interact);
}

void ASimRoomCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ASimRoomCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASimRoomCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASimRoomCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASimRoomCharacter::Interact()
{
	if (InteractionComponent)
	{
		InteractionComponent->Interact();
	}
}
