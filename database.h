#ifndef DATABASE_H
#define DATABASE_H
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QVector>

class Database
{
public:
    Database();
    ~Database();

public:
    bool InitDB();
    bool InitMssDB();
    bool InitBadMarkDB();
    bool isOpen();
    bool isBadMarkOpen();
    void close();
    bool ExecuteSQL(QString sql, QString args1);
    bool InsertLotNo(QString LotNo);
    bool InsertBlockNo(QString BlockNo, QString LotNo);
    bool InsertSn(QString Sn, QString BlockNo, QString Location, int FLAG, QString product, QString opt_id);
    bool FanXiu_LR(QString LotNo, QString BlockNo, QString SN); //返修品录入
    void SearchFanXiu(QString no, QString flag, QStringList *stringList);

    void SearchLotNo(QString LotNo, QStringList *stringList, int sn_flag);
    void SearchBlockNo(QString BlockNo, QStringList *stringList, int sn_flag);
    void SearchSn(QString Sn, QStringList *stringList, int sn_flag);
    void searchByDate(QString start, QString end, QStringList *stringList);

    void SearchBlockNoByLotNO(QString LotNo, QStringList *stringList);
    void SearchBlockNoByBlockNo(QString BlockNo, QStringList *stringList);

    QString GetLotNoByBlockNo(QString BlockNo);
    QString GetBlockNoBySn(QString Sn);
    void GetSnListByBlockNo(QString BlockNo, QStringList *stringList);

    bool IsExistLotNo(QString LotNo);
    bool IsExistBlockNo(QString BlockNo);
    bool IsExistSn(QString SN);
    bool IsExistLotNoAndBlockNo(QString LotNo, QString BlockNo);

    bool ClearSnByBlockNo(QString BlockNo);
    int GetBlockNoNumByLotNo(QString LotNo);
    int GetSnNumByBlockNo(QString BlockNo);
    bool ClearSn(QString SN);

    int m_count();
    bool isLast_BlockNo(QString LotNo);

    void GetBadMarkSn(QString BlockNo, QVector<int> *intList);

    int GetBlockNoLimitSettings();
    void SetBlockNoLimitSettings(int limit);
    QString getMssConfig(QString LotNo);
private:
    QSqlDatabase m_Conn;
    QSqlQuery m_Query;
    QSqlDatabase m_BadMarkConn;
    QSqlDatabase m_MssConn;
    QSqlQuery m_BadMarkQuery;
};

#endif // DATABASE_H
