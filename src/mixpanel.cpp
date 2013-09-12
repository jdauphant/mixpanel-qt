#include "mixpanel.h"
#include <qjson/serializer.h>

const QString Mixpanel::DEFAULT_ENDPOINT = "http://api.mixpanel.com/";
const QString Mixpanel::SET = "$set";
const QString Mixpanel::SET_ONCE = "$set_once";
const QString Mixpanel::ADD = "$add";
const QString Mixpanel::APPEND = "$append";
const QString Mixpanel::UNION = "$union";
const QString Mixpanel::DEFAULT_OPERATION = SET;

Mixpanel::Mixpanel(const QString &token) :endpoint(DEFAULT_ENDPOINT), token(token), distinct_id(QString()), verbose(DEFAULT_VERBOSE)
{
}

bool Mixpanel::track(QString event, QVariantMap properties)
{
    QVariantMap parameters;
    parameters.insert("event", event);

    properties.insert("token", token);
    if(distinct_id!=QString())
        properties.insert("distinct_id", distinct_id);

    parameters.insert("properties", properties);
    return sendRequest("track",parameters);
}

bool Mixpanel::engage(QVariantMap properties, QString operation)
{
    QVariantMap parameters;
    parameters.insert("$token", token);
    if(distinct_id==QString())
    {
        qCritical() << "distinct_id needed for engage";
        return false;
    }
    parameters.insert("$distinct_id", distinct_id);
    parameters.insert(operation, properties);
    return sendRequest("engage", parameters);
}

bool Mixpanel::sendRequest(QString path, const QVariantMap & parameters)
{
    QJson::Serializer serializer;
    bool ok;
    QByteArray json = serializer.serialize(parameters, &ok);
    if (ok) {
      qDebug() << json;
    } else {
      qCritical() << "Something went wrong:" << serializer.errorMessage();
      return ok;
    }
    QByteArray data = json.toBase64();
    QString urlString = endpoint+path+"/?data="+data;
    if(verbose)
        urlString += "&verbose=1";

    const QUrl url = QUrl(urlString);
    qDebug() << url;

    const QNetworkRequest networkRequest(url);
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager;
    QNetworkReply *networkReply = networkAccessManager->get(networkRequest);
    connect(networkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkError(QNetworkReply::NetworkError)));
    connect(networkReply, SIGNAL(finished()), this, SLOT(networkFinished()));
    return (networkReply->isFinished() || networkReply->isRunning());
}

void Mixpanel::networkError(QNetworkReply::NetworkError networkError)
{
    QNetworkReply *networkReply = qobject_cast<QNetworkReply*>(sender());
    qCritical() << networkReply->errorString();
    error();
}

void Mixpanel::networkFinished()
{
    QNetworkReply *networkReply = qobject_cast<QNetworkReply*>(sender());
    qDebug() << "Network Answer" << networkReply->readAll();
    sended();
}


QString Mixpanel::getDistinct_id() const
{
    return distinct_id;
}

void Mixpanel::setDistinct_id(const QString &value)
{
    distinct_id = value;
}

QString Mixpanel::getToken() const
{
    return token;
}

void Mixpanel::setToken(const QString &value)
{
    token = value;
}

QString Mixpanel::getEndpoint() const
{
    return endpoint;
}

void Mixpanel::setEndpoint(const QString &value)
{
    endpoint = value;
}

bool Mixpanel::getVerbose() const
{
    return verbose;
}

void Mixpanel::setVerbose(bool value)
{
    verbose = value;
}
