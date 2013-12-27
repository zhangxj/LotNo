#ifndef DATABASE_H
#define DATABASE_H
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QMap>
#include <QSet>

class Database
{
public:
    Database();
    ~Database();

public:
    bool ExecuteSQL(QString sql);
    bool InsertLotNo(QString LotNo);
    bool InsertBlockNo(QString BlockNo, QString LotNo);
    bool InsertSn(QString Sn, QString BlockNo);

    void SearchLotNo(QString LotNo,
                     QMap<QString, QSet<QString> > *LotNoMap,
                     QMap<QString, QSet<QString> > *BlockNoMap);

    void SearchBlockNo(QString BlockNo,
                     QMap<QString, QSet<QString> > *LotNoMap,
                     QMap<QString, QSet<QString> > *BlockNoMap);

    void SearchSn(QString Sn,
                     QMap<QString, QSet<QString> > *LotNoMap,
                     QMap<QString, QSet<QString> > *BlockNoMap);
private:
    QSqlDatabase m_Conn;
    QSqlQuery m_Query;
};

#endif // DATABASE_H
