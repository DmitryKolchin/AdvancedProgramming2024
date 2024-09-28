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
	void SortItems(int32 LeftBorder, int32 RightBorder, F Comparator)
	{
		if (RightBorder <= LeftBorder)
		{
			return;
		}

		int32 MidBorder = LeftBorder + (RightBorder - LeftBorder) / 2;

		SortItems( LeftBorder, MidBorder, Comparator );
		SortItems( MidBorder + 1, RightBorder, Comparator );
		Merge( LeftBorder, MidBorder, RightBorder, Comparator );

	};

	template <typename F>
	void Merge(int32 LeftBorder, int32 MidBorder, int32 RightBorder, F Comparator)
	{
		// Copying the left and right parts to separate arrays
		TArray<FInventoryItem> LeftArray;
		TArray<FInventoryItem> RightArray;

		for ( int32 Index = LeftBorder; Index <= MidBorder; Index++ )
		{
			LeftArray.Add( Items[ Index ] );
		}

		for ( int32 Index = MidBorder + 1; Index <= RightBorder; Index++ )
		{
			RightArray.Add( Items[ Index ] );
		}

		// Merging the left and right parts using provided comparator

		int32 CurrentLeftItemIndex = 0;
		int32 CurrentRightItemIndex = 0;

		int32 CurrentMainItemIndex = LeftBorder;

		while ( CurrentLeftItemIndex < LeftArray.Num() && CurrentRightItemIndex < RightArray.Num() )
		{
			if ( Comparator( LeftArray[ CurrentLeftItemIndex ], RightArray[ CurrentRightItemIndex ] ) )
			{
				Items[ CurrentMainItemIndex++ ] = LeftArray[ CurrentLeftItemIndex++ ];
			}
			else
			{
				Items[ CurrentMainItemIndex++ ] = RightArray[ CurrentRightItemIndex++ ];
			}
		}

		// Copying the remaining items from the left and right parts

		while ( CurrentLeftItemIndex < LeftArray.Num() )
		{
			Items[ CurrentMainItemIndex++ ] = LeftArray[ CurrentLeftItemIndex++ ];
		}

		while ( CurrentRightItemIndex < RightArray.Num() )
		{
			Items[ CurrentMainItemIndex++ ] = RightArray[ CurrentRightItemIndex++ ];
		}
	};


};
