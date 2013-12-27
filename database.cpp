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
        QString block_no = m_Query.value(0).toString();
        QString sn = m_Query.value(1).toString();

        if(LotNoMap->contains(LotNo)){
            QMap<QString, QSet<QString> >::Iterator it =  LotNoMap->find(LotNo);
            QSet<QString> *block_no_set = &(it.value());
            block_no_set->insert(block_no);
        }
        else{
            QSet<QString> b;
            b.insert(block_no);
            LotNoMap->insert(LotNo, b);
        }

        if(BlockNoMap->contains(block_no)){
            QMap<QString, QSet<QString> >::Iterator it = BlockNoMap->find(block_no);
            QSet<QString> *sn_set = &(it.value());
            sn_set->insert(sn);
        }else{
            QSet<QString> b;
            b.insert(sn);
            BlockNoMap->insert(block_no, b);
        }
    }
}

void Database::SearchBlockNo(QString BlockNo,
                 QMap<QString, QSet<QString> > *LotNoMap,
                 QMap<QString, QSet<QString> > *BlockNoMap)
{
    m_Query.exec(QString("select LOT_NO from BLOCK_NO where BLOCK_NO = '%1'").arg(BlockNo));
    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
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

    m_Query.exec(QString("select SN from SN where BLOCK_NO = '%1'").arg(BlockNo));
    while(m_Query.next()){
        QString sn = m_Query.value(0).toString();

        if(BlockNoMap->contains(BlockNo)){
            QMap<QString, QSet<QString> >::Iterator it = BlockNoMap->find(BlockNo);
            QSet<QString> *sn_set = &(it.value());
            sn_set->insert(sn);
        }else{
            QSet<QString> b;
            b.insert(sn);
            BlockNoMap->insert(BlockNo, b);
        }
    }
}

void Database::SearchSn(QString Sn,
                 QMap<QString, QSet<QString> > *LotNoMap,
                 QMap<QString, QSet<QString> > *BlockNoMap)
{
    m_Query.exec(QString("select BLOCK_NO from SN where SN = '%1'").arg(Sn));
    QString BlockNo;
    while(m_Query.next()){
        BlockNo = m_Query.value(0).toString();

        if(BlockNoMap->contains(BlockNo)){
            QMap<QString, QSet<QString> >::Iterator it = BlockNoMap->find(BlockNo);
            QSet<QString> *sn_set = &(it.value());
            sn_set->insert(Sn);
        }else{
            QSet<QString> b;
            b.insert(Sn);
            BlockNoMap->insert(BlockNo, b);
        }
    }

    m_Query.exec(QString("select LOT_NO from BLOCK_NO where BLOCK_NO = '%1'").arg(BlockNo));
    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();

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

}
