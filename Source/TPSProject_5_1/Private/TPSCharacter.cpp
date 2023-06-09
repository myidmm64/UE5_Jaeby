// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Bullet.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyFSM.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "CharacterAnim.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <CharacterAnim.h>

// Sets default values
ATPSCharacter::ATPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���̷�Ż�޽� ������ �ε�
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	// ī�޶��� �θ� ������Ʈ ����
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (springArmComp)
	{
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		springArmComp->TargetArmLength = 400;
	}

	// ī�޶� ������Ʈ
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamComp"));
	if (tpsCamComp)
	{
		tpsCamComp->SetupAttachment(springArmComp);
	}

	// 2�� ����
	JumpMaxCount = 2;

	// �������� �� ������Ʈ ���
	sniperGunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperGunComp"));
	if (sniperGunComp)
	{
		sniperGunComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

		ConstructorHelpers::FObjectFinder<UStaticMesh> TempSniper(TEXT("/Script/Engine.StaticMesh'/Game/SniperGun/sniper1.sniper1'"));

		if (TempSniper.Succeeded())
		{
			sniperGunComp->SetStaticMesh(TempSniper.Object);
			sniperGunComp->SetRelativeLocation(FVector(-42, 7, 1));
			sniperGunComp->SetRelativeRotation(FRotator(0, 90, 0));
			sniperGunComp->SetRelativeScale3D(FVector(0.15f));
		}
	}

	// �ʱ� �ӵ� ����
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	// �Ѿ� ���� ��������
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/SniperGun/Rifle.Rifle'"));

	if (tempSound.Succeeded())
	{
		bulletSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �������� UI ���� �ν��Ͻ� ����
	sniperUI = CreateWidget(GetWorld(), sniperUIFactory);

	// ũ�ν���� UI ���� �ν��Ͻ� ����
	crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);

	// ũ�ν���� UI ���
	crosshairUI->AddToViewport();

	// �⺻���� �������۰��� ����ϵ��� ����
	//ChangeToSniperGun();
	if (sniperGunComp)
		sniperGunComp->SetVisibility(true);

	hp = initialHP;
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(tpsMappingContext, 0);
		}
	}

	// ��ǲ �׼� ���ε�
	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		// MoveForward
		EnhancedInputComp->BindAction(moveForwardAction, ETriggerEvent::Triggered, this, &ATPSCharacter::MoveForward);

		// MoveRight
		EnhancedInputComp->BindAction(moveRightAction, ETriggerEvent::Triggered, this, &ATPSCharacter::MoveRight);

		// TurnPitch
		EnhancedInputComp->BindAction(turnPitchAction, ETriggerEvent::Triggered, this, &ATPSCharacter::TurnPitch);

		// TurnYaw
		EnhancedInputComp->BindAction(turnYawAction, ETriggerEvent::Triggered, this, &ATPSCharacter::TurnYaw);

		// InputFire
		EnhancedInputComp->BindAction(fireAction, ETriggerEvent::Triggered, this, &ATPSCharacter::InputFire);

		// SniperZoomin
		EnhancedInputComp->BindAction(sniperZoominAction, ETriggerEvent::Triggered, this, &ATPSCharacter::SniperZoomin);

		// RunAction
		EnhancedInputComp->BindAction(runAction, ETriggerEvent::Triggered, this, &ATPSCharacter::InputRun);
	}
}

void ATPSCharacter::MoveForward(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDir, Movement);
	}
}

void ATPSCharacter::MoveRight(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDir, Movement);
	}
}

void ATPSCharacter::TurnPitch(const FInputActionValue& Value)
{
	float Turn = -(Value.Get<float>());
	if (Controller != nullptr)
	{
		AddControllerPitchInput(Turn);
	}
}

void ATPSCharacter::TurnYaw(const FInputActionValue& Value)
{
	float Turn = Value.Get<float>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(Turn);
	}
}

void ATPSCharacter::InputFire(const FInputActionValue& Value)
{
	// �Ѿ� �߻� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

	// ī�޶� ����ũ ���
	auto controller = GetWorld()->GetFirstPlayerController();
	if (controller)
		controller->PlayerCameraManager->StartCameraShake(cameraShake);

	// ������ �ִϸ��̼� ���
	auto anim = Cast<UCharacterAnim>(GetMesh()->GetAnimInstance());
	if (anim)
		anim->PlayAttackAnim();
	if (!tpsCamComp)
		return;
	// LineTrace ���� ��ġ
	FVector startPos = tpsCamComp->GetComponentLocation();
	// LineTrace ���� ��ġ
	FVector endPos = startPos + tpsCamComp->GetForwardVector() * 5000;
	// LineTrace �浹 ������ ���� ����
	FHitResult hitInfo;
	// �浹 �ɼ� ���� ����
	FCollisionQueryParams params;
	// �ڱ��ڽ��� �浹���� ����
	params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);

	if (bHit)
	{
		// �浹ó�� -> �Ѿ� ���� ȿ�� ����
		FTransform bulletTrans;
		// �ε��� ��ġ �Ҵ�
		bulletTrans.SetLocation(hitInfo.ImpactPoint);
		// �Ѿ� ���� ȿ�� �ν��Ͻ� ����
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

		auto hitComp = hitInfo.GetComponent();
		// �浹�� ������Ʈ�� �����ϸ鼭, ������ ����Ǿ� �ִٸ�
		if (hitComp && hitComp->IsSimulatingPhysics())
		{
			FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
			hitComp->AddForce(force);
		}

		// �ε��� ����� Enemy ���� Ȯ��
		auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
		if (enemy)
		{
			auto enemyFSM = Cast<UEnemyFSM>(enemy);
			if (enemyFSM)
				enemyFSM->OnDamageProcess();
		}
	}
}

void ATPSCharacter::SniperZoomin(const FInputActionValue& Value)
{

	bool SniperZoomin = Value.Get<bool>();
	if (SniperZoomin)
	{
		sniperUI->AddToViewport();
		tpsCamComp->SetFieldOfView(45.0f);
		crosshairUI->RemoveFromParent();
	}
	else
	{
		sniperUI->RemoveFromParent();
		tpsCamComp->SetFieldOfView(90.0f);
		crosshairUI->AddToViewport();
	}
}

void ATPSCharacter::InputRun(const FInputActionValue& Value)
{
	auto movement = GetCharacterMovement();
	if (movement == nullptr)
		return;

	bool isRun = Value.Get<bool>();
	if (isRun)
	{
		movement->MaxWalkSpeed = runSpeed;
	}
	else
	{
		movement->MaxWalkSpeed = walkSpeed;
	}
}

void ATPSCharacter::OnHitEvent()
{
	hp--;
	// ���� ��ü ��������GetMesh
	UCharacterAnim* anim = nullptr;
	anim = Cast<UCharacterAnim>(GetMesh()->GetAnimInstance());
	if (anim)
	{
		FString sectionName = FString::Printf(TEXT("Damage"));
		anim->PlayDamageAnim(FName(*sectionName));
		anim->damaged = true;;
	}

	if (hp <= 0)
	{
		OnGameOver();
	}
}

void ATPSCharacter::OnGameOver()
{
	APlayerController* t = Cast<APlayerController>(Controller);
	t->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

