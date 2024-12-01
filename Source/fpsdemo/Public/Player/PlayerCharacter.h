// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class FPSDEMO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	APlayerCharacter();
protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	//×é¼þ
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera",meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;
	//ÊäÈë Input
private:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
