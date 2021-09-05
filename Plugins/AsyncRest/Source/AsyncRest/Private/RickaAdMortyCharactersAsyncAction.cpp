#include "RickAndMortyCharactersAsyncAction.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "JsonObjectConverter.h"

URickAndMortyCharactersAsyncAction* URickAndMortyCharactersAsyncAction::GetRickAndMortyCharacters(int page)
{
	URickAndMortyCharactersAsyncAction* Proxy = NewObject<URickAndMortyCharactersAsyncAction>();
	Proxy->Page = page;
	return Proxy;
}

void URickAndMortyCharactersAsyncAction::Activate()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", "application/json");
	HttpRequest->SetURL(*FString::Printf(TEXT("https://rickandmortyapi.com/api/character/?page=%d"), Page));
	
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URickAndMortyCharactersAsyncAction::OnRequestCompleted);
	HttpRequest->ProcessRequest();
}

void URickAndMortyCharactersAsyncAction::OnRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	const FString ResponseContent = Response->GetContentAsString();
	FRaMCharactersResponse Result = FRaMCharactersResponse();
	
	if (!bWasSuccessful)
	{
		OnFailure.Broadcast(Result, *FString::Printf(TEXT("%d: %s"), Response->GetResponseCode(), *ResponseContent));
		return;
	}

	if(!FJsonObjectConverter::JsonObjectStringToUStruct(ResponseContent, &Result, 0, 0))
	{
		OnFailure.Broadcast(Result, *FString::Printf(TEXT("Failed deserealize to FRaMCharactersResponse")));
		return;
	}
	
	OnSuccess.Broadcast(Result, "");
}
