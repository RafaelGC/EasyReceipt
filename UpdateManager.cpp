#include "UpdateManager.hpp"

const QString UpdateManager::UPDATE_SOURCE = "http://personales.alumno.upv.es/ragonca2/easyreceipt.html";

UpdateManager::UpdateManager(){
}

void UpdateManager::connectToServer(){
    http = new QNetworkAccessManager(this);
    QObject::connect(http,SIGNAL(finished(QNetworkReply*)),this,SLOT(reply(QNetworkReply*)));

    http->get(QNetworkRequest(QUrl(UPDATE_SOURCE)));
}

void UpdateManager::reply(QNetworkReply *reply){
    //Aquí se guardará la información de la actualización.
    char dataRead[256];
    reply->readLine(dataRead,256);

    //Se almacena en un array.
    QString dataString(dataRead);
    //Y se parte en trozos para obtener lo que interesa: por un lado el número
    //de versión y por otro la web de descarga.
    QStringList tokenized = dataString.split(" ");
    if (tokenized.size()==2){
        emit newUpdate(Version(tokenized.at(0)),tokenized.at(1));
    }

    reply->deleteLater();//Según la documentación hay que eliminarlo así.
}

