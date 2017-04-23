#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>

#include "UDSServer.hpp"

UDSServer::UDSServer(std::string filename)
{
    this->fileName = fileName;
}

UDSServer::~UDSServer()
{
    close();
}

UDSServer::start()
{
    if(access(fileName.c_str(), F_OK) != 0) {
        perror("access() error");
        return 1;
    }
    unlink(fileName.c_str());

    sSock = socket(PF_FILE, SOCK_STREAM, 0);
    if(sSock == -1) {
        perror("socket() error");
        return 1;
    }

    memset(&sAddr, 0, sizeof(sAddr));
    sAddr.sun_family = AF_UNIX;
    strcpy(sAddr.sun_path, fileName.c_str());

    if(bind(sSock, (struct sockaddr*)&sAddr, sizeof(sAddr)) == -1) {
        perror("bind() error");
        return 1;
    }

    if(listen(sSock, 1) == -1) {
        perror("listen() error");
        return 1;
    }

    cSize = sizeof(cAddr);
    cSock = accept(sSock, (struct sockaddr*)&cAddr, &cSize);
    if(cSock == -1) {
        perror("accept() error");
        return 1;
    }


}

UDSServer::close()
{
    close(cSock);
    close(sSock);
}