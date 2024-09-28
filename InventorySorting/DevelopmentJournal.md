# Inventory Sorting

Advanced Programming

Dmitrii Kolchin

2220982

## Research

## Implementation

In order to keep the code in one place, I decided to create a UObject based class called UInventory, which will represent character's inventory and store all the items and have all the functions provided in the task description.

Firstly, I changed the Item class provided in the task to a struct, since it has no Blueprint Callable methods in it, and I do not need them to be watched by the Garbage Collector:

```cpp
USTRUCT( BlueprintType )
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite )
	FString Name;

	UPROPERTY( BlueprintReadWrite )
	int32 Value;
};
```

So that the UInventory class could have an array of FInventoryItems. This field is protected since I'll need it acessible in the Blueprint child, and I don't want any other classes to access it for the incapsulation reasons

```cpp
UPROPERTY(BlueprintReadWrite)
TArray<FInventoryItem> Items;
```

Now implementing the Inventory API:

```cpp
void UInventory::AddItem(const FInventoryItem& Item)
{
	Items.Add( Item );
}

void UInventory::DisplayInventory()
{
	FString SeparationLine{"----------------"};
	UE_LOG( LogTemp, Warning, TEXT( "%s" ), *SeparationLine );
	if ( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, SeparationLine );
	}

	for ( auto Item : Items )
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s" ), *Item.ToString() );
		if ( GEngine )
		{
			GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, Item.ToString() );
		}
	}

	UE_LOG( LogTemp, Warning, TEXT( "%s" ), *SeparationLine );
	if ( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, SeparationLine );
	}
}
```

All of these function are Blueprint Callable, so I do not need to write additional initialization and calls within C++.


### C++ Sorting

Making public Blueprint Callable and Blueprint Native (so we can override them with Blueprint-only logic further without creating additional instances)

```cpp
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent )
	void SortItemsByName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SortItemsByValue();
```

Since the sorting algorithms only differ with the comparator used, I decided to make a private templated merge sort function which accepts comparator as an argument:

```cpp
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
```

So that our public functions goint to look like this:
```cpp

void UInventory::SortItemsByName_Implementation()
{
	SortItems( 0, Items.Num() - 1, [](const FInventoryItem& Left, const FInventoryItem& Right)
	{
		return Left.Name < Right.Name;
	} );
}

void UInventory::SortItemsByValue_Implementation()
{
	SortItems( 0, Items.Num() - 1, [](const FInventoryItem& Left, const FInventoryItem& Right)
	{
		return Left.Value < Right.Value;
	} );
}

```

In order to check that our sorting is working properly, I created a simple Blueprint script within the level blueprint which tests the sorts:

<iframe width="100%" height="500px" src="https://blueprintue.com/render/q1xj89de/" scrolling="no" allowfullscreen></iframe>

And it gives us the following results:
```md
LogTemp: Warning: ----------------
LogTemp: Warning: Sword 150
LogTemp: Warning: Potion 50
LogTemp: Warning: Shield 100
LogTemp: Warning: Bow 120
LogTemp: Warning: Helmet 80
LogTemp: Warning: ----------------
LogTemp: Warning: ----------------
LogTemp: Warning: Potion 50
LogTemp: Warning: Helmet 80
LogTemp: Warning: Shield 100
LogTemp: Warning: Bow 120
LogTemp: Warning: Sword 150
LogTemp: Warning: ----------------
LogTemp: Warning: ----------------
LogTemp: Warning: Bow 120
LogTemp: Warning: Helmet 80
LogTemp: Warning: Potion 50
LogTemp: Warning: Shield 100
LogTemp: Warning: Sword 150
LogTemp: Warning: ----------------
```
### Blueprint Sorting

## Outcome

## Critical Reflection

## Bibliography

## Declared Assets
