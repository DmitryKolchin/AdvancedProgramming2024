// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Inventory.generated.h"

USTRUCT( BlueprintType )
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FString Name;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	int32 Value;

	FString ToString() const
	{
		return Name + " " + FString::FromInt( Value );
	}
};

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class INVENTORYSORTING_API UInventory : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY( BlueprintReadWrite )
	TArray<FInventoryItem> Items;

public:
	UFUNCTION( BlueprintCallable )
	void AddItem(const FInventoryItem& Item);

	UFUNCTION( BlueprintCallable )
	void DisplayInventory();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent )
	void SortItemsByName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SortItemsByValue();

private:
	template <typename F>
	void SortItemsArrayPart(int32 LeftBorder, int32 RightBorder, F Comparator)
	{
		if (RightBorder <= LeftBorder)
		{
			return;
		}

		int32 MidBorder = LeftBorder + (RightBorder - LeftBorder) / 2;

		SortItemsArrayPart( LeftBorder, MidBorder, Comparator );
		SortItemsArrayPart( MidBorder + 1, RightBorder, Comparator );
		MergeTwoSortedItemArrayParts( LeftBorder, MidBorder, RightBorder, Comparator );

	};

	template <typename F>
	void MergeTwoSortedItemArrayParts(int32 LeftBorder, int32 MidBorder, int32 RightBorder, F Comparator)
	{
		// Copying the left and right parts to separate arrays
		TArray<FInventoryItem> LeftPart;
		TArray<FInventoryItem> RightPart;

		for ( int32 Index = LeftBorder; Index <= MidBorder; Index++ )
		{
			LeftPart.Add( Items[ Index ] );
		}

		for ( int32 Index = MidBorder + 1; Index <= RightBorder; Index++ )
		{
			RightPart.Add( Items[ Index ] );
		}

		// Merging the left and right parts using provided comparator

		int32 CurrentLeftItemIndex = 0;
		int32 CurrentRightItemIndex = 0;

		int32 CurrentMainItemIndex = LeftBorder;

		while ( CurrentLeftItemIndex < LeftPart.Num() && CurrentRightItemIndex < RightPart.Num() )
		{
			if ( Comparator( LeftPart[ CurrentLeftItemIndex ], RightPart[ CurrentRightItemIndex ] ) )
			{
				Items[ CurrentMainItemIndex++ ] = LeftPart[ CurrentLeftItemIndex++ ];
			}
			else
			{
				Items[ CurrentMainItemIndex++ ] = RightPart[ CurrentRightItemIndex++ ];
			}
		}

		// Copying the remaining items from the left and right parts

		while ( CurrentLeftItemIndex < LeftPart.Num() )
		{
			Items[ CurrentMainItemIndex++ ] = LeftPart[ CurrentLeftItemIndex++ ];
		}

		while ( CurrentRightItemIndex < RightPart.Num() )
		{
			Items[ CurrentMainItemIndex++ ] = RightPart[ CurrentRightItemIndex++ ];
		}
	};


};
