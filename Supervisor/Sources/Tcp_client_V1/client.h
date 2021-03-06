#ifndef CLIENT_H
#define CLIENT_H
#include <QApplication>
#include <QTcpSocket>
#include <QDebug>

class client: public QObject
{
Q_OBJECT
public :
    client();
public slots :
    void recoit_texte(QString t); // en provenance de l'IHM et écrit sur la socket
    void connect_server() ;
private slots :
    void connexion_OK();  // en provenance de la socket et émet un signal vers l'IHM
    void connexion_stopped() ;
    void lecture();       // en provenance de la socket, lit la socket, émet un signal vers l'IHM
signals :
    void socket_connected();
    void socket_disconnected();
    void vers_IHM_texte(QString);
private :
    QString IP;
    int port;
    QTcpSocket soc;
};

#endif // CLIENT_H
