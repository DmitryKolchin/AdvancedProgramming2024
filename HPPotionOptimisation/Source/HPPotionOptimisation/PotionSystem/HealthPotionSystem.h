// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HealthPotionSystem.generated.h"

class UPlayerCharacter;



USTRUCT( BlueprintType )
struct FOverTimeHealingPotion
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FString PotionName;

	/** How many health points is restored instantly */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float InstantHealingValue;

	/** Which percent of max health is restored over time */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float MaxHealthPercentageToHealOverTime;

	/** How long the healing effect lasts in total*/
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float TotalHealingDuration;

	/** How long the healing effect has been active */
	UPROPERTY( )
	float ElapsedHealingDuration;

	float GetTotalHealingValue(const float MaxHealth) const
	{
		return InstantHealingValue + MaxHealth * MaxHealthPercentageToHealOverTime;
	}

	float GetHealingValuePerTick(const float MaxHealth, const float DeltaTime)
	{
		return (MaxHealth * MaxHealthPercentageToHealOverTime / TotalHealingDuration) * DeltaTime;
	}
};



USTRUCT( BlueprintType )
struct FPotion
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString PotionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 HealingValue;
};

UCLASS(BlueprintType)
class HPPOTIONOPTIMISATION_API UHealthPotionSystem : public UObject
{
	GENERATED_BODY()

private:
	TArray<FPotion> Potions;

	TArray<FOverTimeHealingPotion> OverTimeHealingPotions;

public:
	UFUNCTION( BlueprintCallable )
	void AddPotion(const FPotion& NewPotion);

	UFUNCTION(BlueprintCallable)
	void AddOverTimeHealingPotion(const FOverTimeHealingPotion& NewOverTimeHealingPotion);

	UFUNCTION( BlueprintCallable, Category = "HealthPotionSystem" )
	void HealPlayers(TArray<UPlayerCharacter*> Players);

	UFUNCTION(BlueprintCallable, Category= "HealthPotionSystem")
	void HealPlayersWithOverTimePotions(TArray<UPlayerCharacter*> Players);
};
