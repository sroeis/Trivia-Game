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
	static const Buffer serializeResponse(const ErrorResponse& er); 
	static const Buffer serializeResponse(const LoginResponse& lr);
	static const Buffer serializeResponse(const SignupResponse& sr);
	static const Buffer serializeResponse(const LogoutResponse& lr);
	static const Buffer serializeResponse(const GetRoomsResponse& r);
	static const Buffer serializeResponse(const GetPlayersInRoomResponse& pr);
	static const Buffer serializeResponse(const JoinRoomResponse& jr);
	static const Buffer serializeResponse(const CreateRoomResponse& cr);
	static const Buffer serializeResponse(const GetHighScoreResponse& gr);
	static const Buffer serializeResponse(const GetPersonalStatsResponse& gr);

private:
	//get the data into the protocol format : Code - Size - Data
	static const Buffer PackIntoBuffer(int Code, const Buffer& payload);


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