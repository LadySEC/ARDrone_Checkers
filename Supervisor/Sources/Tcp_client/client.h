/**
 * \file 	client.h
 * \brief 	Manages TCP connection/deconnection from the HMI side
 * \author 	Lady team
 * \version 1.0
 * \date 	9 January 2015
 *
 */

#ifndef CLIENT_H
#define CLIENT_H

/**********************************************************************************/
/* Libraries														      		  */
/**********************************************************************************/
#include <QTcpSocket>               /*!< Access to high-level TCP sockets functions in Qt */
#include <QDebug>                   /*!< Allow the use of qDebug to debug the program */
#include "global.h"                 /*!< Retrieve all common tools */

class client: public QObject
{
Q_OBJECT

/**********************************************************************************/
/* Public methodes                                                                */
/**********************************************************************************/

public :
    client();
    void connect_server() ;
    void recoit_texte(QByteArray message); // en provenance de l'IHM et écrit sur la socket



/**********************************************************************************/
/* Private slots                                                                  */
/**********************************************************************************/

private slots :
    void slot_connexion_OK();  // en provenance de la socket et émet un signal vers l'IHM
    void slot_connexion_stopped() ;
    void slot_lecture();       // en provenance de la socket, lit la socket, émet un signal vers l'IHM

/**********************************************************************************/
/* Signals                                                                        */
/**********************************************************************************/

signals :
    void sig_socket_connected();
    void sig_socket_disconnected();
    void sig_data_to_IHM(QChar mnemo/*, int sizeOfData*/, QByteArray data);

/**********************************************************************************/
/* Private attributes                                                             */
/**********************************************************************************/

private :
    QString IP;             /*!< IP address of the socket       */
    int port;               /*!< Number of the socket's pin     */
    QTcpSocket soc;         /*!< Socket for the TCP connexion   */

};

#endif // CLIENT_H
