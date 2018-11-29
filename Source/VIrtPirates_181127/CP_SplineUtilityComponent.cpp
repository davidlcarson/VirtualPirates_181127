// Fill out your copyright notice in the Description page of Project Settings.

#include "CP_SplineUtilityComponent.h"

#include "Runtime/Core/Public/misc/Paths.h" //FPath

// Sets default values for this component's properties
/**********************************************************************/
UCP_SplineUtilityComponent::UCP_SplineUtilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	return;
}

// Called when the game starts
/**********************************************************************/
void UCP_SplineUtilityComponent::BeginPlay()
{
	Super::BeginPlay();

	///dc
	//Store a pointer to the spline component that is our sibling.
	AActor* Actor = GetOwner();
	SplineComponent = GetOwner()->FindComponentByClass<USplineComponent>();	

	//Store the number of points in the spline
	if (SplineComponent != nullptr) 
		m_numberSplinePoints = SplineComponent->GetNumberOfSplinePoints();
	else
		UE_LOG(LogTemp, Warning, TEXT("No Spline Component Found."));

	//Any requests?

	//Read before write in case we want to save
	//..a new combined spline
	if (ReadSpline == true) {
		readSplineFromFile();
	}

	if (WriteSpline == true) {
		writeSplineToFile();
	}

	return;
}


// Called every frame
/*******************************************************************/
void UCP_SplineUtilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

///Saves the current spline to a .csv file
/********************************************************/
void UCP_SplineUtilityComponent::writeSplineToFile(void)
{
	if (!fillWriteStringFilename())
		return;

	//open a file for csv writing
	FILE* pFile = _wfopen(m_stringFilename, L"wt");

	fprintf(pFile, "%d,,,\n", m_numberSplinePoints);

	FVector vLocation;
	FVector vTangent;

	int coordinateSpace = 0; //local
	if (UseWorldSpace == true)
		coordinateSpace = 1; //world
	
	for (int32 i = 0; i < m_numberSplinePoints; i++) {
		SplineComponent->GetLocationAndTangentAtSplinePoint(i, OUT vLocation, OUT vTangent, (ESplineCoordinateSpace::Type)coordinateSpace);
		fprintf(pFile, "%f,%f,%f,%f,%f,%f,\n", vLocation.X, vLocation.Y, vLocation.Z, vTangent.X, vTangent.Y, vTangent.Z);
	}

	fclose(pFile);

	return;
}

//Read the spline from a .csv file and make our spline match.
//THIS HAS TO BE SAVED during run to persist.
/********************************************************/
void UCP_SplineUtilityComponent::readSplineFromFile(void)
{
	//make sure there's a filename to read from...
	if (!fillReadStringFilename())
		return;
	//TODO: emit a warning

	//open the file
	FILE* pFile = _wfopen(m_stringFilename, L"rt");
	if (pFile == NULL)
		return;
	//TODO: emit a warning

	//get first string in the file. Will be number splines, some commas and a newline
	char maxString[32];
	fgets(maxString, 32, pFile);

	for (int i = 0; i < 32; i++) {
		if (maxString[i] == ',') {
			maxString[i] = '\0';
			break;
		}
	}

	//store the number of points in the file
	int32 numberPoints = atoi(maxString);

	FVector vLocation;
	FVector vTangent;

	int curPointIndex = 0;
	if (Append == true) {		
		//Get OUR current number of points
		curPointIndex = m_numberSplinePoints;
	}
	else
		//Not appending: Clear our current points (don't need to update)
		SplineComponent->ClearSplinePoints(false);
	
	int coordinateSpace = 0; //local
	if (UseWorldSpace == true)
		coordinateSpace = 1; //world

	//read in all the points
	for (int i = 0; i < numberPoints; i++)
	{
		//points in the file are two vectors. Location and Tangent
		getNextPoint(&vLocation, &vTangent, pFile);
		//add at index will shove down any files currently at that index?
		//We use world space
		//don't update each time (false)
		SplineComponent->AddSplinePointAtIndex(vLocation, curPointIndex, (ESplineCoordinateSpace::Type)coordinateSpace, false);
		SplineComponent->SetTangentAtSplinePoint(curPointIndex, vTangent, (ESplineCoordinateSpace::Type)coordinateSpace, false);
		curPointIndex++;
	}
	fclose(pFile);
	pFile = NULL;

	//Now updaet
	SplineComponent->UpdateSpline();

	//NOTE: Have to eject (F8) and 'Save Modified' if you want to keep this new spline!!
	
	return;
}

//Read the next Point's worth of data from the file
/**************************************************************************************/
bool UCP_SplineUtilityComponent::getNextPoint(FVector* pLocation, FVector* pTangent, FILE* pFile)
{
	/// Each point is one line in the csv file. (Two vectors, six floats);

	//get next line of text. Should be 6 floats
	char maxString[256];
	fgets(maxString, 256, pFile);

	int newPos = 0; //store our current offset into the string
	float curFloat = 0.0f; //holds current float
	FVector vector;  //holds current vector

	newPos += getNextFloat(&maxString[newPos], &curFloat);
	vector.X = curFloat;
	newPos += getNextFloat(&maxString[newPos], &curFloat);
	vector.Y = curFloat;
	newPos += getNextFloat(&maxString[newPos], &curFloat);
	vector.Z = curFloat;

	*pLocation = vector;

	newPos += getNextFloat(&maxString[newPos], &curFloat);
	vector.X = curFloat;
	newPos += getNextFloat(&maxString[newPos], &curFloat);
	vector.Y = curFloat;
	newPos += getNextFloat(&maxString[newPos], &curFloat);
	vector.Z = curFloat;

	*pTangent = vector;

	return true;
}

//Read the next float in the line. The pString should be pointing to it.
/************************************************************************************/
int UCP_SplineUtilityComponent::getNextFloat(char* pString, float* pFloat)
{
	int numRead = 0;

	while (pString[numRead] != ',') {
		numRead++;
	}
	pString[numRead] = '\0';

	*pFloat = atof(pString);

	//bump numRead by one because of '/0'
	return numRead+1;
}

//Appends the name of the file to the Config Directory path
/**********************************************************************/
bool UCP_SplineUtilityComponent::fillWriteStringFilename(void)
{
	//make sure there's a filename filled in
	if (WriteFileName == "") {
		UE_LOG(LogTemp, Error, TEXT("Write Requested but no Filename given."));
		return false;
	}

	//get the directory where config files are stored
	FString dir = FPaths::ProjectConfigDir();
	wcscpy(m_stringFilename, *dir);

	//append the file name to it
	int32 len = wcslen(*dir);
	wcscpy(&m_stringFilename[len], *WriteFileName);

	//m_stringDirectory is now good to go
	return true;
}

/**********************************************************************/
bool UCP_SplineUtilityComponent::fillReadStringFilename(void)
{
	//make sure there's a filename filled in
	if (ReadFileName == "") {
		UE_LOG(LogTemp, Error, TEXT("Read Requested but no Filename given."));
		return false;
	}

	//get the directory where config files are stored
	FString dir = FPaths::ProjectConfigDir();
	wcscpy(m_stringFilename, *dir);

	//append the file name to it
	int32 len = wcslen(*dir);
	wcscpy(&m_stringFilename[len], *ReadFileName);

	//m_stringDirectory is now good to go
	return true;
}
