#include "http.h"

#include <CoreModule.h>

#include <curl.h>

namespace SamEngine
{
    size_t WriteDataCallback(char *ptr, size_t size, size_t nmemb, void *userData)
    {
        auto result = size * nmemb;
        auto d = static_cast<Data *>(userData);
        d->Append(ptr, result);
        return result;
    }

    void HTTP::Initialize()
    {
        s_assert(!mAvailable);
        auto code = curl_global_init(CURL_GLOBAL_ALL);
        s_assert(code == CURLE_OK);
        mAvailable = true;
    }

    void HTTP::Finalize()
    {
        s_assert(mAvailable);
        curl_global_cleanup();
        mAvailable = false;
    }

    bool HTTP::Available()
    {
        return mAvailable;
    }

    DataPtr HTTP::Read(const std::string &path)
    {
        s_assert(mAvailable);
        
        auto data = Data::Create();
        auto error = Data::Create(CURL_ERROR_SIZE * 4);
        auto request = curl_easy_init();
        curl_easy_setopt(request, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(request, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(request, CURLOPT_WRITEFUNCTION, WriteDataCallback);
        curl_easy_setopt(request, CURLOPT_ERRORBUFFER, error->GetBuffer());
        curl_easy_setopt(request, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(request, CURLOPT_TCP_KEEPIDLE, 10L);
        curl_easy_setopt(request, CURLOPT_TCP_KEEPINTVL, 10L);
        curl_easy_setopt(request, CURLOPT_TIMEOUT, 30);
        curl_easy_setopt(request, CURLOPT_CONNECTTIMEOUT, 30);
        curl_easy_setopt(request, CURLOPT_ACCEPT_ENCODING, "");
        curl_easy_setopt(request, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(request, CURLOPT_WRITEDATA, data.get());
        curl_easy_setopt(request, CURLOPT_URL, path.c_str());
        curl_easy_setopt(request, CURLOPT_PORT, 80);
        curl_easy_setopt(request, CURLOPT_HTTPGET, 1);
        auto code = curl_easy_perform(request);
        auto status = 0L;
        curl_easy_getinfo(request, CURLINFO_RESPONSE_CODE, &status);
        if (code != 0)
        {
            data.reset();
            if (mAvailable)
            {
                GetLog().Warning("curl perform fail of status(%ld) when loading [%s], with error [%s].\n", status, path.c_str(), error->GetBuffer());
            }
        }
        curl_easy_cleanup(request);
        return data;
    }

    HTTP_API IHTTP &GetHTTP()
    {
        static HTTP instance;
        return instance;
    }
}