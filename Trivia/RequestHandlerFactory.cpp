#include "RequestHandlerFactory.h"

LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
    return LoginRequestHandler();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}
