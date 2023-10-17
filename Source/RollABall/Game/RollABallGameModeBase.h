#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollABallGameModeBase.generated.h"

class URollABallWidget;

UCLASS()
class ROLLABALL_API ARollABallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollABallWidget *GameWidget;

	virtual void BeginPlay() override;

	void UpdateItemText();

public:
	void ItemCollected();
};
