#ifndef DATABASE_H
#define DATABASE_H
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

class Database
{
public:
    Database();
    ~Database();

public:
    bool InitDB();
    bool isOpen();
    void close();
    bool ExecuteSQL(QString sql);
    bool InsertLotNo(QString LotNo);
    bool InsertBlockNo(QString BlockNo, QString LotNo);
    bool InsertSn(QString Sn, QString BlockNo, QString Location, int FLAG);
    bool FanXiu_LR(QString LotNo, QString BlockNo, QString SN); //返修品录入
    void SearchFanXiu(QString no, QString flag, QStringList *stringList);

    void SearchLotNo(QString LotNo, QStringList *stringList, int sn_flag);
    void SearchBlockNo(QString BlockNo, QStringList *stringList, int sn_flag);
    void SearchSn(QString Sn, QStringList *stringList, int sn_flag);
    void searchByDate(QString start, QString end, QStringList *stringList);

    void SearchBlockNoByLotNO(QString LotNo, QStringList *stringList);
    void SearchBlockNoByBlockNo(QString BlockNo, QStringList *stringList);

    QString GetLotNoByBlockNo(QString BlockNo);

    bool IsExist(QString sql);
    bool IsExistSn(QString SN);
    bool IsExistLotNoAndBlockNo(QString LotNo, QString BlockNo);

    bool ClearSnByBlockNo(QString BlockNo);
    bool ClearSn(QString SN);
private:
    QSqlDatabase m_Conn;
    QSqlQuery m_Query;
};

#endif // DATABASE_H
