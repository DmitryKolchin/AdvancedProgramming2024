// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HPPotionOptimisation/UI/PlayerIconWidget.h"
#include "PlayerCharacter.generated.h"

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
	int32 CurrentHealth;

	UPROPERTY()
	int32 MaxHealth;

	UPROPERTY( EditDefaultsOnly, Category="UI" )
	TSoftClassPtr<UPlayerIconWidget> PlayerIconWidgetClassSoftClassPtr;

	UPROPERTY()
	UPlayerIconWidget* PlayerIconWidget;

public:
	/* Initialization from the provided Data Asset */
	UFUNCTION( BlueprintCallable )
	void Init(TSoftObjectPtr<UCharacterInfoDataAsset> CharacterInfoDataAssetSoftPtr);

	// GETTERS
	UFUNCTION( BlueprintPure )
	FText GetCharacterName() const;

	UFUNCTION( BlueprintPure )
	int32 GetCurrentHealth() const;

	UFUNCTION( BlueprintPure )
	int32 GetMaxHealth() const;

	UFUNCTION( BlueprintPure )
	UPlayerIconWidget* GetPlayerIconWidget() const;

	/* Function that adds health to the player, and clamps it according to the Max Health parameter value*/
	void AddHealth(int32 HealthToAdd);
};
