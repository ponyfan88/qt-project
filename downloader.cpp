#include "downloader.h"

downloader::downloader()
{
    CURL* curl;

    curl_global_init(CURL_GLOBAL_ALL);
}
