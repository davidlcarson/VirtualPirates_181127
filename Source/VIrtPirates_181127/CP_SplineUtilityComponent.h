// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Classes/Components/SplineComponent.h" //spline component

#include "CP_SplineUtilityComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIRTPIRATES_181127_API UCP_SplineUtilityComponent : public UActorComponent
{
	GENERATED_BODY()	

public:	
	// Sets default values for this component's properties
	UCP_SplineUtilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//private vars
	//Holds path and filename for current read/write
	wchar_t m_stringFilename[256];

	//points in current spline
	int32 m_numberSplinePoints = 0;

	//private methods
	bool fillWriteStringFilename();
	bool fillReadStringFilename();
	void writeSplineToFile();
	void readSplineFromFile();
	bool getNextPoint(FVector* pLocation, FVector* pTangent, FILE* pFile);
	int getNextFloat(char* pString, float* pFloat);

public:	
	//public member vars
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere)
	bool ReadSpline = false;

	UPROPERTY(EditAnywhere)
	FString ReadFileName = "";

	UPROPERTY(EditAnywhere)
	bool UseWorldSpace = false;

	UPROPERTY(EditAnywhere)
	bool Append = false;

	UPROPERTY(EditAnywhere)
	bool WriteSpline = false;

	UPROPERTY(EditAnywhere)
	FString WriteFileName = "";

	//-- Public Functions
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};

//
//	This class can read and write spline files from a .csv file.
//	The format of the file is a custom one. 
//
//	The file has to be stored in the Config directory of the current project.
//
//	It can create a new spline from a file, append points to the current spline
//	(Both should be in World Space w/ spline @ 0/0/0), or write the current spline to a file.
//
//	This is meant to be added as a component to a Spline_Provider instance, but shouold work
//	with any actor that has a spline component
//
