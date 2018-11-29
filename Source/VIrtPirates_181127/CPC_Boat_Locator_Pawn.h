// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SplineComponent.h"
#include "Components/SceneCaptureComponent.h"

#include "CPC_Boat_Locator_Pawn.generated.h"

UCLASS()
class VIRTPIRATES_181127_API ACPC_Boat_Locator_Pawn : public APawn
{
	GENERATED_BODY()

private:
	bool bPaused = false;
	float CurrentSplineLength = 0;

	UPROPERTY()
	USplineComponent* pSpline;

	//--- private methods
	void updatePosition();

protected:
	//--- protected variables
	UPROPERTY(BlueprintReadWrite)
	int32 BoatID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDistance = 0;

	//This is stored primarily for debug display
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentBobRate = 0;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	//--- protected methods

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Constructor
	ACPC_Boat_Locator_Pawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BLueprintCallable)
	float GetCurrentDistance() { return CurrentDistance; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentSpline(USplineComponent* pNewSpline, float startingPosition = 0);

	void SetBoatID(int32 ID) { BoatID = ID; }
	void SetCurrentDistance(float position) { CurrentDistance = position; }

	//set speed in cmps along spline
	UFUNCTION(BlueprintCallable)
	void SetSpeed(float BoatSpeed) {CurrentSpeed = BoatSpeed;} 

	//This routine implemented in BP Derived AS EVENT
	UFUNCTION(BlueprintImplementableEvent, Category = "Output")
	void SetBobRate(float rate); // = 0

	UFUNCTION(BlueprintCallable)
	void PauseBoat(bool pause) { bPaused = pause; }
};
