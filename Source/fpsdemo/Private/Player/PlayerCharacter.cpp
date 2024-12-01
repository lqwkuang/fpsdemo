// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"

#include<EnhancedInputSubsystems.h>
#include<EnhancedInputComponent.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("cameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 5.0f;
	CameraBoom->SetRelativeRotation(FRotator(0, 0, 0));

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("playerCamera");
	PlayerCamera->SetupAttachment(CameraBoom);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (const ULocalPlayer* player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player);
		if (DefaultMapping)
		{
			Subsystem->AddMappingContext(DefaultMapping,0);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	FVector2D movevector = value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, movevector.X);
		AddMovementInput(RightDirection, movevector.Y);
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookvector = value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(lookvector.X);
		AddControllerPitchInput(lookvector.Y);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhanceInputcomponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhanceInputcomponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhanceInputcomponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	}
}

