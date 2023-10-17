#include "RollABallItemBase.h"
#include "RollABall/Game/RollABallPlayer.h"
#include "RollABall/Game/RollABallGameModeBase.h"

// Sets default values
ARollABallItemBase::ARollABallItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollABallItemBase::OverlapBegin);
}

// Called when the game starts or when spawned
void ARollABallItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ARollABallItemBase::OverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<ARollABallPlayer>(OtherActor))
	{
		Collected();
	}
}

void ARollABallItemBase::Collected_Implementation()
{
	ARollABallGameModeBase *GameMode = Cast<ARollABallGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}