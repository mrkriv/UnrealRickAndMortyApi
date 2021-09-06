#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RickAndMortyModels.h"

#include "RickAndMortyCharactersAsyncAction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRandomRickAndMortyCharacterResult, FRaMCharacter, Character, UTexture2DDynamic*, Texture, FString, ErrorMessage);

/**
 * Get random character of RickAndMorty world from fun API 
 */
UCLASS()
class URickAndMortyCharactersAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	
    UPROPERTY(BlueprintAssignable)
    FRandomRickAndMortyCharacterResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
    FRandomRickAndMortyCharacterResult OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Fun|RickAndMorty")
    static URickAndMortyCharactersAsyncAction* GetRandomRickAndMortyCharacter();

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	// End of UBlueprintAsyncActionBase interface

private:
	static int CharactersCount;
	FRaMCharacter Character;
	
	void LoadCharactersCount();
	void LoadCharacter();
	void LoadImage();

	UFUNCTION()
	void OnLoadImage(UTexture2DDynamic* Texture);
	
	UFUNCTION()
	void OnLoadImageFailed(UTexture2DDynamic* Texture);
};
