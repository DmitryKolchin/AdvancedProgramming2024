// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterInfoDataAsset.generated.h"

/**
 *
 */
UCLASS( BlueprintType )
class HPPOTIONOPTIMISATION_API UCharacterInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY( EditDefaultsOnly, Category="Character Info" )
	FText CharacterName;

	UPROPERTY( EditDefaultsOnly, Category="Character Info" )
	UTexture2D* CharacterIcon;

	UPROPERTY( EditDefaultsOnly, Category="Character Info|Health" )
	int32 MaxHealth = 100.f;

	UPROPERTY( EditDefaultsOnly, Category="Character Info|Health" )
	int32 CurrentHealth = 100.f;
};
