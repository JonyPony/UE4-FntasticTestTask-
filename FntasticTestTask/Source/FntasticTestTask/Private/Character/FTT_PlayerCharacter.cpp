// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FTT_PlayerCharacter.h"
#include "Character/FTT_PlayerController.h"
#include "Character/FTT_PlayerInputActions.h"

#include "TargetHUD_WD/FTT_TargetHUDWDActor.h"

#include "InteractiveObjects/FTT_InteractiveObjectInterface.h"

//...........................Components include..............................//

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractiveObjects/FTT_InteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//...........................................................................//



AFTT_PlayerCharacter::AFTT_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->bMaintainHorizontalGroundVelocity = false;

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

void AFTT_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionComponent->OnPotentialForInteractChangedBind.AddDynamic(this, &AFTT_PlayerCharacter::OnPotentialForInteractChanged);

	if (TargetWDActorClass != nullptr)
	{
		FActorSpawnParameters LTargetWDActorSpawnParams;
		LTargetWDActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		TargetWDActor = GetWorld()->SpawnActor<AFTT_TargetHUDWDActor>(TargetWDActorClass, LTargetWDActorSpawnParams);
	}
}

void AFTT_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFTT_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<AFTT_PlayerController>(NewController);

	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("UpdateTargetView"));
	GetWorldTimerManager().SetTimer(UpdateTargetViewTimerHandle, TimerDel, TargetUpdateInterval, true);
}

void AFTT_PlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	PlayerController = nullptr;

	GetWorldTimerManager().ClearTimer(UpdateTargetViewTimerHandle);
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

	//......................................//
}



//....................................................Methods to bind with Input Actions.........................................................................//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//.....................Moving..................................//

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

	FRotator LookRotate = FRotator(0, GetControlRotation().Yaw, 0);
	FVector ForwardVector = FRotationMatrix(LookRotate).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, AxisValue);
}

void AFTT_PlayerCharacter::LookRight(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue)) this->AddControllerYawInput(AxisValue * MouseSensitivity);
}

void AFTT_PlayerCharacter::LookUp(float AxisValue)
{
	if (!FMath::IsNearlyZero(AxisValue)) this->AddControllerPitchInput(AxisValue * MouseSensitivity);
}

//............................................................//



//.....................Gameplay Actions.......................//

void AFTT_PlayerCharacter::OnPressInteract()
{
	if (IsValid(InteractionComponent)) 	InteractionComponent->InteractWithPotentialForInteract();
}

//............................................................//



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//...............................................................................................................................................................//






void AFTT_PlayerCharacter::OnPotentialForInteractChanged(AActor* InteractiveActor, bool WasRemoved)
{
	if (!IsValid(PlayerController) || !IsValid(InteractiveActor)) return;

	if (InteractiveActor->GetClass()->ImplementsInterface(UFTT_InteractiveObjectInterface::StaticClass()))
	{
		IFTT_InteractiveObjectInterface::Execute_TargetInteractiveObject(InteractiveActor, !WasRemoved);
	}

	if (!IsValid(TargetWDActor)) return;

	if (InteractionComponent->GetPotentialForInteractObjects().Num() == 0 || !InteractionComponent->GetCanInteractWithActor(InteractiveActor))
	{
		TargetWDActor->HideTarget();
		return;
	}

	TargetWDActor->ShowTargetByActor(InteractiveActor, FirstPersonCameraComponent);
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
		InteractionComponent->GetCanTargetedActor(LTargetActor) &&
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



//.....................TargetView/Math.......................//



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

//............................................................//