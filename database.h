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
    bool InsertSn(QString Sn, QString BlockNo, QString Location);

    void SearchLotNo(QString LotNo, QStringList *stringList);

    void SearchBlockNo(QString BlockNo, QStringList *stringList);

    void SearchSn(QString Sn, QStringList *stringList);

    QString GetLotNoByBlockNo(QString BlockNo);

    bool IsExistSn(QString SN);

    bool ClearSnByBlockNo(QString BlockNo);
private:
    QSqlDatabase m_Conn;
    QSqlQuery m_Query;
};

#endif // DATABASE_H
