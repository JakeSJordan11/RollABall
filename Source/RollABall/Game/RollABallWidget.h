#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RollABallWidget.generated.h"

UCLASS()
class ROLLABALL_API URollABallWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetItemText(int32 ItemsCollected, int32 ItemsInLevel);
};
