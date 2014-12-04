#include "client.h"


client::client()
{
    port = NUM_PORT_CLIENT; // choix arbitraire (>1024)
    IP = ADDR_IP_CLIENT  ;
    QObject::connect(&soc,SIGNAL(connected()),this,SLOT(connexion_OK()));
    // signal émis lors de la connexion au serveur
    QObject::connect(&soc, SIGNAL(disconnected()), this, SLOT(connexion_stopped()));
    QObject:: connect(&soc, SIGNAL(readyRead()), this, SLOT(lecture()));
    // signal émis lorsque des données sont prêtes à être lues
}


void client::connect_server()
{
    soc.connectToHost(IP,port) ;
}

void client::recoit_texte(QString t)
{
    QTextStream texte(&soc); // on associe un flux à la socket
    texte << t ;        // on écrit dans le flux le texte saisi dans l'IHM
    qDebug() << t;
}
void client::connexion_OK()
{
    emit socket_connected(); // on envoie un signal à l'IHM
}

void client::connexion_stopped()
{
    emit socket_disconnected();
}

void client::lecture()
{
    QString ligne;
    while(soc.canReadLine()) // tant qu'il y a quelque chose à lire dans la socket
    {
        ligne = soc.readLine();     // on lit une ligne
        qDebug() << ligne ;
        std::cout << ligne.toStdString() << endl ;
        emit vers_IHM_texte(ligne); // on envoie à l'IHM
    }
}
