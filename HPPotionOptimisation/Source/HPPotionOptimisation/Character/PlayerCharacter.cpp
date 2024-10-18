// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "Blueprint/UserWidget.h"
#include "HPPotionOptimisation/DataAssets/CharacterInfoDataAsset.h"

void UPlayerCharacter::Init(TSoftObjectPtr<UCharacterInfoDataAsset> CharacterInfoDataAssetSoftPtr)
{
	if (CharacterInfoDataAssetSoftPtr.IsNull())
	{
		ensureAlwaysMsgf( false, TEXT("CharacterInfoDataAssetSoftPtr is null") );
		return;
	}

	CharacterName = CharacterInfoDataAssetSoftPtr.LoadSynchronous()->CharacterName;
	CurrentHealth = CharacterInfoDataAssetSoftPtr.LoadSynchronous()->CurrentHealth;
	MaxHealth = CharacterInfoDataAssetSoftPtr.LoadSynchronous()->MaxHealth;


	if ( PlayerIconWidgetClassSoftClassPtr.IsNull() )
	{
		ensureAlwaysMsgf( false, TEXT("PlayerIconWidgetClassSoftClassPtr is null") );
		return;
	}

	PlayerIconWidget = Cast<UPlayerIconWidget>( CreateWidget( GetWorld(), PlayerIconWidgetClassSoftClassPtr.LoadSynchronous() ) );
	if ( !IsValid( PlayerIconWidget ) )
	{
		ensureAlwaysMsgf( false, TEXT("Unable to create player icon widget") );
		return;
	}

	PlayerIconWidget->SetCharacterName( CharacterName );
	PlayerIconWidget->SetCurrentHealthPercent( static_cast<float>( CurrentHealth ) / static_cast<float>( MaxHealth ) );
	PlayerIconWidget->SetPlayerIconTexture( CharacterInfoDataAssetSoftPtr.LoadSynchronous()->CharacterIcon );

}

FText UPlayerCharacter::GetCharacterName() const
{
	return CharacterName;
}

int32 UPlayerCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

int32 UPlayerCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

UPlayerIconWidget* UPlayerCharacter::GetPlayerIconWidget() const
{
	return PlayerIconWidget;
}

void UPlayerCharacter::AddHealth(int32 HealthToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding %d health to %s"), HealthToAdd, *CharacterName.ToString());
	CurrentHealth = FMath::Min( MaxHealth, CurrentHealth + HealthToAdd );
	if ( PlayerIconWidget )
	{
		PlayerIconWidget->SetCurrentHealthPercent( static_cast<float>( CurrentHealth ) / static_cast<float>( MaxHealth ) );
	}
}
