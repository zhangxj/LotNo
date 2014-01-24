#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <QSet>
#include <QJsonArray>
#include "database.h"

class DataFilter : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString inerString READ getString WRITE setString NOTIFY stringChanged)

public:
    explicit DataFilter(QObject *parent = 0);

signals:
    void stringChanged();
    void stringListChanged();
    void checkCodeOk();
    void checkCodeError();

public slots:
    QString getString();
    QStringList getStringList();

    bool setScan(QString flag, QString no, QString Location);
    void searchData(QString flag, QString no);


    bool record_LotNoBlockNo(QString flag, QString no);
    void searchLotNoBlockNo(QString flag, QString no);

    void OnAbout();
    void clearData();
    void clearBlockNo();

    QString getHardMD5();
    void checkCode(QString code);
    void FirstCheck();
    QString JiaMi(QString code);
    void setDBConfig(QString ip, QString user, QString pwd);
    QString getIp();
    QString getUser();
    QString getPwd();
    QString CheckDB();
    void quit();


public:
    Database        m_DB;
    QString         m_string;
    QStringList     m_StringList;

    QString m_CurrentLotNo;
    QString m_CurrentBlockNo;

    QString m_checkCode;
};

#endif // DATAFILTER_H
