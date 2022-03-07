// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/FTT_BaseInteractiveObject.h"

#include "InteractiveObjects/FTT_InteractionComponent.h"

// Sets default values
AFTT_BaseInteractiveObject::AFTT_BaseInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFTT_BaseInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	
}


