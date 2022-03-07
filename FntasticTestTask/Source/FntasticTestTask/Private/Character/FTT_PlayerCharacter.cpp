// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FTT_PlayerCharacter.h"
#include "Character/FTT_PlayerInputActions.h"

#include "Components/CapsuleComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/GameUserSettings.h"

#include "GameFramework/CharacterMovementComponent.h"



AFTT_PlayerCharacter::AFTT_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->bMaintainHorizontalGroundVelocity = false;

	GetCharacterMovement()->GravityScale = 1.7;
	GetCharacterMovement()->MaxAcceleration = 900;
	GetCharacterMovement()->MaxStepHeight = 20.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(30);
	GetCharacterMovement()->GroundFriction = 6.9;

	GetCharacterMovement()->BrakingFrictionFactor = 0.5;
	GetCharacterMovement()->BrakingDecelerationWalking = 420.0f;

	GetCharacterMovement()->JumpZVelocity = 480;
	GetCharacterMovement()->AirControl = 0.1;

	GetCharacterMovement()->BrakingDecelerationFlying = 1000.0f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	GetMesh()->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	bCanAffectNavigationGeneration = true;
}

void AFTT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFTT_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFTT_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//................Moving................//

	PlayerInputComponent->BindAxis(FPlayerInputActionNames::MoveForwardAxis, this, &AFTT_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FPlayerInputActionNames::MoveRightAxis, this, &AFTT_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis(FPlayerInputActionNames::LookRightAxis, this, &AFTT_PlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis(FPlayerInputActionNames::LookUpAxis, this, &AFTT_PlayerCharacter::LookUp);
}



void AFTT_PlayerCharacter::MoveForward(float AxisValue)
{
	if (FMath::IsNearlyZero(AxisValue)) return;

	FVector ForwardVector;

	FRotator LookRotate = FRotator(0, GetControlRotation().Yaw, 0);
	ForwardVector = FRotationMatrix(LookRotate).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardVector, AxisValue);

}

void AFTT_PlayerCharacter::MoveRight(float AxisValue)
{
	if (FMath::IsNearlyZero(AxisValue)) return;

	if (!GetMovementComponent()->IsSwimming())
	{
		FRotator LookRotate = FRotator(0, GetControlRotation().Yaw, 0);
		FVector ForwardVector = FRotationMatrix(LookRotate).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardVector, AxisValue);
	}
}

void AFTT_PlayerCharacter::LookRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		this->AddControllerYawInput(AxisValue * MouseSensitivity);
	}
}

void AFTT_PlayerCharacter::LookUp(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		this->AddControllerPitchInput(AxisValue * MouseSensitivity);
	}
}
