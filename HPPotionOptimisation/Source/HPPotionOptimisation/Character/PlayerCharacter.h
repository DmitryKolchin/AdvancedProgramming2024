// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HPPotionOptimisation/UI/PlayerIconWidget.h"
#include "HPPotionOptimisation/PotionSystem/HealthPotionSystem.h"
#include "PlayerCharacter.generated.h"

struct FOverTimeHealingPotion;

class UHealingPotion;
class UCharacterInfoDataAsset;
class UPlayerIconWidget;
/**
 *
 */
UCLASS( BlueprintType, Blueprintable )
class HPPOTIONOPTIMISATION_API UPlayerCharacter : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FText CharacterName;

	UPROPERTY()
	float CurrentHealth;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY( EditDefaultsOnly, Category="UI" )
	TSoftClassPtr<UPlayerIconWidget> PlayerIconWidgetClassSoftClassPtr;

	UPROPERTY()
	UPlayerIconWidget* PlayerIconWidget;

	/** Over time healing potion */

	UPROPERTY()
	TOptional<FOverTimeHealingPotion> ActiveHealingPotion;



public:
	/* Initialization from the provided Data Asset */
	UFUNCTION( BlueprintCallable )
	void Init(TSoftObjectPtr<UCharacterInfoDataAsset> CharacterInfoDataAssetSoftPtr);

	// GETTERS
	UFUNCTION( BlueprintPure )
	FText GetCharacterName() const;

	UFUNCTION( BlueprintPure )
	float GetCurrentHealth() const;

	UFUNCTION( BlueprintPure )
	float GetMaxHealth() const;

	UFUNCTION( BlueprintPure )
	UPlayerIconWidget* GetPlayerIconWidget() const;

	/* Function that adds health to the player, and clamps it according to the Max Health parameter value*/
	void AddHealth(float HealthToAdd);

	void SetNewOverTimeHealingPotion(const FOverTimeHealingPotion& NewOverTimeHealingPotion);


private:
	void ApplyOverTimeHealingPotionPerTick();


};
