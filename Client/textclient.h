#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#define _WIN32_WINNT 0x501
#include <ws2tcpip.h>
#include <QThread>
#include <winsock2.h>
#include <iostream>
using namespace std;

class TextClient: public QObject {

    Q_OBJECT

    SOCKET server;
    WSADATA wsadata;
    char *buf;
    bool buf_changed;

    friend class ReceiveThread;


    class ReceiveThread: public QThread {
        TextClient *parent;

    public:

        ReceiveThread(TextClient *p);

        void run() {
            SOCKET& serv = parent->server;


            while(true) {
                char* &buf = parent->buf;
                buf = new char[2048];
                int bytes = recv(serv, buf, 2047, 0);

                if (bytes <= 0) return;
                buf[bytes] = '\0';
                parent->update();
                sleep(1);

            }
        }
    };

    ReceiveThread *incomingConnection;

    void update() {
        //cout << "Updating data to: " << buf << endl;
        emit got_new_data();
    }

public:

    TextClient() {}


    void sendData(QString data) {
        string line = data.toStdString();

        int len = line.length();
        char* buf = new char[len + 1];
        strcpy(buf, line.c_str());
        buf[len] = '\0';

        //cout << buf << endl;
        send(server, buf, len + 1, 0);
    }

    int sconnect() {

        memset(&wsadata, 0, sizeof(WSADATA));

        int res = WSAStartup(MAKEWORD(2,2),&wsadata);
        if (res != 0) {
            cout << "Startup failed" << endl;
            return 10001;
        }

        addrinfo hints;
        addrinfo *svaddr;

        memset(&hints, 0, sizeof(hints));

        int result = getaddrinfo("127.0.0.1", "20248", &hints, &svaddr);
        if (result != 0) {
            cout << "getinfo error " << result << endl;
            return 10002;
        }


        server = socket(svaddr->ai_family, svaddr->ai_socktype, svaddr->ai_protocol);
        if (server == INVALID_SOCKET) {
            cout << "Socket creation failed" << endl;
            return 10003;
        }


        result = ::connect(server, svaddr->ai_addr, svaddr->ai_addrlen);
        if (result != 0) {
            cout << "Connection error" << endl;
            return 10004;
        }

        incomingConnection = new ReceiveThread(this);
        incomingConnection->start();

        return 0;
    }

    char *getBuf() const;

public slots:


signals:
    void got_new_data();
};

#endif // TEXTCLIENT_H
