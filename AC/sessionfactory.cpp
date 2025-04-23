#include "sessionfactory.h"

SessionFactory::SessionFactory() {

}

std::unique_ptr<Session> SessionFactory::CreateSession(Cel && cel)
{
    return std::make_unique<Session>(std::move(cel));
}
