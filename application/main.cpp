#include "HTTPDownloader.h"
#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <ctime>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;



int main(int argc, char** argv) {

    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%m-%d-%Y", localtime(&t));

    HTTPDownloader downloader;

    std::string Urls [3] = {"http://www.pfizer.com/","https://stackoverflow.com","www.snapdeal.com"};

    for(auto& URL : Urls)
    {
        std::string content = downloader.download(URL);
        mongocxx::instance inst{};

        mongocxx::client conn{mongocxx::uri{}};

        bsoncxx::builder::stream::document document{};

        auto collection = conn["test"]["testcollection"];
        document  << "Url" <<  URL << "Body" << content << "Crawled date" << s;

        collection.insert_one(document.view());
        auto cursor = collection.find({});
    }
}


/* code to print document in json
    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
    */
