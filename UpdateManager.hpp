#ifndef UPDATEMANAGER_HPP
#define UPDATEMANAGER_HPP

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Version.hpp"

class UpdateManager : public QObject{
    Q_OBJECT
private:
    QNetworkAccessManager *http;
    static const QString UPDATE_SOURCE;
public:
    UpdateManager();
public:
    void connectToServer();
private slots:
    void reply(QNetworkReply *reply);
signals:
    void newUpdate(Version version, QString updateUrl);
};

#endif // UPDATEMANAGER_HPP
