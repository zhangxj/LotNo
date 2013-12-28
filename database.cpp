#include "database.h"


Database::Database()
{
    QString dbHost = "2012-20130121KO\\SQLEXPRESS";
    QString db = "barcode";
    QString user = "sa";
    QString pwd = "sasa";
    QString driver = "DRIVER={SQL SERVER};SERVER=" + dbHost + ";DATABASE=" + db;

    m_Conn = QSqlDatabase::addDatabase("QODBC");
    //QString dsn = QString::fromLocal8Bit(driver);
    m_Conn.setDatabaseName(driver);
    m_Conn.setUserName(user);
    m_Conn.setPassword(pwd);
    if(!m_Conn.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                m_Conn.lastError().text());
    }

    m_Query = QSqlQuery(m_Conn);
}

Database::~Database()
{
    m_Conn.close();
}

bool Database::ExecuteSQL(QString sql){
    return m_Query.exec(sql);
}

bool Database::InsertLotNo(QString LotNo)
{
    m_Query.prepare("insert into LOT_NO (LOT_NO) values (:LOT_NO)");
    m_Query.bindValue(0, LotNo);
    return m_Query.exec();
}

bool Database::InsertBlockNo(QString BlockNo, QString LotNo)
{
    m_Query.prepare("insert into BLOCK_NO (BLOCK_NO, LOT_NO) values (:BLOCK_NO, :LOT_NO)");
    m_Query.bindValue(0, BlockNo);
    m_Query.bindValue(1, LotNo);
    return m_Query.exec();
}

bool Database::InsertSn(QString Sn, QString BlockNo)
{
    m_Query.prepare("insert into SN (SN,BLOCK_NO) values (:SN, :BLOCK_NO)");
    m_Query.bindValue(0, Sn);
    m_Query.bindValue(1, BlockNo);
    return m_Query.exec();
}

void Database::SearchLotNo(QString LotNo,
                           QMap<QString, QSet<QString> > *LotNoMap,
                           QMap<QString, QSet<QString> > *BlockNoMap)
{
    m_Query.exec(QString("SELECT b.BLOCK_NO, s.SN from BLOCK_NO b, SN s where s.BLOCK_no = b.BLOCK_NO and LOT_NO = '%1'").arg(LotNo) );

    while(m_Query.next()){
        QString BlockNo = m_Query.value(0).toString();
        QString SN = m_Query.value(1).toString();
        InsertLotNoMap(LotNo, BlockNo, LotNoMap);
        InsertBLockNoMap(BlockNo, SN, BlockNoMap);
    }
}

void Database::SearchBlockNo(QString BlockNo,
                 QMap<QString, QSet<QString> > *LotNoMap,
                 QMap<QString, QSet<QString> > *BlockNoMap)
{

    m_Query.exec(QString("select b.LOT_NO, b.BLOCK_NO, s.SN from BLOCK_NO b, SN s where b.BLOCK_NO = S.BLOCK_NO AND S.BLOCK_NO = '%1'").arg(BlockNo));
    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();

        InsertLotNoMap(LotNo, BlockNo, LotNoMap);
        InsertBLockNoMap(BlockNo, SN, BlockNoMap);
    }
}

void Database::SearchSn(QString Sn,
                 QMap<QString, QSet<QString> > *LotNoMap,
                 QMap<QString, QSet<QString> > *BlockNoMap)
{
    m_Query.exec(QString("select b.LOT_NO, b.BLOCK_NO, s.SN from BLOCK_NO b, SN s where b.BLOCK_NO = S.BLOCK_NO AND S.SN = '%1'").arg(Sn));
    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();

        InsertLotNoMap(LotNo, BlockNo, LotNoMap);
        InsertBLockNoMap(BlockNo, SN, BlockNoMap);
    }
}

void Database::InsertLotNoMap(QString LotNo, QString BlockNo,
                              QMap<QString, QSet<QString> > *LotNoMap)
{
    if(LotNoMap->contains(LotNo)){
        QMap<QString, QSet<QString> >::Iterator it =  LotNoMap->find(LotNo);
        QSet<QString> *block_no_set = &(it.value());
        block_no_set->insert(BlockNo);
    }
    else{
        QSet<QString> b;
        b.insert(BlockNo);
        LotNoMap->insert(LotNo, b);
    }
}

void Database::InsertBLockNoMap(QString BlockNo, QString SN,
                                QMap<QString, QSet<QString> > *BlockNoMap)
{
    if(BlockNoMap->contains(BlockNo)){
        QMap<QString, QSet<QString> >::Iterator it = BlockNoMap->find(BlockNo);
        QSet<QString> *sn_set = &(it.value());
        sn_set->insert(SN);
    }else{
        QSet<QString> b;
        b.insert(SN);
        BlockNoMap->insert(BlockNo, b);
    }
}
