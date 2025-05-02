#pragma once

#include <iostream>
#include <bitset>
#include "json.hpp"
#include "Responses.h"


//just to make typing it easier
using json = nlohmann::json;





class JsonResponsePacketSerializer  
{
public:
	static Buffer serializeResponse(ErrorResponse er); 
	static Buffer serializeResponse(LoginResponse lr);
	static Buffer serializeResponse(SignupResponse sr);
	static Buffer serializeResponse(LogoutResponse lr);
	static Buffer serializeResponse(GetRoomsResponse r);
	static Buffer serializeResponse(GetPlayersInRoomResponse pr);
	static Buffer serializeResponse(JoinRoomResponse jr);
	static Buffer serializeResponse(CreateRoomResponse cr);
	static Buffer serializeResponse(GetHighScoreResponse gr);
	static Buffer serializeResponse(GetPersonalStatsResponse gr);

private:
	//get the data into the protocol format : Code - Size - Data
	static Buffer PackIntoBuffer(int Code, const Buffer& payload);


};

//macro from json.hpp that turn struct to json and the other way
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LoginResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SignupResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ErrorResponse, message)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LogoutResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(JoinRoomResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateRoomResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetHighScoreResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetPersonalStatsResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RoomData, id, name, maxPlayers, numOfQuestionsInGame, timePerQuestion, status)


// Custom JSON serialization for GetPlayersInRoomResponse (change "players" to "PlayersInRoom")
//NOTE: same as macro
inline void to_json(json& j, const GetPlayersInRoomResponse& pr) {
	j = json{
		{"PlayersInRoom", pr.players}  // "players" in struct becomes "PlayersInRoom" in JSON
	};
}

inline void to_json(json& j, const GetRoomsResponse& pr) {
	j = json{
		{"status", pr.status},
		{"Rooms", pr.rooms}
	};
}