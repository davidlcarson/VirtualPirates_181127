// Fill out your copyright notice in the Description page of Project Settings.

#include "CPC_Boat_Locator_Pawn.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
/***************************************************/
ACPC_Boat_Locator_Pawn::ACPC_Boat_Locator_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	return;
}

// Called when the game starts or when spawned
/***************************************************/
void ACPC_Boat_Locator_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/***************************************************/
void ACPC_Boat_Locator_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPaused)
		return;

	//increase distance by (speed per sec * time slice)
	CurrentDistance += (CurrentSpeed * DeltaTime);

	if (CurrentDistance > CurrentSplineLength) {
		CurrentDistance -= CurrentSplineLength;
	}

	updatePosition();

	return;
}

// Called to bind functionality to input
/***************************************************/
void ACPC_Boat_Locator_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/***************************************************/
void ACPC_Boat_Locator_Pawn::updatePosition()
{
	if (pSpline == nullptr)
		return;

	FVector NewLocation;
	FRotator NewRotation;

	NewRotation = pSpline->GetRotationAtDistanceAlongSpline(CurrentDistance, 
		ESplineCoordinateSpace::World);
	NewLocation = pSpline->GetLocationAtDistanceAlongSpline(CurrentDistance,
		ESplineCoordinateSpace::World);

	bool bSuccess = SetActorLocationAndRotation(NewLocation, NewRotation);

	return;
}

/***************************************************/
void ACPC_Boat_Locator_Pawn::SetCurrentSpline(USplineComponent* pNewSpline,
	float startingPosition)
{
	pSpline = pNewSpline;

	if (pSpline != nullptr) {

		CurrentSplineLength = pSpline->GetSplineLength();
		CurrentDistance = startingPosition;

		updatePosition();
	}

	return;
}


