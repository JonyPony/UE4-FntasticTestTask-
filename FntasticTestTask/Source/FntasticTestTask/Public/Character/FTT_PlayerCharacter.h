// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FTT_PlayerCharacter.generated.h"

class AFTT_TargetHUDWDActor;

/*
	Base class for player. Other classes will be in BP.
*/
UCLASS()
class FNTASTICTESTTASK_API AFTT_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()



//constructor
public:

	AFTT_PlayerCharacter();



//c++ public methods
public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;


//..........................................Methods to bind with Input Actions.................................................................//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//..........Moving..............//

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void LookRight(float AxisValue);
	void LookUp(float AxisValue);

	//..............................//


	//.....Gameplay Actions.........//

	void OnPressInteract();

	//..............................//


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//.............................................................................................................................................//





//c++ protected methods
protected:

	virtual void BeginPlay() override;


	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;


	//....................InteractiveObjects Interface......................//
	UFUNCTION()
		void OnPotentialForInteractChanged(AActor* InteractiveActor, bool WasRemoved);

	//......................................................................//


//c++ private methods
private: 

	//.....................TargetView/Math.......................//

	float GetAngleBetweenActors(AActor* A, AActor* B);
	float GetAngleBetweenVectors(const FVector& VectorA, const FVector& VectorB);
	float GetAngleInRadiansBetweenVectors(const FVector& VectorA, const FVector& VectorB);

	//............................................................//

//c++ private values
private:

	FTimerHandle UpdateTargetViewTimerHandle;

	AFTT_TargetHUDWDActor* TargetWDActor = nullptr;


//Blueprint public methods
public:


	//..............................................TargetItem..................................................//

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
		void UpdateTargetView();

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
		void SetTargetByScreenCenter();

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter|TargetItem")
		void ClearTarget();

	//..........................................................................................................//



//Blueprint values
public:

	/*
		Speed of camera movment.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter | Settings")
		float MouseSensitivity = 1.f;


	/*
		Class of the container of object target widget.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacter | TargetWDActor")
		TSubclassOf<AFTT_TargetHUDWDActor> TargetWDActorClass = nullptr;

	//..............................................TargetItem........................................//

	/*
		If false then target system for interactive objects will be disabled.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | TargetItem")
		bool IsUpdateInteractiveEnabled = true;
	/*
		Time between searching new interactive item.
		In seconds.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter | TargetItem")
		float TargetUpdateInterval = 0.2;
	/*
		Radius of circle in the center of the screen for target system by screen center.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", UIMin = "1.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter | TargetItem")
		float ScreenTargetRadius = 10.0f;
	/*
		Radius for searching interactive objects.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter | TargetItem")
		float TargetRadius = 200.0f;
	/*
		Maximum angle to target an item between a character and an object.
		In degrees.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "180.0", UIMax = "180.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter | TargetItem")
		float MaxAngleBetweenPlayerAndObjectToTarget = 90.0f;
	/*
		The maximum angle between the object and the camera to target it.
		In degrees.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "180.0", UIMax = "180.0", EditCondition = "IsUpdateInteractiveEnabled"), Category = "PlayerCharacter | TargetItem")
		float MaxAngleToTargetObject = 13.0f;

	//................................................................................................//



	UPROPERTY(BlueprintReadOnly, Category = "PlayerCharacter")
		class AFTT_PlayerController* PlayerController = nullptr;



	//.................................Components.....................................................//

	UPROPERTY(BlueprintReadOnly, Category = "PlayerCharacter | Components")
		class UFTT_InteractionComponent* InteractionComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerCharacter | Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent = nullptr;

	//................................................................................................//


};
