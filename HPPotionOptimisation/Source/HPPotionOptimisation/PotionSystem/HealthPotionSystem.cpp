// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPotionSystem.h"

#include "HPPotionOptimisation/Character/PlayerCharacter.h"

void UHealthPotionSystem::AddPotion(const FPotion& NewPotion)
{
	Potions.Add( NewPotion );
}

void UHealthPotionSystem::AddOverTimeHealingPotion(const FOverTimeHealingPotion& NewOverTimeHealingPotion)
{
	OverTimeHealingPotions.Add( NewOverTimeHealingPotion );
}

void UHealthPotionSystem::HealPlayers(TArray<UPlayerCharacter*> Players)
{
	// Let's sort all the available potions in descending order of healing value
	Potions.Sort( [](const FPotion& A, const FPotion& B)
	{
		return A.HealingValue > B.HealingValue;
	} );

	// Outer loop to iterate over all players
	for ( auto Player : Players )
	{
		UE_LOG( LogTemp, Warning, TEXT("%s currently has %f/%f health"), *Player->GetCharacterName().ToString(), Player->GetCurrentHealth(), Player->GetMaxHealth() );
		// Initial check to see if the player is already at full health
		if ( Player->GetMaxHealth() == Player->GetCurrentHealth() )
		{
			continue;
		}

		// Inner loop to iterate over all potions
		for ( int32 PotionIndex = 0; PotionIndex < Potions.Num(); ++PotionIndex )
		{
			// If we can heal this player without exceeding the max health, we can use this potion
			float MissingHealth = Player->GetMaxHealth() - Player->GetCurrentHealth();
			if ( Potions[ PotionIndex ].HealingValue <= MissingHealth )
			{
				// Applying the healing value of the potion to the player, and removing the potion
				Player->AddHealth( Potions[ PotionIndex ].HealingValue );
				Potions.RemoveAt( PotionIndex );
			}
		}

		// If the player is not at full health, and we still have potions left, we can use the last potion
		// We will waste the potion, but the player will be fully healed
		if ( Player->GetCurrentHealth() < Player->GetMaxHealth() && Potions.Num() > 0 )
		{
			Player->AddHealth( Potions.Last().HealingValue );
			Potions.RemoveAt( Potions.Num() - 1 );
		}
	}
}

void UHealthPotionSystem::HealPlayersWithOverTimePotions(TArray<UPlayerCharacter*> Players)
{
	// Let's sort all the available potions in descending order of healing value
	OverTimeHealingPotions.Sort( [](const FOverTimeHealingPotion& A, const FOverTimeHealingPotion& B)
	{
		return A.InstantHealingValue > B.InstantHealingValue;
	} );

	// Outer loop to iterate over all players
	for ( auto Player : Players )
	{
		UE_LOG( LogTemp, Warning, TEXT("%s currently has %f/%f health"), *Player->GetCharacterName().ToString(), Player->GetCurrentHealth(), Player->GetMaxHealth() );
		// Initial check to see if the player is already at full health
		if ( Player->GetMaxHealth() == Player->GetCurrentHealth() )
		{
			continue;
		}

		bool bPotionWasApplied = false;

		// Inner loop to iterate over all potions
		for ( int32 PotionIndex = 0; PotionIndex < OverTimeHealingPotions.Num(); ++PotionIndex )
		{
			// If we can heal this player without exceeding the max health, we can use this potion
			float MissingHealth = Player->GetMaxHealth() - Player->GetCurrentHealth();
			float RestoredHealth = OverTimeHealingPotions[ PotionIndex ].GetTotalHealingValue( Player->GetMaxHealth() );
			if ( RestoredHealth <= MissingHealth )
			{
				// Applying the healing value of the potion to the player, and removing the potion
				Player->SetNewOverTimeHealingPotion( OverTimeHealingPotions[ PotionIndex ] );
				OverTimeHealingPotions.RemoveAt( PotionIndex );
				bPotionWasApplied = true;
				break;
			}
		}

		if ( bPotionWasApplied )
		{
			continue;
		}

		// If the player is not at full health, and we still have potions left, we can use the last potion
		// We will waste the potion, but the player will be fully healed
		if ( Player->GetCurrentHealth() < Player->GetMaxHealth() && OverTimeHealingPotions.Num() > 0 )
		{
			Player->SetNewOverTimeHealingPotion( OverTimeHealingPotions.Last() );
			OverTimeHealingPotions.RemoveAt( OverTimeHealingPotions.Num() - 1 );
		}
	}
}
