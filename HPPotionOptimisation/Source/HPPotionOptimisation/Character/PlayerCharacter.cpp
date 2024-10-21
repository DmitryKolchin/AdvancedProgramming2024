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

float UPlayerCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UPlayerCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

UPlayerIconWidget* UPlayerCharacter::GetPlayerIconWidget() const
{
	return PlayerIconWidget;
}

void UPlayerCharacter::AddHealth(float HealthToAdd)
{
	if ( !IsValid( PlayerIconWidget ) )
	{
		ensureAlwaysMsgf( false, TEXT("PlayerIconWidget is not valid") );
		return;
	}
	UE_LOG( LogTemp, Warning, TEXT("Adding %f health to %s"), HealthToAdd, *CharacterName.ToString() );

	CurrentHealth = FMath::Min( MaxHealth, CurrentHealth + HealthToAdd );
	PlayerIconWidget->SetCurrentHealthPercent( static_cast<float>( CurrentHealth ) / static_cast<float>( MaxHealth ) );
}

void UPlayerCharacter::SetNewOverTimeHealingPotion(const FOverTimeHealingPotion& NewOverTimeHealingPotion)
{
	if ( !IsValid( PlayerIconWidget ) )
	{
		ensureAlwaysMsgf( false, TEXT("PlayerIconWidget is not valid") );
		return;
	}

	// If we have no active healing potion, we start the healing effect
	if ( !ActiveHealingPotion.IsSet() )
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick( this, &UPlayerCharacter::ApplyOverTimeHealingPotionPerTick );
	}

	// Setting the new active healing potion
	ActiveHealingPotion = NewOverTimeHealingPotion;

	// Calculating potential health to show it on the UI
	float PotentialHealth = FMath::Min( MaxHealth, CurrentHealth + ActiveHealingPotion.GetValue().GetTotalHealingValue( MaxHealth) );
	PlayerIconWidget->SetPotentialHealthPercent( PotentialHealth / MaxHealth );

	// Adding the instant healing value to the player
	AddHealth( ActiveHealingPotion.GetValue().InstantHealingValue );
}

void UPlayerCharacter::ApplyOverTimeHealingPotionPerTick()
{
	if ( !IsValid( GetWorld() ) )
	{
		ensureAlwaysMsgf( false, TEXT("World is not valid") );
		return;
	}

	// If we do not have any active healing potion, we stop the function
	if ( !ActiveHealingPotion.IsSet() )
	{
		return;
	}

	float DeltaSeconds = GetWorld()->GetDeltaSeconds();

	// Calculating the added health
	float HealingValuePerTick = ActiveHealingPotion.GetValue().GetHealingValuePerTick( MaxHealth, DeltaSeconds );

	// Adding the health to the player
	AddHealth( HealingValuePerTick );

	ActiveHealingPotion.GetValue().ElapsedHealingDuration += GetWorld()->GetDeltaSeconds();

	// If the healing effect has expired or the player is at full health, we stop the healing effect
	if ( ActiveHealingPotion.GetValue().ElapsedHealingDuration >= ActiveHealingPotion.GetValue().TotalHealingDuration || CurrentHealth == MaxHealth )
	{
		ActiveHealingPotion.Reset();
		return;
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick( this, &UPlayerCharacter::ApplyOverTimeHealingPotionPerTick );
}
