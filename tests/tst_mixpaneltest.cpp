#include <QString>
#include <QtTest>

#include "mixpanel.h"

class MixpanelTest : public QObject
{
    Q_OBJECT
    
public:
    MixpanelTest();

private:
    Mixpanel * mixpanel;
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void mixpanelTrackCase();
    void mixpanelTrackCase_data();
    void mixpanelEngageCase();
    void mixpanelEngageCase_data();
};

MixpanelTest::MixpanelTest()
{

}

void MixpanelTest::initTestCase()
{
    mixpanel = new Mixpanel("cbaf4f8d9d5c467e9eda8b4d9cf7df0d");
}

void MixpanelTest::cleanupTestCase()
{
    delete mixpanel;
}

void MixpanelTest::mixpanelTrackCase()
{
    QFETCH(QString, event);
    QFETCH(QVariantMap, properties);
    QFETCH(QString, distinct_id);
    QFETCH(bool, verbose);

    mixpanel->setVerbose(verbose);
    mixpanel->setDistinct_id(distinct_id);

    QSignalSpy spySended(mixpanel, SIGNAL(sended()));
    QSignalSpy spyError(mixpanel, SIGNAL(error()));
    QVERIFY(mixpanel->track(event,properties));

    QTest::qWait(2000);

    QCOMPARE(spySended.count(), 1);
    QCOMPARE(spyError.count(), 0);
}


void MixpanelTest::mixpanelTrackCase_data()
{
    QTest::addColumn<QString>("event");
    QTest::addColumn<QVariantMap>("properties");
    QTest::addColumn<QString>("distinct_id");
    QTest::addColumn<bool>("verbose");

    QTest::newRow("Simple event 1 verbose") << QString("TrackCase 1") << QVariantMap() << QString() << true;
    QTest::newRow("Simple event 2 verbose") << QString("TrackCase 2") << QVariantMap() << QString() << true;
    QVariantMap test1;
    test1.insert("time", QDateTime().toTime_t());
    QTest::newRow("Event with properties 1 verbose") << QString("TrackCase with properties 1") << test1 << QString() << true;
    QVariantMap test2;
    test1.insert("time", QDateTime().toTime_t());
    test1.insert("mp_name_tag", "Stream Name");
    QTest::newRow("Event with properties 2 verbose") << QString("TrackCase with properties 2") << test2 << QString() << true;


    QTest::newRow("Simple event 1") << QString("TrackCase 1") << QVariantMap() << QString() << false;
    QTest::newRow("Simple event 2") << QString("TrackCase 2") << QVariantMap() << QString() << false;
    QTest::newRow("Event with properties 1") << QString("TrackCase with properties 1") << test1 << QString() << false;
    QTest::newRow("Event with properties 2") << QString("TrackCase with properties 2") << test2 << QString() << false;

    QTest::newRow("John event 1") << QString("Signup") << QVariantMap() << QString("john_doe_1234") << false;
    QTest::newRow("John event 2") << QString("Signin") << QVariantMap() << QString("john_doe_1234") << false;
    QTest::newRow("John event 3") << QString("Buy somethings") << QVariantMap() << QString("john_doe_1234") << false;
    QVariantMap test3;
    test1.insert("mp_name_tag", "Buy stream");
    QTest::newRow("John event with properties 1") << QString("Buy another things") << test3 << QString("john_doe_1234") << false;
    QVariantMap test4;
    test1.insert("time", QDateTime().toTime_t());
    test1.insert("mp_name_tag", "Buy stream");
    QTest::newRow("John event with properties 2") << QString("Buy yet another things") << test4 << QString("john_doe_1234") << false;

    QTest::newRow("Jane event 1") << QString("Signup") << QVariantMap() << QString("jane_doe_12") << false;
    QTest::newRow("Jane event 2") << QString("Signin") << QVariantMap() << QString("jane_doe_12") << false;
    QTest::newRow("Jane event 3") << QString("Buy somethings") << QVariantMap() << QString("jane_doe_12") << false;
}

void MixpanelTest::mixpanelEngageCase()
{
    QFETCH(QVariantMap, properties);
    QFETCH(QString, distinct_id);
    QFETCH(QString, operation);
    QFETCH(bool, verbose);

    mixpanel->setVerbose(verbose);
    mixpanel->setDistinct_id(distinct_id);

    QSignalSpy spySended(mixpanel, SIGNAL(sended()));
    QSignalSpy spyError(mixpanel, SIGNAL(error()));
    QVERIFY(mixpanel->engage(properties,operation));

    QTest::qWait(1000);

    QCOMPARE(spySended.count(), 1);
    QCOMPARE(spyError.count(), 0);
}


void MixpanelTest::mixpanelEngageCase_data()
{
    QTest::addColumn<QVariantMap>("properties");
    QTest::addColumn<QString>("distinct_id");
    QTest::addColumn<QString>("operation");
    QTest::addColumn<bool>("verbose");

    QVariantMap test1;
    test1.insert("gender", "male");
    test1.insert("age", 15);
    QTest::newRow("Set john") << test1 << QString("john_doe_1234") << Mixpanel::SET << true;
    QVariantMap test2;
    test2.insert("gender", "female");
    test2.insert("birthday", "1987-09-20");
    QTest::newRow("Set jane") << test2 << QString("jane_doe_12") << Mixpanel::SET << false;

    QVariantList test3;
    test3 << "Stuff" << "More stuff";
    QVariantMap test4;
    test4.insert("Items Buy",test3);
    QTest::newRow("Union john 1") << test4 << QString("john_doe_1234") << Mixpanel::UNION << true;

    QVariantList test5;
    test5 << "Stuff" << "More More stuff";
    QVariantMap test6;
    test6.insert("Items Buy",test5);
    QTest::newRow("Union john 2") << test6 << QString("john_doe_1234") << Mixpanel::UNION << true;
}

QTEST_MAIN(MixpanelTest)

#include "tst_mixpaneltest.moc"
