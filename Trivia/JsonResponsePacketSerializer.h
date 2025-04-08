#include <vector>
typedef std::vector<char> Buffer;
struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

class JsonResponsePacketSerializer 
{
public:
	Buffer serializeResponse(ErrorResponse); 

private:
	

};