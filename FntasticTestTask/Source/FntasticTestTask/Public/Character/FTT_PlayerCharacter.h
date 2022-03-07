// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FTT_PlayerCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;


UCLASS()
class FNTASTICTESTTASK_API AFTT_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()



	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

public:
	AFTT_PlayerCharacter();

protected:
	virtual void BeginPlay() override;


//c++ public methods
public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



//..........................................Methods to bind with Input Actions.................................................................//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//..........Moving..............//

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookRight(float AxisValue);
	void LookUp(float AxisValue);

	void OnPressWalk();
	void OnReleaseWalk();

	void OnPressSprint();
	void OnReleaseSprint();

	void OnPressCrouch();
	void OnReleaseCrouch();

	//..............................//


	//.....Gameplay Actions.........//

	void OnPressInteract();

	void OnPressParkurAction();

	void OnPressUseQuickSlot(int SlotIndex);

	//..............................//


	//.........Camera Actions.......//

	void ChangeCameraDistance(float AxisValue);

	void OnPressSwitchTargetEnabled();
	void OnPressNextTarget();

	//..............................//

	/* MouseSensitivity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MouseSensitivity = 1.f;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//.............................................................................................................................................//

};
