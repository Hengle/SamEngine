#include "http.h"

#include <core/assert.h>

#include <curl/curl.h>

namespace sam
{
    size_t write_data_callback(char *ptr, size_t size, size_t nmemb, void *userData)
    {
        auto d = static_cast<data *>(userData);
        d->append(ptr, size * nmemb);
        return size * nmemb;
    };

    bool http::available = false;

    void http::initialize()
    {
        s_assert(!available);
        auto code = curl_global_init(CURL_GLOBAL_ALL);
        s_assert(code == CURLE_OK);
        available = true;
    }

    void http::finalize()
    {
        s_assert(available);
        curl_global_cleanup();
        available = false;
    }

    data_ptr http::read(const std::string &path)
    {
        s_assert(available);
        
        auto data = data::create();
        auto error = data::create(CURL_ERROR_SIZE * 4);
        auto request = curl_easy_init();
        curl_easy_setopt(request, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(request, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(request, CURLOPT_WRITEFUNCTION, write_data_callback);
        curl_easy_setopt(request, CURLOPT_ERRORBUFFER, error->get_buffer());
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
            log::warning("curl perform fail of status(%ld) when loading [%s], with error [%s].\n", status, path.c_str(), error->get_buffer());
        }
        curl_easy_cleanup(request);
        return data;
    }
}