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

    void SearchLotNo(QString LotNo, QStringList *stringList, int sn_flag);
    void SearchBlockNo(QString BlockNo, QStringList *stringList, int sn_flag);
    void SearchSn(QString Sn, QStringList *stringList, int sn_flag);

    void SearchBlockNoByLotNO(QString LotNo, QStringList *stringList);
    void SearchBlockNoByBlockNo(QString BlockNo, QStringList *stringList);

    QString GetLotNoByBlockNo(QString BlockNo);

    bool IsExistSn(QString SN);

    bool ClearSnByBlockNo(QString BlockNo);
    bool ClearSn(QString SN);
private:
    QSqlDatabase m_Conn;
    QSqlQuery m_Query;
};

#endif // DATABASE_H
