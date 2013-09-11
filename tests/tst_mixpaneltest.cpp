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
    void mixpanelTrackCase1();
    void mixpanelTrackCase1_data();
};

MixpanelTest::MixpanelTest()
{

}

void MixpanelTest::initTestCase()
{
    mixpanel = new Mixpanel("cbaf4f8d9d5c467e9eda8b4d9cf7df0d");
    mixpanel->setVerbose(true);
}

void MixpanelTest::cleanupTestCase()
{
    delete mixpanel;
}

void MixpanelTest::mixpanelTrackCase1()
{
    QFETCH(QString, event);
    QSignalSpy spySended(mixpanel, SIGNAL(sended()));
    QSignalSpy spyError(mixpanel, SIGNAL(error()));
    QVERIFY(mixpanel->track(event));

    QTest::qWait(2000);

    QCOMPARE(spySended.count(), 1);
    QCOMPARE(spyError.count(), 0);
}


void MixpanelTest::mixpanelTrackCase1_data()
{
    QTest::addColumn<QString>("event");
    QTest::newRow("0") << QString("Test TrackCase1 Event 1");
    QTest::newRow("1") << QString("Test TrackCase1 Event 2");
}

QTEST_MAIN(MixpanelTest)

#include "tst_mixpaneltest.moc"
