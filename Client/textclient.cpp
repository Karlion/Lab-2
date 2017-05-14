#include "textclient.h"

TextClient::ReceiveThread::ReceiveThread(TextClient *p) {
    parent = p;
}
char *TextClient::getBuf() const
{
    return buf;
}
