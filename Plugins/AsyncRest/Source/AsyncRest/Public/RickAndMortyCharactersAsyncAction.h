#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RickAndMortyModels.h"
#include "RickAndMortyCharactersAsyncAction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRestObjectRequestResult, FRaMCharactersResponse, Result, FString, Response);

/**
 * 
 */
UCLASS()
class URickAndMortyCharactersAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	
    UPROPERTY(BlueprintAssignable)
    FRestObjectRequestResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
    FRestObjectRequestResult OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Fun|RickAndMorty")
    static URickAndMortyCharactersAsyncAction* GetRickAndMortyCharacters(int page);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	// End of UBlueprintAsyncActionBase interface

private:
    void OnRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	int Page;
};
