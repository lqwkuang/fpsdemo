// Fill out your copyright notice in the Description page of Project Settings.


#include "Playeranima.h"
#include"Player/PlayerCharacter.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Kismet/KismetMathLibrary.h"


void UPlayeranima::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (PlayerCharacter)
	{
		PlayerCharacterMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayeranima::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (PlayerCharacterMovement)
	{
		speed = UKismetMathLibrary::VSizeXY(PlayerCharacterMovement->Velocity);
	}
}
