// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h" 

#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;	
}

/*

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	//DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce() {
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
}
*/

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	float CurrentThrottle = FMath::Clamp<float>(Throttle + Throttle, -1, 1);
	DriveTrack(CurrentThrottle);

}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
    auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel:Wheels){

		Wheel->AddDrivingForce(ForcePerWheel);
	}

	//auto ForceLocation = GetComponentLocation();
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

TArray<ASprungWheel*>UTankTrack::GetWheels()const{
	//UE_LOG(LogTemp, Warning, TEXT("Aiming at"));
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child: Children) {


		//UE_LOG(LogTemp, Warning, TEXT(" im working "));

		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		//UE_LOG(LogTemp, Warning, TEXT(" Spawn point: %s"), *SpawnPointChild->GetFName().ToString());

		if (!SpawnPointChild) {
			continue;
		}

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		//UE_LOG(LogTemp, Warning, TEXT("Sprung wheel %s"), *SprungWheel->GetFName().ToString());

		
		if (!SprungWheel) {
			continue;	
		}

		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}