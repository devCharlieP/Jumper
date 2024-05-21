// Fill out your copyright notice in the Description page of Project Settings.

#include "JPPawn.h"


// Sets default values
AJPPawn::AJPPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAN(TEXT("/Game/Man/Mesh/Full/SK_Man_Full_04.SK_Man_Full_04"));
	if (SK_MAN.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_MAN.Object);
	}

	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> JUMPER_ANIM(TEXT("/Game/Save/Animations/JumperAnimBlueprint.JumperAnimBlueprint_C"));
	if (JUMPER_ANIM.Succeeded())
	{
		Mesh->SetAnimInstanceClass(JUMPER_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void AJPPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJPPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJPPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AJPPawn::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AJPPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AJPPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AJPPawn::LeftRight);
}

void AJPPawn::UpDown(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AJPPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}


