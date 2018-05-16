/*
 * SSNFS Client v0.1
 *
 * Available under the license(s) specified at https://github.com/MDTech-us-MAN/SSNFS.
 *
 * Copyright 2018 Maxwell Dreytser
 */

#ifndef SSNFSWORKER_H
#define SSNFSWORKER_H

#include <QThread>
#include <QSqlDatabase>
#include <QSslSocket>
#include <QUuid>

#include <common.h>

enum ClientStatus {
    WaitingForHello,
    WaitingForShare,
    WaitingForOperation,
    InOperation
};

class SSNFSWorker : public QThread
{
    Q_OBJECT
public:
    SSNFSWorker(int socketDescriptor, QObject *parent);
    ~SSNFSWorker() {
        configDB.close();
        QSqlDatabase::removeDatabase(configDB.databaseName());
        socket->deleteLater();
    }

    void run() override;

    QString getPerms(QString path, qint32 uid);
    void ReadyToRead();
    void processHttpRequest(char firstChar);

    QSqlDatabase configDB;

    QSslSocket *socket;
    ClientStatus status = WaitingForHello;
    Common::Operation operation;
    bool working = false;
    QHash<int, int> fds;
    QTime timer;

    qint64 clientKey = -1;
    QString clientName;
    qint64 shareKey = -1;
    QString shareName;
    QString defaultPerms;
    QString localPath;

    QByteArray httpResponse;
    QHash<QString, QString> responseHeaders;
    quint16 httpResultCode = 200;
    QHash<quint16, QString> knownResultCodes;
    qint64 webUserKey = -1;

private:
    int socketDescriptor;
};

#endif // SSNFSWORKER_H
