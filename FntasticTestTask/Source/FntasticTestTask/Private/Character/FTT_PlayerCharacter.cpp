// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FTT_PlayerCharacter.h"
#include "Character/FTT_PlayerController.h"
#include "Character/FTT_PlayerInputActions.h"


#include "GameFramework/GameUserSettings.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractiveObjects/FTT_InteractionComponent.h"
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


	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<UFTT_InteractionComponent>(TEXT("InteractionComponent")); 

	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FirstPersonCameraComponent);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	GetMesh()->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	bCanAffectNavigationGeneration = true;
}

void AFTT_PlayerCharacter::PossessedBy(AController* NewController)
{
	PlayerController = Cast<AFTT_PlayerController>(NewController);

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("UpdateTargetView"));
	GetWorldTimerManager().SetTimer(UpdateTargetViewTimerHandle, TimerDel, TargetUpdateInterval, true);
}


void AFTT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

float AFTT_PlayerCharacter::GetAngleBetweenActors(AActor* A, AActor* B)
{
	if (!IsValid(A) || !IsValid(B)) return 0.0f;

	FVector DirectionToTarget = B->GetActorLocation() - A->GetActorLocation();
	DirectionToTarget.Z = A->GetActorForwardVector().Z;
	return GetAngleBetweenVectors(DirectionToTarget, A->GetActorForwardVector());
}

float AFTT_PlayerCharacter::GetAngleBetweenVectors(const FVector& VectorA, const FVector& VectorB)
{
	return FMath::RadiansToDegrees(GetAngleInRadiansBetweenVectors(VectorA, VectorB));
}

float AFTT_PlayerCharacter::GetAngleInRadiansBetweenVectors(const FVector& VectorA, const FVector& VectorB)
{
	return FMath::Acos(FVector::DotProduct(VectorA, VectorB) / (VectorA.Size() * VectorB.Size()));
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

	//......................................//



	//..........Gameplay Actions............//

	PlayerInputComponent->BindAction(FPlayerInputActionNames::InteractionAction, IE_Pressed, this, &AFTT_PlayerCharacter::OnPressInteract);
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



void AFTT_PlayerCharacter::OnPressInteract()
{
	if (!IsValid(InteractionComponent)) return;

	InteractionComponent->InteractWithPotentialForInteract();
}






void AFTT_PlayerCharacter::UpdateTargetView()
{
	if (!IsUpdateInteractiveEnabled) return;

	SetTargetByScreenCenter();

}

void AFTT_PlayerCharacter::SetTargetByScreenCenter()
{
	if (!IsValid(PlayerController)) return;

	FVector2D ScreenPosition = PlayerController->GetViewportHalfSize();

	FHitResult LHitRes;
	bool LIsHit = PlayerController->GetHitResultAtScreenRadius(ScreenPosition, ScreenTargetRadius, ECollisionChannel::ECC_Visibility, true, LHitRes);
	AActor* LTargetActor = LHitRes.Actor.Get();

	if (
		IsValid(LTargetActor) && InteractionComponent->GetCanInteractWithActor(LTargetActor) &&
		FMath::Abs<float>(GetAngleBetweenActors(this, LTargetActor)) <= MaxAngleBetweenPlayerAndObjectToTarget
		)
	{
		InteractionComponent->AddToPotentialInteract(LTargetActor);
		return;
	}

	ClearTarget();
}

void AFTT_PlayerCharacter::ClearTarget()
{
	if (IsValid(InteractionComponent)) InteractionComponent->RemoveAllFromPotentialInteract();
}

