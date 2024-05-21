// Fill out your copyright notice in the Description page of Project Settings.

#include "JPCharacter.h"
#include "TimerManager.h"

// Sets default values
AJPCharacter::AJPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAN(TEXT("/Game/Man/Mesh/Full/SK_Man_Full_04.SK_Man_Full_04"));
	if (SK_MAN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAN.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> JUMPER_ANIM(TEXT("/Game/Save/Animations/JumperAnimBlueprint.JumperAnimBlueprint_C"));
	if (JUMPER_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(JUMPER_ANIM.Class);
	}

	SetControlMode(0);

	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	RunSpeedMultiplier = 2.0f;
	
	bIsClimbing = false;
	bIsOnCeiling = false;
	bIsJump = false;
}

// Called when the game starts or when spawned
void AJPCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AJPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTimerHandle TimerHandle;

	if (bIsClimbing)
	{
		CheckWallAndCeilingPresence();

		if (bIsOnCeiling)
		{
			bIsJump = true;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJPCharacter::StopClimbing, 1.0f, false);

			// 수직, 전방 이동 처리
			float VerticalInput = 1.8f;

			FVector ForwardMove = GetActorForwardVector() * VerticalInput * ClimbingSpeed * DeltaTime;
			FVector VerticalMove = FVector(0.0f, 0.0f, VerticalInput * ClimbingSpeed * DeltaTime);
			FVector CombinedMove = VerticalMove + ForwardMove;

			SetActorLocation(GetActorLocation() + CombinedMove);
		}
		else
		{
			// 수직 이동 처리
			float VerticalInput = GetInputAxisValue(TEXT("UpDown"));
			ClimbingDirectionUD = VerticalInput;

			FVector VerticalMove = FVector(0.0f, 0.0f, VerticalInput * ClimbingSpeed * DeltaTime);
			SetActorLocation(GetActorLocation() + VerticalMove);

			// 수평 이동 처리
			float HorizontalInput = GetInputAxisValue(TEXT("LeftRight"));
			ClimbingDirectionLR = HorizontalInput;

			FVector RightVector = FVector::CrossProduct(WallNormal, FVector::UpVector).GetSafeNormal();
			FVector HorizontalMove = RightVector * HorizontalInput * ClimbingSpeed * DeltaTime;
			SetActorLocation(GetActorLocation() + HorizontalMove);
		}
	}
}

// Called to bind functionality to input
void AJPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AJPCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AJPCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJPCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJPCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AJPCharacter::Run);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AJPCharacter::StopRun);

	PlayerInputComponent->BindAction(TEXT("ClimbingWall"), EInputEvent::IE_Pressed, this, &AJPCharacter::ToggleClimbing);
}

void AJPCharacter::UpDown(float NewAxisValue)
{
	if(!bIsClimbing)
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AJPCharacter::LeftRight(float NewAxisValue)
{
	if(!bIsClimbing)
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AJPCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AJPCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void AJPCharacter::Jump()
{
	if (bIsJump)
		return;

	Super::Jump();

	if(bIsClimbing)
		StopClimbing();
}

void AJPCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed *= RunSpeedMultiplier;
}

void AJPCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed /= RunSpeedMultiplier;
}

void AJPCharacter::CheckWallAndCeilingPresence()
{
	FVector StartHead = GetActorLocation() + FVector(0, 0, 80);  // 캐릭터 머리 높이에서 시작
	FVector EndForward = StartHead + GetActorForwardVector() * 100.0f;  // 앞으로 100 유닛 거리 확인
	FHitResult HitForward;

	FVector StartFeet = GetActorLocation() + FVector(0, 0, -5);  // 캐릭터 발밑에서 시작
	FVector EndDown = StartFeet + FVector(0, 0, -100.0f);  // 아래로 100 유닛 거리 확인
	FHitResult HitDown;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);  // 자신은 무시
	Params.bReturnPhysicalMaterial = true;

	// 벽 감지
	bool bHitForward = GetWorld()->LineTraceSingleByChannel(HitForward, StartHead, EndForward, ECC_WorldStatic, Params);
	bool bHitDown = GetWorld()->LineTraceSingleByChannel(HitDown, StartFeet, EndDown, ECC_WorldStatic, Params);

	// 발밑에 땅이 감지되면 Climbing 중지
	if (bHitDown && HitDown.bBlockingHit)
	{
		if (ClimbingDirectionUD < 0.0f)  // 내려가고 있는 상태
		{
			StopClimbing();
			return;
		}
	}

	// 벽을 감지하지 못했을 때
	if (!bHitForward || !(HitForward.bBlockingHit && FVector::DotProduct(HitForward.ImpactNormal, FVector::UpVector) < 0.3))
	{
		if (ClimbingDirectionUD > 0.0f)  // 올라가고 있는 상태
		{
			bIsOnCeiling = true;
		}
		else  // 내려가거나 옆으로 이동 중인 상태
		{
			StopClimbing();
		}
	}
	else
	{
		WallNormal = HitForward.ImpactNormal;
		bIsOnCeiling = false;
	}
}

void AJPCharacter::ToggleClimbing()
{
	if (!bIsClimbing)
	{
		StartClimbing();
	}
	else
	{
		StopClimbing();
	}
}

void AJPCharacter::StartClimbing()
{
	if (bIsClimbing) return;  // 이미 클라이밍 상태인 경우 함수를 종료

	FVector Start = GetActorLocation() + FVector(0, 0, 50);  // 레이캐스트 시작점 조정
	FVector End = Start + GetActorForwardVector() * 100.0f;  // 적절한 거리 설정
	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);  // 자신은 무시
	Params.bReturnPhysicalMaterial = true;  // 물리적 속성 반환

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params))
	{
		if (Hit.bBlockingHit && Hit.ImpactNormal.Z < 0.1)  // 벽이 거의 수직인지 검사
		{
			WallNormal = Hit.ImpactNormal;
			bIsClimbing = true;
			GetCharacterMovement()->SetMovementMode(MOVE_Custom);
		}
	}
}

void AJPCharacter::StopClimbing()
{
	bIsClimbing = false;
	bIsOnCeiling = false;
	bIsJump = false;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking); // 캐릭터 움직임을 복구
}

void AJPCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0)
	{
		SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}