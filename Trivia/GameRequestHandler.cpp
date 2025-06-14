#include "GameRequestHandler.h"

using std::exception;

GameRequestHandler::GameRequestHandler(const LoggedUser& user, Game& game, GameManager& gameManager, RequestHandlerFactory factory) :
	m_user(user), m_game(game), m_gameManager(gameManager), m_handlerFactroy(factory)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& request)
{
    return request.id == LEAVE_GAME_CODE ||
           request.id == GET_GAME_RESULTS_CODE ||
           request.id == SUBMIT_ANSWER_CODE ||
           request.id == GET_QUESTION_CODE;
}

const RequestResult GameRequestHandler::handleRequest(const RequestInfo& request)
{
    switch (request.id)
    {
        case GET_QUESTION_CODE:
            return getQuestion(request);
        case SUBMIT_ANSWER_CODE:
            return submitAnswer(request);
        case GET_GAME_RESULTS_CODE:
            return getGameResults(request);
        case LEAVE_GAME_CODE:
            return leaveGame(request);
    };
}

const RequestResult GameRequestHandler::getQuestion(const RequestInfo& request)
{
    RequestResult result;
    
    try
    {
		GetQuestionResponse response;
        const Question& question = m_game.getQuestionForUser(m_user);
		response.question = question.getQuestion();

        if (response.question.empty()) throw exception();

        const auto& possibleAnswers = question.getPossibleAnswers();

        for (unsigned int i = 0; i < possibleAnswers.size(); ++i)
        {
            response.answers[i] = possibleAnswers[i];
        }
        
		result.response = JsonResponsePacketSerializer::serializeResponse(response);
        result.newHandler = this;
    }
    catch (const exception& e)
    {
        return leaveGame(request);
	}
    return result;
}

const RequestResult GameRequestHandler::submitAnswer(const RequestInfo& request)
{
    SubmitAnswerRequest submitReq = JsonResponsePacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);
	RequestResult result;
	SubmitAnswerResponse response;

	int correctAnswerId = m_game.submitAnswer(submitReq.answerId, m_user);

	result.response = JsonResponsePacketSerializer::serializeResponse(response);
    result.newHandler = this;
    
    return result;
}

const RequestResult GameRequestHandler::getGameResults(const RequestInfo& request)
{
	GetGameResultsResponse response;
    response.results = m_game.getPlayersResults();
	response.status = STATUS_OK;

	RequestResult result;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = m_handlerFactroy.createMenuRequestHandler(m_user);

    m_gameManager.deleteGame(m_game.getGameId());
    return result;
}

const RequestResult GameRequestHandler::leaveGame(const RequestInfo& request)
{
	RequestResult result;
    LeaveGameResponse response;
    
	response.status = STATUS_OK;
    result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = m_handlerFactroy.createMenuRequestHandler(m_user);

	m_game.removePlayer(m_user);

    return result;
}
