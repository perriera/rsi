#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const* argv[]) {
    try {
        extras::rsi::DownloaderClient downloader;
        downloader.parameters(argc, argv);
        extras::rsi::FileNotFoundException::assertion(downloader.payload(), __INFO__);
        downloader.connect();
        downloader.transfer();
        printf("[+]File data downloaded successfully.\n");
        downloader.close();
        printf("[+]Closed the connection.\n");
        return 0;
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        return -1;
    }
}
