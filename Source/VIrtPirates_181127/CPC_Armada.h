// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CPC_Boat_Locator_Pawn.h"
#include "CPC_Spline_Provider.h"
#include "Classes/Engine/DataTable.h"
#include "Engine.h"

#include "CPC_Armada.generated.h"

//------------ A structure for transferring data from armada to a boat ---+
USTRUCT(BlueprintType)
struct FArmada
{	
	GENERATED_USTRUCT_BODY()

	//Structure constructor. (empty)
	FArmada()
	{

	}

	//Tell boat its index
	UPROPERTY(BlueprintReadWrite, Category = "Boat")
	int32 BoatIndexID = -1;

	//pointer to spline boat's on
	UPROPERTY(BlueprintReadWrite, Category = "Boat")
	USplineComponent* pSpline = NULL;

	//Initial distance along spline
	UPROPERTY(BlueprintReadWrite, Category = "Boat")
	float Distance = 0.0f;

	//initial speed
	UPROPERTY(BlueprintReadWrite, Category = "Boat")
	float BoatSpeed = 0;

	//Initia Bob Rate (as factor)
	UPROPERTY(BlueprintReadWrite, Category = "Boat")
	float BobRateFactor = 0.5f;
};


//--------------- The Armada Class ----------------------+
UCLASS()
class VIRTPIRATES_181127_API ACPC_Armada : public AActor
{
	GENERATED_BODY()
	
private:

protected:
	//-- protected variables
	//The armada: An array of boats
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ACPC_Boat_Locator_Pawn*> Boat_Array;

	//An array of splines that boats can travel on. Currently only 1.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ACPC_Spline_Provider*> SplineProvider_Array; //just one for now

	//Default boat speed in normal conditions. Allows me to
	//..speed up or slow down the entire water-flow speed w/ one
	//..variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DefaultBoatSpeed = 80.0f; //in cps along spline: 80 = max at DLand (I think)

	//Allows us not to generate all 20 boats. For debug etc.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxBoatsWanted = 1;

	//-- Protected Methods
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Routine to initialize all the boats. Pertinent data is
	//..read from a .csv file. The FArmada structure is used
	//..to pass the data to each boat.
	UFUNCTION(BlueprintCallable)
	void initBoat(int whichBoat, FArmada pData);

public:	
	//Constructor
	ACPC_Armada();

	//Grant access to on of the boats in the array
	UFUNCTION(BlueprintCallable)
	ACPC_Boat_Locator_Pawn* GetBoat(int32 which) { return Boat_Array[which]; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Set the boat's speed from a RATE
	UFUNCTION(BlueprintCallable)
	void SetBoatAnimByRate(int32 which, float speedRate, float bobRate);
};


