#ifndef MIXPANEL_H
#define MIXPANEL_H

#include "mixpanel-qt_global.h"
#include <QtCore>
#include <QtNetwork>

class MIXPANELQTSHARED_EXPORT Mixpanel: public QObject
{
    Q_OBJECT
public:
    enum EngageOperation {
        set,
        set_once,
        add,
        append,
        union_
    };

    const static QString DEFAULT_ENDPOINT;
    const static bool DEFAULT_VERBOSE = false;
    const static EngageOperation DEFAULT_OPERATION = set;

private:
    QString endpoint;
    QString token;
    QString distinct_id;
    bool verbose;

public:
    Mixpanel(const QString &token);

    QString getEndpoint() const;
    void setEndpoint(const QString &value);
    QString getToken() const;
    void setToken(const QString &value);
    QString getDistinct_id() const;
    void setDistinct_id(const QString &value);
    bool getVerbose() const;
    void setVerbose(bool value);

    bool track(QString event, QVariantMap properties = QVariantMap(), QString mp_name_tag="");
    bool engage(QVariantMap properties, EngageOperation operation = DEFAULT_OPERATION);

signals:
    void sended();
    void error();

private:
    bool sendRequest(QString path,QByteArray data);

private slots:
    void networkError(QNetworkReply::NetworkError networkError);
    void networkFinished();


};


#endif // MIXPANEL_H
