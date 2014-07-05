#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <QSet>
#include <QJsonArray>
#include <QCalendarWidget>

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

    bool setScan(QString flag, QString no, QString Location, int sn_flag);
    void searchData(QString flag, QString no, int sn_flag);
    void searchDataByDate();


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
    QString getDirPath();
    QString setFilePath();
    void createLogDir();
    void saveLog1(QString LotNo, QString BlockNo);
    void saveLog2(QString LotNo, QString BlockNo, QString SN, QString Location);
    void SNLuRuDone();  //SN 录入完毕， 写入文件
    void quit();
    void calendarFormat();
    void calendarShow(QString type, int x, int y);
    QString getDate(QString type);

    void setMaxLuRu(int max_LuRu);

    bool DeleteBlockNo(QString Block_NO);
    bool isLast_BlockNo();


public:
    Database        m_DB;
    QString         m_string;
    QStringList     m_StringList;

    QString m_CurrentLotNo;
    QString m_CurrentBlockNo;
    int m_CurrentMax_LuRu;
    QString m_LogFile2;

    QString m_checkCode;

    QCalendarWidget *m_Calendar;
    QString m_DateType;
    QString m_StartDate;
    QString m_EndDate;
};

#endif // DATAFILTER_H
