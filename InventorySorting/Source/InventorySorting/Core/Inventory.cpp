// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"

void UInventory::AddItem(const FInventoryItem& Item)
{
	Items.Add( Item );
}

void UInventory::DisplayInventory()
{
	FString SeparationLine{"----------------"};
	UE_LOG( LogTemp, Warning, TEXT( "%s" ), *SeparationLine );

	for ( auto Item : Items )
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s" ), *Item.ToString() );
	}

	UE_LOG( LogTemp, Warning, TEXT( "%s" ), *SeparationLine );
}

void UInventory::SortItemsByName_Implementation()
{
	SortItemsArrayPart( 0, Items.Num() - 1, [](const FInventoryItem& Left, const FInventoryItem& Right)
	{
		return Left.Name < Right.Name;
	} );
}

void UInventory::SortItemsByValue_Implementation()
{
	SortItemsArrayPart( 0, Items.Num() - 1, [](const FInventoryItem& Left, const FInventoryItem& Right)
	{
		return Left.Value < Right.Value;
	} );
}
