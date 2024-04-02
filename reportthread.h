#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
#ifndef REPORTTHREAD_H
#define REPORTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTextToSpeech>
#include <QSettings>
class reportthread : public QThread
{
    Q_OBJECT
public:
    explicit reportthread();
    QTextToSpeech *speech;
    QSettings *settings;
    void  speechStop();
protected:
    void run() override;
signals:
    void reportStopped();
private slots:
    void stateChanged(QTextToSpeech::State state);
};

#endif // REPORTTHREAD_H
