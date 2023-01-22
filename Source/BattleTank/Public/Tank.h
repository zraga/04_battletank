// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"//must be at bottom

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//Called by the engine when actor damage is dealt 
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EvenInstigator, AActor * DamageCauser);
	
	//returns health as a % of starting health, between 0 to 1
	UFUNCTION(BlueprintPure, Category= "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;//intialised in begin play 

	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;
};
