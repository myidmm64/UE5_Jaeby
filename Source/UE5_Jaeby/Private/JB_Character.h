// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <EnhancedPlayerInput.h>
#include "JB_Character.generated.h"

UCLASS()
class AJB_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJB_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//actions
	void ForwardAction(const FInputActionValue& Value);
	void RightAction(const FInputActionValue& Value);
public:
	UPROPERTY(EditAnywhere, Category = Move)
	float moveAmount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* moveFowardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* moveRightAction;
};
