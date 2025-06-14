#pragma once

#include "IRequestHandler.h"
class RequestHandlerFactory; // Forward declaration
#include "RequestHandlerFactory.h"
#include "GameManager.h"
#include "Responses.h"

class GameRequestHandler : public IRequestHandler
{
private:
    Game& m_game;
    LoggedUser m_user;
    GameManager& m_gameManager;
    RequestHandlerFactory& m_handlerFactroy;
    const RequestResult getQuestion(const RequestInfo& request);
    const RequestResult submitAnswer(const RequestInfo& request);
    const RequestResult getGameResults(const RequestInfo& request);
    const RequestResult leaveGame(const RequestInfo& request);

public:
    GameRequestHandler(const LoggedUser& user, Game& game, GameManager& gameManager, RequestHandlerFactory factory);
    bool isRequestRelevant(const RequestInfo& request) override;
    const RequestResult handleRequest(const RequestInfo& request) override;
    
};