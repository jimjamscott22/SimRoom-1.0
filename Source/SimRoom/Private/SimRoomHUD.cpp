#include "SimRoomHUD.h"

#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "SimRoomInteractionComponent.h"

void ASimRoomHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas)
	{
		return;
	}

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FCanvasLineItem Horizontal(Center + FVector2D(-CrosshairHalfSize, 0.0f), Center + FVector2D(CrosshairHalfSize, 0.0f));
	Horizontal.SetColor(CrosshairColor);
	Canvas->DrawItem(Horizontal);

	FCanvasLineItem Vertical(Center + FVector2D(0.0f, -CrosshairHalfSize), Center + FVector2D(0.0f, CrosshairHalfSize));
	Vertical.SetColor(CrosshairColor);
	Canvas->DrawItem(Vertical);

	const APawn* Pawn = GetOwningPawn();
	const USimRoomInteractionComponent* Interaction = Pawn ? Pawn->FindComponentByClass<USimRoomInteractionComponent>() : nullptr;
	if (!Interaction || !Interaction->GetFocusedActor())
	{
		return;
	}

	const FString Prompt = FString::Printf(TEXT("E - %s"), *Interaction->GetFocusedInteractionText().ToString());
	FCanvasTextItem PromptItem(Center + FVector2D(-70.0f, 36.0f), FText::FromString(Prompt), GEngine->GetSmallFont(), PromptColor);
	PromptItem.EnableShadow(FLinearColor::Black);
	Canvas->DrawItem(PromptItem);
}
