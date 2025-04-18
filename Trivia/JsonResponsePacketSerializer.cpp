#include "JsonResponsePacketSerializer.h"



Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse Er)
{
	//using the macro to turn
	json J = Er;

	std::string JsonStr = J.dump();

	std::string BinaryStr = TurnToBinary(JsonStr);

	Buffer buffer = PackIntoBuffer(ERROR_CODE, BinaryStr);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse Lr)
{
	//using the macro to turn
	json J = Lr;

	std::string JsonStr = J.dump();

	std::string BinaryStr = TurnToBinary(JsonStr);

	Buffer buffer = PackIntoBuffer(LOGIN_CODE, BinaryStr);

	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse Sr)
{
	//using the macro to turn
	json J = Sr;

	std::string JsonStr = J.dump();

	std::string BinaryStr = TurnToBinary(JsonStr);

	Buffer buffer = PackIntoBuffer(SIGNUP_CODE, BinaryStr);

	return buffer;
}

std::string JsonResponsePacketSerializer::TurnToBinary(std::string Str)
{

	std::string BinaryStr = "";

	for (char& _char : Str)
	{
		BinaryStr += std::bitset<8>(_char).to_string();
	}
	
	return BinaryStr;
}

Buffer JsonResponsePacketSerializer::PackIntoBuffer(int Code, std::string Str)
{
	Buffer buffer;

	// first the code 
	buffer.push_back(Code);

	//then the data size byte by byte
	uint32_t size = Str.size()/8; //8 because str is represented as binary so 8 chars represent 1 byte
	for (int i = 0; i < 4; ++i) {
		//bit shifting the size by a byte=8bits each time and pushing it in
		buffer.push_back((size >> (8 * i)) & 0xFF);
	}

	//inserting the string to the end of the buffer 
	buffer.insert(buffer.end(), Str.begin(), Str.end());

	//now the buffer is complete it has first byte the code then size then string
	return buffer;
}


