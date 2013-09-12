#ifndef MIXPANEL_H
#define MIXPANEL_H

#include "mixpanel-qt_global.h"
#include <QtCore>
#include <QtNetwork>

class MIXPANELQTSHARED_EXPORT Mixpanel: public QObject
{
    Q_OBJECT
public:
    const static QString SET;
    const static QString SET_ONCE;
    const static QString ADD;
    const static QString APPEND;
    const static QString UNION;


    const static QString DEFAULT_ENDPOINT;
    const static bool DEFAULT_VERBOSE = false;
    const static QString DEFAULT_OPERATION;

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

    bool track(QString event, QVariantMap properties = QVariantMap());
    bool engage(QVariantMap properties, QString operation = DEFAULT_OPERATION);

signals:
    void sended();
    void error();

private:
    bool sendRequest(QString path, const QVariantMap & parameters);

private slots:
    void networkError(QNetworkReply::NetworkError networkError);
    void networkFinished();
};


#endif // MIXPANEL_H
