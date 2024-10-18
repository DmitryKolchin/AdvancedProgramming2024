// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerIconWidget.generated.h"

/**
 * 
*/
UCLASS()
class HPPOTIONOPTIMISATION_API UPlayerIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetCharacterName(const FText& NewCharacterName);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCurrentHealthPercent(float NewCurrentHealthPercent);

	UFUNCTION(BlueprintImplementableEvent)
	void SetPlayerIconTexture(UTexture2D* NewPlayerIconTexture);
};
