#include "HTTPDownloader.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv) {

    HTTPDownloader downloader;
    std::string content = downloader.download("https://stackoverflow.com");
    cout << content << std::endl;
}
