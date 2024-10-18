// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HealthPotionSystem.generated.h"

class UPlayerCharacter;

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

public:
	UFUNCTION( BlueprintCallable )
	void AddPotion(const FPotion& NewPotion);

	UFUNCTION( BlueprintCallable, Category = "HealthPotionSystem" )
	void HealPlayers(TArray<UPlayerCharacter*> Players);
};
