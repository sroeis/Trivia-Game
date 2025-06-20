#include "GameRequestHandler.h"

using std::exception;

GameRequestHandler::GameRequestHandler(const LoggedUser& user, Game& game, GameManager& gameManager, RequestHandlerFactory& factory) :
	m_user(user), m_game(game), m_gameManager(gameManager), m_handlerFactory(factory)
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
    GetQuestionResponse response;

    try
    {
		const Question& question = m_gameManager.getGame(m_user).getQuestionForUser(m_user);
		response.question = question.getQuestion();

        if (response.question.empty()) throw exception("user finished game!");

        const auto& possibleAnswers = question.getPossibleAnswers();

        for (unsigned int i = 0; i < possibleAnswers.size(); ++i)
        {
            response.answers[i] = possibleAnswers[i];
        }
		response.status = STATUS_OK;

    }
    catch (std::runtime_error er)
    {
        std::cout << er.what() << std::endl;
    }
    catch (const exception& e)
    {
		/*response.status = 100;
        response.question = "";
		response.answers = {};*/
        return leaveGame(request);
		std::cout << e.what() << std::endl;
	}
    result.response = JsonResponsePacketSerializer::serializeResponse(response);
    result.newHandler = this;
    return result;
}

const RequestResult GameRequestHandler::submitAnswer(const RequestInfo& request)
{
    SubmitAnswerRequest submitReq = JsonResponsePacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);
	RequestResult result;
	SubmitAnswerResponse response;
    int correctAnswerId;
    try {
        correctAnswerId = m_game.submitAnswer(submitReq.answerId, submitReq.timeTaken, m_user);
    }
	catch (const std::exception& e)
    {
        std::cout << "submit" << std::endl;

		std::cout << e.what() << std::endl;
	}
	response.correctAnswerId = correctAnswerId;
    response.status = STATUS_OK;
	result.response = JsonResponsePacketSerializer::serializeResponse(response);
    result.newHandler = this;
    
    return result;
}

const RequestResult GameRequestHandler::getGameResults(const RequestInfo& request)
{
	GetGameResultsResponse response;
    RequestResult result;
    std::cout << "getting game results for" <<m_user.getUsername()<< std::endl;

    
	response.status = STATUS_OK;


    try
    {
        if (m_game.IsGameEmpty())
        {
            std::cout << "Game is empty, deleting game" << std::endl;
            response.results = m_game.getPlayersResults();
            result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
            if (m_game.didAllGotResults()) 
                m_gameManager.deleteGame(m_game.getGameId());
            

            
        }
        else {
            std::cout << "Game is not empty, waiting for players to leave" << std::endl;
            //m_game.removePlayer(m_user);
            result.newHandler = this;
            //100 Is just a random code to say there are still players in the game so we need to wait
            response.status = 100;
            map<LoggedUser, GameData>& players = m_game.getPlayers();
            for (const auto& pair : players) {
                const LoggedUser& player = pair.first;
                std::cout << player.getUsername() << std::endl;
            }
        }
    }
    catch (...)
    {
        result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
    }
    result.response = JsonResponsePacketSerializer::serializeResponse(response);

    return result;
}

const RequestResult GameRequestHandler::leaveGame(const RequestInfo& request)
{
	RequestResult result;
    LeaveGameResponse response;
    
	response.status = STATUS_OK;
    result.response = JsonResponsePacketSerializer::serializeResponse(response);
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);

	m_game.removePlayer(m_user);

    return result;
}
