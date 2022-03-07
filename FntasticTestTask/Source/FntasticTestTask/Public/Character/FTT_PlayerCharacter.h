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



	virtual void PossessedBy(AController* NewController) override;
	//virtual void UnPossessed() override;

	/* MouseSensitivity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MouseSensitivity = 1.f;


//c++ protected methods
protected:

	virtual void BeginPlay() override;

private: 

	float GetAngleBetweenActors(AActor* A, AActor* B);
	float GetAngleBetweenVectors(const FVector& VectorA, const FVector& VectorB);
	float GetAngleInRadiansBetweenVectors(const FVector& VectorA, const FVector& VectorB);
	
private:

	FTimerHandle UpdateTargetViewTimerHandle;


//Blueprint public methods
public:

//..............................................TargetItem..................................................//

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
		void UpdateTargetView();

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
		void SetTargetByScreenCenter();
	//UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
	//	void SetTargetByCameraView();

	//UFUNCTION(NetMulticast, Reliable, Category = "PlayerCharacter|TargetItem")
	//	void TargetIteractiveItemServerToAll(AActor* InteractiveActor, bool WasRemoved);
	//	void TargetIteractiveItemServerToAll_Implementation(AActor* InteractiveActor, bool WasRemoved);

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
		void ClearTarget();

//..........................................................................................................//


//Blueprint values
public:

	//..............................................TargetItem........................................//

	/*
		If false then target system for interactive objects will be disabled.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter|TargetItem")
		bool IsUpdateInteractiveEnabled = true;
	/*
		Time between searching new interactive item.
		In seconds.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter|TargetItem")
		float TargetUpdateInterval = 0.2;
	/*
		Radius of circle in the center of the screen for target system by screen center.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", UIMin = "1.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter|TargetItem")
		float ScreenTargetRadius = 10.0f;
	/*
		Radius for searching interactive objects.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter|TargetItem")
		float TargetRadius = 200.0f;
	/*
		Maximum angle to target an item between a character and an object.
		In degrees.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "180.0", UIMax = "180.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter|TargetItem")
		float MaxAngleBetweenPlayerAndObjectToTarget = 90.0f;
	/*
		The maximum angle between the object and the camera to target it.
		In degrees.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "180.0", UIMax = "180.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter|TargetItem")
		float MaxAngleToTargetObject = 13.0f;

	//................................................................................................//




	UPROPERTY(BlueprintReadOnly, Category = "PlayerCharacter")
		class AFTT_PlayerController* PlayerController = nullptr;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseCharacter|Components")
		class UFTT_InteractionComponent* InteractionComponent;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//.............................................................................................................................................//

};
