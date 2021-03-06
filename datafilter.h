#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QMap>
#include <QSet>
#include <QVector>
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
    QString getBlockNo();
    bool showMessageBox(QString text, QString msg);
    QStringList getStringList();

    bool setScan(QString flag, QString no, QString Location, int sn_flag, QString product);
    bool setScan_1(QString flag, QString no, QString Location, int sn_flag, QString product);
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
    void setDBConfig_P2(QString ip, QString user, QString pwd,QString mss_ip, QString mss_user, QString mss_pwd,QString mss_db);
    void setBadMarkDBConfig(QString ip, QString user, QString pwd);
    QString getIp();
    QString getUser();
    QString getPwd();
    QString getMssIp();
    QString getMssUser();
    QString getMssPwd();
    QString getMssDB();

    QString getBadMarkIp();
    QString getBadMarkUser();
    QString getBadMarkPwd();
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
    bool isLast_BlockNo();

    void CheckItem(QString item);
    bool DeleteItem();
    bool DeleteSN();
    bool DeleteFanXiu();

    bool ChangeProductItem(QString item);

    int GetBlockNoLimitSettings();
    void SetBlockNoLimitSettings(int limit);
public:
    Database        m_DB;
    QString         m_string;
    QStringList     m_StringList;

    QString m_CurrentLotNo;
    QString m_CurrentBlockNo;
    QString m_Opt_ID;
    int m_CurrentMax_LuRu;
    QString m_LogFile2;

    QString m_checkCode;

    QCalendarWidget *m_Calendar;
    QString m_DateType;
    QString m_StartDate;
    QString m_EndDate;
    QStringList m_CheckItems;

    QString m_CurrentProduct;
    QString m_Product;

    QVector<int> m_IntList;
};

#endif // DATAFILTER_H
