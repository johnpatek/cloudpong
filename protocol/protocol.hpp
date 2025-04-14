#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <memory>

#include <CivetServer.h>

#include <yyjson.h>

namespace protocol
{
    class json_message
    {
    public:
        virtual void read(const yyjson_doc *doc) = 0;
    };

    struct connect_request
    {

    };
}

#endif // PROTOCOL_HPP