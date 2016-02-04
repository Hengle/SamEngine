#include "http.h"

#include <CoreModule.h>

namespace SamEngine
{
    void HTTP::Initialize()
    {
        s_assert(!mAvailable);
        mg_mgr_init(&mManager, nullptr);
        mAvailable = true;
    }

    void HTTP::Finalize()
    {
        s_assert(mAvailable);
        mg_mgr_free(&mManager);
        mAvailable = false;
    }

    bool HTTP::Available()
    {
        return mAvailable;
    }

    DataPtr HTTP::Read(const std::string &path)
    {
        s_assert(mAvailable);
        s_assert(mData == nullptr);
        s_assert(!mPollFlag);

        mData = Data::Create();

        auto connection = mg_connect_http(&mManager, EventHandle, path.c_str(), nullptr, nullptr);
        connection->user_data = this;
        mPollFlag = true;
        while (mPollFlag)
        {
            mg_mgr_poll(&mManager, 1000);
        }
        mg_mgr_poll(&mManager, 1000);

        return mData;
    }

    void HTTP::EventHandle(struct mg_connection *connection, int event, void *eventData)
    {
        auto self = static_cast<HTTP *>(connection->user_data);
        switch (event)
        {
            case MG_EV_CONNECT:
            {
                auto connectStatus = static_cast<int *>(eventData);
                if (*connectStatus != 0)
                {
                    GetLog().Warning("HTTP connect fail of status(%d).\n", *connectStatus);
                }
                break;
            }
            case MG_EV_HTTP_REPLY:
            {
                connection->flags |= MG_F_CLOSE_IMMEDIATELY;
                self->mPollFlag = false;

                auto message = static_cast<http_message *>(eventData);
                if (message->resp_code == 200)
                {
                    self->mData->Copy(message->body.p, message->body.len);
                }
                else if (message->resp_code == 301)
                {
                    auto location = mg_get_http_header(message, "Location");
                    if (location)
                    {
                        std::string path(location->p, location->len);
                        auto redirect = mg_connect_http(&self->mManager, EventHandle, path.c_str(), nullptr, nullptr);
                        redirect->user_data = self;
                        self->mPollFlag = true;
                    }
                }
                else
                {
                    GetLog().Warning("HTTP response of status(%d).\n", message->resp_code);
                }
                break;
            }
            default: break;
        }
    }

    HTTP_API IHTTP &GetHTTP()
    {
        static HTTP instance;
        return instance;
    }
}