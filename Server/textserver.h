#ifndef TEXTSERVER_H
#define TEXTSERVER_H

#define _WIN32_WINNT 0x501
#include <ws2tcpip.h>
#include "Text.h"
#include <QThread>
#include <winsock2.h>


class textServer {


    class SendTextThread:public QThread {
        SOCKET client;
        textServer *parent;
    public:
        SendTextThread(textServer *p, SOCKET src) {
            client = src;
            parent = p;
        }

        void run() {
            while(true) {
                string std_ln = parent->text->toString();
                int len = std_ln.size();

                char* line = new char[len];
                strcpy(line, parent->text->toString().c_str());
                int res = send(client, line, len, 0);
                if (res <= 0) return;
                sleep(1);
            }
        }
    };


    class ReceiveTextThread:public QThread {
        SOCKET client;
        textServer *parent;
    public:
        ReceiveTextThread(textServer *p, SOCKET src) {
            client = src;
            parent = p;
        }

        void run() {

            while(true) {
                char *buf = new char[2048];
                memset(buf, 0, sizeof(buf));

                int bytes = recv(client, buf, 2047, 0);

                if (bytes <= 0) {
                    cout << "Disconnected" << endl;
                    return;
                }
                buf[bytes] = '\0';


                string txt_in_line(buf);
                parent->text = parent->text->parseFromString(txt_in_line);

                //cout << "Text updated to:" << endl;
                //cout << txt_in_line << endl;
                //cout << "----------------" << endl;
            }
            cout << "Disconnected" << endl;
        }
    };


    class ListenThread:public QThread {
        textServer *parent;
    public:

        ListenThread(textServer *p) {
            parent = p;
        }


        void run() {

            addrinfo hints;
            addrinfo *addr;

            memset(&hints, 0, sizeof(hints));

            getaddrinfo("127.0.0.1", "20248", &hints, &addr);


            SOCKET ListenSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
            if(ListenSocket == INVALID_SOCKET) {
                cout << "Invalid socket" << endl;
                return;
            }

            cout << "Socket created" << endl;

            if ( bind(ListenSocket, addr->ai_addr, addr->ai_addrlen) == SOCKET_ERROR) {
                int err = WSAGetLastError();
                cout << "Bind failed " << err << endl;
                return;
            }
            cout << "Bind successful" << endl;

            u_long iMode = 1;
            while(true) {
                listen(ListenSocket, SOMAXCONN);
                SOCKET clnt = accept(ListenSocket, NULL, NULL);
                parent->addNewClient(clnt);
                parent->runLastClient();
                cout << "New client connected" << endl;
            }
        }
    };

    friend class ListenThread;

    void addNewClient(SOCKET cln) {
        SendTextThread* sclient = new SendTextThread(this, cln);
        ReceiveTextThread *rclient = new ReceiveTextThread(this, cln);
        clients.push_back(
                    pair<SendTextThread*, ReceiveTextThread*>
                        (sclient, rclient));
    }

    void runLastClient() {
        if (clients.size() > 0) {
            clients.at(clients.size() - 1).first->start();
            clients.at(clients.size() - 1).second->start();
        }
    }


    WSADATA wsadata;
    sockaddr_in local;

    Text *text;
    vector<pair <SendTextThread*, ReceiveTextThread*> > clients;

public:

    int run() {

        if (WSAStartup(MAKEWORD(2,2),&wsadata) != 0) {
            printf("Failed. Error Code : %d",WSAGetLastError());
            return 1;
        }

        text = Text::parseFromString("Type to start editing");

        ListenThread listenForConnections(this);
        listenForConnections.run();

        return 0;
    }
};

#endif // TEXTSERVER_H
