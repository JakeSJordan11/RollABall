#include "RollABallPlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollABallPlayer::ARollABallPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &ARollABallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();

	if (APlayerController *PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called to bind functionality to input
void ARollABallPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARollABallPlayer::Jump);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARollABallPlayer::Move);
	}
}

void ARollABallPlayer::Jump(const FInputActionValue &Value)
{
	if (JumpCount >= MaxJumpCount)
	{
		return;
	}
	if (JumpCount < MaxJumpCount)
	{
		Mesh->AddImpulse(FVector::UpVector * JumpImpulse);
		JumpCount++;
	}
}

void ARollABallPlayer::Move(const FInputActionValue &Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	if (CurrentValue != FVector2D::ZeroVector)
	{
		Mesh->AddForce(FVector(CurrentValue.X, CurrentValue.Y, 0.0f) * MoveForce);
	}
}

void ARollABallPlayer::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	float HitDirection = FVector::DotProduct(Hit.ImpactNormal, FVector::UpVector);
	if (HitDirection > 0.0f)
	{
		JumpCount = 0;
	}
}
