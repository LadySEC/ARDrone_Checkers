#include "client.h"


client::client()
{
    port = NUM_PORT_CLIENT;
    IP = ADDR_IP_CLIENT  ;
    QObject::connect(&soc,SIGNAL(connected()),this,SLOT(slot_connexion_OK()));
    // signal émis lors de la connexion au serveur
    QObject::connect(&soc, SIGNAL(disconnected()), this, SLOT(slot_connexion_stopped()));
    QObject:: connect(&soc, SIGNAL(readyRead()), this, SLOT(slot_lecture()));
    // signal émis lorsque des données sont prêtes à être lues
}


void client::connect_server()
{
    soc.connectToHost(IP,port) ;
}


void client::recoit_texte(QByteArray message)
{
    unsigned char i;

    QTextStream texte(&soc); // on associe un flux à la socket
    //texte << message ;        // on écrit dans le flux le texte saisi dans l'IHM

    for(i = 0; i < 3; i++)
    {
        texte << message.at(i);
        qDebug() << message.toHex().at(i*2) << message.toHex().at(i*2 +1)  ;
    }
    if (message.size() > 3)
    {
        for(i = 3; i < message.size(); i++)
        {
            texte << message.at(i);
            qDebug() << message.toHex().at(i*2) << message.toHex().at(i*2 +1)  ;
        }
    }



    qDebug() << "size : " << message.size() <<  " MESSAGE TO SEND TO THE DRONE : " << message.toHex() << endl ;
}



void client::slot_connexion_OK()
{
    emit sig_socket_connected(); // on envoie un signal à l'IHM
}

void client::slot_connexion_stopped()
{
    emit sig_socket_disconnected();
    if (soc.isOpen())
        soc.close();
}

void client::slot_lecture()
{
    QByteArray ligne;
    if(soc.bytesAvailable() > 0)
        ligne+=soc.readAll();

    int numOc = 0 ;
    int taille ;
    QByteArray mess ;
   // qDebug() << "message : " << ligne.toHex();

    while (numOc < ligne.size())
    {
        mess.clear();
        QChar mnemo = ligne.at(numOc) ;
        //qDebug() << "mnemo : " << mnemo ;
        numOc++ ;
        taille = ligne.at(numOc) ;
        //qDebug() << "Nombre d'octets : " << taille ;
        numOc++ ;

        for (int j = 0 ; j < taille ; j++)
        {
            mess.append(ligne.at(numOc+j))  ;
        }
        //qDebug() << mess.toHex() << endl ;

        emit(sig_data_to_IHM(mnemo/*, taille*/, mess));

        numOc += taille ;
    }


}















