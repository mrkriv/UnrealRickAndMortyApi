#include "RickAndMortyCharactersAsyncAction.h"
#include "RickAndMortyApi.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonObjectConverter.h"
#include "Engine/Texture2DDynamic.h"
#include "Blueprint/AsyncTaskDownloadImage.h"

int URickAndMortyCharactersAsyncAction::CharactersCount = 0;

template<typename FunctorType>
void MakeGetRequest(FString Url, FunctorType&& OnProcessRequestComplete)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(Url);
	
	HttpRequest->OnProcessRequestComplete().BindLambda(OnProcessRequestComplete);
	HttpRequest->ProcessRequest();
}

URickAndMortyCharactersAsyncAction* URickAndMortyCharactersAsyncAction::GetRandomRickAndMortyCharacter()
{
	return NewObject<URickAndMortyCharactersAsyncAction>();
}

void URickAndMortyCharactersAsyncAction::Activate()
{
	if(CharactersCount == 0)
	{
		LoadCharactersCount();
	}
	else
	{
		LoadCharacter();
	}
}

void URickAndMortyCharactersAsyncAction::LoadCharactersCount()
{
	MakeGetRequest(*RickAndMortyApi::GetURLCharacters(0), [&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        const FString ResponseContent = Response->GetContentAsString();
        FRaMCharacterPageResponse PageResult = FRaMCharacterPageResponse();
	
        if (!bWasSuccessful)
        {
            OnFailure.Broadcast(this->Character, NULL, *FString::Printf(TEXT("%d: %s"), Response->GetResponseCode(), *ResponseContent));
            return;
        }

        if(!FJsonObjectConverter::JsonObjectStringToUStruct(ResponseContent, &PageResult, 0, 0))
        {
            OnFailure.Broadcast(this->Character, NULL, *FString::Printf(TEXT("Failed deserealize to FRaMCharacterPageResponse")));
            return;
        }

        CharactersCount = PageResult.Info.Count;
	
        LoadCharacter();
    });	
}

void URickAndMortyCharactersAsyncAction::LoadCharacter()
{
	const int CharacterId = FMath::RandRange(0, CharactersCount);
	
	MakeGetRequest(*RickAndMortyApi::GetURLCharacter(CharacterId), [&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
		const FString ResponseContent = Response->GetContentAsString();
	
        if (!bWasSuccessful)
        {
            OnFailure.Broadcast(this->Character, NULL, *FString::Printf(TEXT("%d: %s"), Response->GetResponseCode(), *ResponseContent));
            return;
        }

        if(!FJsonObjectConverter::JsonObjectStringToUStruct(ResponseContent, &this->Character, 0, 0))
        {
            OnFailure.Broadcast(this->Character, NULL, *FString::Printf(TEXT("Failed deserealize to FRaMCharacter")));
            return;
        }
	
        LoadImage();
    });
}

void URickAndMortyCharactersAsyncAction::LoadImage()
{
	UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage(*Character.Image);
	DownloadTask->OnSuccess.AddDynamic(this, &URickAndMortyCharactersAsyncAction::OnLoadImage);
	DownloadTask->OnFail.AddDynamic(this, &URickAndMortyCharactersAsyncAction::OnLoadImageFailed);

	DownloadTask->Activate();
}

void URickAndMortyCharactersAsyncAction::OnLoadImage(UTexture2DDynamic* Texture)
{
	OnSuccess.Broadcast(Character, Texture, "");
}

void URickAndMortyCharactersAsyncAction::OnLoadImageFailed(UTexture2DDynamic* Texture)
{
	OnFailure.Broadcast(this->Character, NULL, *FString::Printf(TEXT("Failed load Texture")));
}