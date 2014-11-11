#include "client.h"


client::client()
{
    port=4000; // choix arbitraire (>1024)
    IP="192.168.1.1" ;
    QObject::connect(&soc,SIGNAL(connected()),this,SLOT(connexion_OK()));
    // signal émis lors de la connexion au serveur
    QObject:: connect(&soc, SIGNAL(readyRead()), this, SLOT(lecture()));
    // signal émis lorsque des données sont prêtes à être lues
}

void client::recoit_IP  (QString IP2)
{
    IP=IP2;
    soc.connectToHost(IP,port); // pour se connecter au serveur
    qDebug() << IP2;
}

/*
void client::connect_server()
{
    soc.connectToHost(IP,port) ;
}
*/
void client::recoit_texte(QString t)
{
    QTextStream texte(&soc); // on associe un flux à la socket
    texte << t<<endl;        // on écrit dans le flux le texte saisi dans l'IHM
    qDebug() << t;
}
void client::connexion_OK()
{
    emit vers_IHM_connexion_OK(); // on envoie un signal à l'IHM
}
void client::lecture()
{
    QString ligne;
    while(soc.canReadLine()) // tant qu'il y a quelque chose à lire dans la socket
    {
        ligne = soc.readLine();     // on lit une ligne
        emit vers_IHM_texte(ligne); // on envoie à l'IHM
    }
}
