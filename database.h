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
    bool InitDB();
    bool isOpen();
    void close();
    bool ExecuteSQL(QString sql);
    bool InsertLotNo(QString LotNo);
    bool InsertBlockNo(QString BlockNo, QString LotNo);
    bool InsertSn(QString Sn, QString BlockNo);

    void SearchLotNo(QString LotNo,
                     QMap<QString, QSet<QString> > *LotNoMap,
                     QMap<QString, QStringList > *BlockNoMap);

    void SearchBlockNo(QString BlockNo,
                     QMap<QString, QSet<QString> > *LotNoMap,
                     QMap<QString, QStringList > *BlockNoMap);

    void SearchSn(QString Sn,
                     QMap<QString, QSet<QString> > *LotNoMap,
                     QMap<QString, QStringList > *BlockNoMap);

    void InsertLotNoMap(QString LotNo, QString BlockNo,
                        QMap<QString, QSet<QString> > *LotNoMap);

    void InsertBlockNoMap(QString BlockNo, QString SN,
                          QMap<QString, QStringList > *BlockNoMap);

    QString GetLotNoByBlockNo(QString BlockNo);

    bool IsExistSn(QString SN);
private:
    QSqlDatabase m_Conn;
    QSqlQuery m_Query;
};

#endif // DATABASE_H
