#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TriggerableInterface.generated.h"

UINTERFACE(BlueprintType)
class SIMROOM_API UTriggerableInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMROOM_API ITriggerableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger")
	void Activate(AActor* SourceActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger")
	void Deactivate(AActor* SourceActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger")
	void Toggle(AActor* SourceActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Trigger")
	bool IsActive() const;
};
