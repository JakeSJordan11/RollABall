#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollABallItemBase.generated.h"

UCLASS()
class ROLLABALL_API ARollABallItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARollABallItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent *Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintNativeEvent)
	void Collected();
};
