// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FTT_PlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"

AFTT_PlayerController::AFTT_PlayerController()
{

}




FVector2D AFTT_PlayerController::GetViewportHalfSize() const
{
	int32 XSize;
	int32 YSize;

	GetViewportSize(XSize, YSize);

	return FVector2D(XSize / 2, YSize / 2);
}

bool AFTT_PlayerController::GetHitResultAtScreenRadius(const FVector2D& ScreenPosition, float Radius, ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	if (GetHUD() != NULL && GetHUD()->GetHitBoxAtCoordinates(ScreenPosition, true))
	{
		return false;
	}


	FVector WorldOrigin;
	FVector WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenPosition, WorldOrigin, WorldDirection) == true)
	{
		FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(ClickableTrace), bTraceComplex);

		return GetWorld()->SweepSingleByChannel(
			HitResult, WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, FQuat::Identity,
			TraceChannel, FCollisionShape::MakeSphere(Radius), FCollisionQueryParams(SCENE_QUERY_STAT(ClickableTrace), bTraceComplex)
		);
	}

	return false;
}
