// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <InputAction.h>
#include "TPSCharacter.generated.h"

UCLASS()
class ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void TurnPitch(const FInputActionValue& Value);
	void TurnYaw(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);
	// 스나이퍼 조준
	void SniperZoomin(const FInputActionValue& Value);
	// 달리기 이벤트 처리 함수
	void InputRun(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable, Category = AnimEvent)
	void OnHitEvent();
	void OnGameOver();

	void Move(float deltaTime);
	void MoveStart(FVector dir);
	void MoveEnd();
	bool Moveable();
	void MoveInputReset();
public:
	bool isMoving = false;
	FVector startPosition;
	FVector endPosition;
	float moveTimer = 0.0f;
	bool moveInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	int initialHP = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HP)
	int hp = 0;
	// 스나이퍼 조준 중인지 여부
	bool bSniperZoomin = false;
	// 걷기 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moving)
	float walkSpeed = 200;
	// 달리기 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moving)
	float runSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moving)
	float moveTime = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moving)
	float moveableRatio = 0.85f;
	float currentSpeed = 200;

#pragma region /* Component*/
public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* tpsCamComp;

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent* sniperGunComp;
#pragma endregion

public:
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;

	UPROPERTY(EditDefaultsOnly, Category = CrosshairUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;

	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<class UCameraShakeBase> cameraShake;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* bulletSound;

public:
	// 스나이퍼 UI 위젯 인스턴스
	class UUserWidget* sniperUI;

	// 크로스헤어 UI 위젯 인스턴스
	class UUserWidget* crosshairUI;

#pragma region Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* tpsMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* moveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* moveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* turnPitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* turnYawAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* fireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* sniperZoominAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* runAction;
#pragma endregion
};
