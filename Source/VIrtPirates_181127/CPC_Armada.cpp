// Fill out your copyright notice in the Description page of Project Settings.

#include "CPC_Armada.h"

// Sets default values
/*************************************************/
ACPC_Armada::ACPC_Armada()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//UE_LOG(LogTemp, Warning, TEXT("At CPC_Armada Constructor"));

	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Armada_Root"));
	RootComponent = pRoot;

	//Init variables
	//Create an array of 20 boats (uninitialized)
	Boat_Array.SetNum(20);

	//There's only one boat spline in the world (for now)
	SplineProvider_Array.SetNum(1);

}

// Called when the game starts or when spawned
/*************************************************/
void ACPC_Armada::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("At CPC_Armada BeginPlay"));
}

// Called every frame
/*************************************************/
void ACPC_Armada::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma optimize("", off)
//Called by the Init Armada routine. Inits One Boat
/***************************************************************/
void ACPC_Armada::initBoat(int boatIndex, FArmada Data)
{
	ACPC_Boat_Locator_Pawn* pCurrentBoat = Boat_Array[boatIndex];
	if (pCurrentBoat == nullptr)
		return;

	//Give the boat its ID. Is also its index into array.
	pCurrentBoat->SetBoatID(Data.BoatIndexID);
	//Current Speed in cps along spline
	pCurrentBoat->SetSpeed(Data.BoatSpeed);

	//Bob Rate: Should call function in derived Blueprint
	pCurrentBoat->SetBobRate(Data.BobRateFactor);

	//Set the boat's spline, and starting position
	pCurrentBoat->SetCurrentSpline(Data.pSpline, Data.Distance);

	return;
}
#pragma optimize("", on)
#pragma optimize("", off)
/***************************************************************/
void ACPC_Armada::SetBoatAnimByRate(int32 which, float speedRate, float bobRate)
{
	Boat_Array[which]->SetSpeed(speedRate * DefaultBoatSpeed); 
	Boat_Array[which]->SetBobRate(bobRate);

	return;
}
#pragma optimize("", on)