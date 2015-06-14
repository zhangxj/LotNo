#include "database.h"
#include <QSettings>

extern QString SMF_Product;
Database::Database()
{
    //if (! InitDB() ){
        //exit(0);
    //}
}

Database::~Database()
{
    if(m_Conn.isOpen()){
        m_Conn.close();
    }
}

bool Database::InitDB()
{
    QString sIniFilePath   = "config.ini";
    QSettings *s = new QSettings(sIniFilePath, QSettings::IniFormat);
    QString dbHost = s->value("DATABASE/IP").toString();
    QString user = s->value("DATABASE/USER").toString();
    QString pwd= s->value("DATABASE/PWD").toString();

    if(dbHost.isEmpty() || user.isEmpty() || pwd.isEmpty()){
        //QMessageBox::critical(0, QObject::tr("config Error"), "请配置数据库");
        return false;
    }

    QString db = "smf_barcode";
    QString driver = "DRIVER={SQL SERVER};SERVER=" + dbHost + ";DATABASE=" + db;

    m_Conn = QSqlDatabase::addDatabase("QODBC");
    m_Conn.setDatabaseName(driver);
    m_Conn.setUserName(user);
    m_Conn.setPassword(pwd);
    m_Conn.setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=1;SQL_ATTR_LOGIN_TIMEOUT=1");
    if(!m_Conn.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"), "数据库配置错误\r\n" + m_Conn.lastError().text());

            return false;
    }

    m_Query = QSqlQuery(m_Conn);
    return true;
}

bool Database::InitBadMarkDB()
{
    QString sIniFilePath   = "config.ini";
    QSettings *s = new QSettings(sIniFilePath, QSettings::IniFormat);
    QString dbHost = s->value("BadMark/IP").toString();
    QString user = s->value("BadMark/USER").toString();
    QString pwd= s->value("BadMark/PWD").toString();

    if(dbHost.isEmpty() || user.isEmpty() || pwd.isEmpty()){
        QMessageBox::critical(0, QObject::tr("config Error"), "请配置BadMark数据库");
        return false;
    }

    QString db = "BadMark";
    QString driver = "DRIVER={SQL SERVER};SERVER=" + dbHost + ";DATABASE=" + db;

    m_BadMarkConn = QSqlDatabase::addDatabase("QODBC", "BadMark");
    m_BadMarkConn.setDatabaseName(driver);
    m_BadMarkConn.setUserName(user);
    m_BadMarkConn.setPassword(pwd);
    m_BadMarkConn.setConnectOptions("SQL_ATTR_CONNECTION_TIMEOUT=1;SQL_ATTR_LOGIN_TIMEOUT=1");
    if(!m_BadMarkConn.open()) {
            QMessageBox::critical(0, QObject::tr("Database Error"), "数据库配置错误\r\n" + m_BadMarkConn.lastError().text());

            return false;
    }

    m_BadMarkQuery = QSqlQuery(m_BadMarkConn);
    return true;
}


bool Database::isOpen()
{
    return m_Conn.isOpen();
}

bool Database::isBadMarkOpen()
{
    return m_BadMarkConn.isOpen();
}

void Database::close()
{
    if(m_Query.isActive()) m_Query.clear();
    if(m_Conn.isOpen()) m_Conn.close();
}

bool Database::ExecuteSQL(QString sql, QString args1){
    m_Query.prepare(sql);
    m_Query.bindValue(0, args1);
    return m_Query.exec();
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

bool Database::InsertSn(QString Sn, QString BlockNo, QString Location, int FLAG, QString product, QString opt_id)
{
    m_Query.prepare("insert into SN (SN, BLOCK_NO, Location, FLAG, PRODUCT, opt_id) values (:SN, :BLOCK_NO, :LOCATION, :FLAG, :PRODUCT, :OPT_ID)");
    m_Query.bindValue(0, Sn);
    m_Query.bindValue(1, BlockNo);
    m_Query.bindValue(2, Location);
    m_Query.bindValue(3, FLAG);
    m_Query.bindValue(4, product);
    m_Query.bindValue(5, opt_id);
    return m_Query.exec();
}

void Database::SearchLotNo(QString LotNo, QStringList *stringList, int sn_flag)
{
    m_Query.prepare("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN, SN.LOCATION, SN.ADDON, SN.PRODUCT, SN.OPT_ID from LOT_NO "
                         "left join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO "
                         "where LOT_NO.LOT_NO = :LOT_NO and sn.flag=:FLAG");
    m_Query.bindValue(0, LotNo);
    m_Query.bindValue(1, sn_flag);

    m_Query.exec();

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Location = m_Query.value(3).toString();
        QString Addon = m_Query.value(4).toString();
        QString product = m_Query.value(5).toString();
//        QString opt_id = "";
//        if(m_Query.value(6))
        QString opt_id = m_Query.value(6).toString();
//        else
//            opt_id = "";

        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        if(sn_flag == 1 && BlockNo == LotNo){
            BlockNo = "";
        }
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon + "|" + product + "|" + opt_id);
    }
}

void Database::SearchBlockNo(QString BlockNo, QStringList *stringList, int sn_flag)
{
    m_Query.prepare("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN, SN.LOCATION, SN.ADDON, SN.PRODUCT, SN.OPT_ID from LOT_NO "
                         "join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO "
                         "where BLOCK_NO.BLOCK_NO = :BLOCK_NO");

    m_Query.bindValue(0, BlockNo);
    m_Query.exec();

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Location = m_Query.value(3).toString();
        QString Addon = m_Query.value(4).toString();
        QString product = m_Query.value(5).toString();
        QString opt_id = m_Query.value(6).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon + "|" + product + "|" + opt_id);
    }
}

void Database::SearchSn(QString Sn, QStringList *stringList, int sn_flag)
{
    m_Query.prepare("select b.LOT_NO, b.BLOCK_NO, s.SN, s.LOCATION, s.ADDON, s.PRODUCT, s.OPT_ID from BLOCK_NO b, SN s "
                         "where b.BLOCK_NO = S.BLOCK_NO "
                         "AND S.SN = :SN");

    m_Query.bindValue(0, Sn);
    m_Query.exec();

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Location = m_Query.value(3).toString();
        QString Addon = m_Query.value(4).toString();
        QString product = m_Query.value(5).toString();
        QString opt_id = m_Query.value(6).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        if(sn_flag == 1 && BlockNo == LotNo){
            BlockNo = "";
        }
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon + "|" + product + "|" + opt_id);
    }
}


QString Database::GetBlockNoBySn(QString Sn)
{
    m_Query.prepare("select BLOCK_NO from SN where SN = :SN");
    m_Query.bindValue(0, Sn);
    m_Query.exec();


    while(m_Query.next()){
        QString BlockNo = m_Query.value(0).toString();
        return BlockNo;
    }
    return "";
}

void Database::GetSnListByBlockNo(QString BlockNo, QStringList *stringList)
{
    m_Query.prepare("select SN from SN where BLOCK_NO = :BLOCK_NO");
    m_Query.bindValue(0, BlockNo);
    m_Query.exec();


    while(m_Query.next()){
        QString SN = m_Query.value(0).toString();
        stringList->append(SN);
    }
}

void Database::searchByDate(QString start, QString end, QStringList *stringList)
{
    if(SMF_Product == "SMF_P1"){
        m_Query.prepare("select b.LOT_NO, b.BLOCK_NO, s.SN, s.LOCATION, s.ADDON, s.PRODUCT "
                         "from BLOCK_NO b, SN s "
                         "where b.BLOCK_NO = s.BLOCK_NO "
                         "AND s.ADDON >= :ADDON1 and s.ADDON <= :ADDON2 order by s.ADDON");

        m_Query.bindValue(0, start + " 00:00:00");
        m_Query.bindValue(1, end + " 23:59:59");
        m_Query.exec();

        while(m_Query.next()){
            QString LotNo = m_Query.value(0).toString();
            QString BlockNo = m_Query.value(1).toString();
            QString SN = m_Query.value(2).toString();
            QString Location = m_Query.value(3).toString();
            QString Addon = m_Query.value(4).toString();
            QString product = m_Query.value(5).toString();
            QStringList qsl = Addon.split("T");
            Addon = qsl.join(" ");
            stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon + "|" + product);
        }
    }else if(SMF_Product == "SMF_P2"){
        m_Query.prepare("select BLOCK_NO.LOT_NO, BLOCK_NO.BLOCK_NO, BLOCK_NO.ADDON "
                             "from BLOCK_NO "
                             "where BLOCK_NO.ADDON >= :ADDON1 and BLOCK_NO.ADDON <= :ADDON2 "
                             "order by BLOCK_NO.ADDON");

        m_Query.bindValue(0, start + " 00:00:00");
        m_Query.bindValue(1, end + " 23:59:59");
        m_Query.exec();

        while(m_Query.next()){
            QString LotNo = m_Query.value(0).toString();
            QString BlockNo = m_Query.value(1).toString();
            QString Addon = m_Query.value(2).toString();
            QStringList qsl = Addon.split("T");
            Addon = qsl.join(" ");
            stringList->append(LotNo + "|" + BlockNo + "|" + Addon);
        }
    }else if(SMF_Product == "SMF_P3"){
        m_Query.prepare("select LOT_NO, BLOCK_NO, SN, ADDON "
                             "from FANXIU_SN "
                             "where ADDON >= :ADDON1 and ADDON <= :ADDON2 "
                             "order by ADDON");

        m_Query.bindValue(0, start + " 00:00:00");
        m_Query.bindValue(1, end + " 23:59:59");
        m_Query.exec();

        while(m_Query.next()){
            QString LotNo = m_Query.value(0).toString();
            QString BlockNo = m_Query.value(1).toString();
            QString SN = m_Query.value(2).toString();
            QString Addon = m_Query.value(3).toString();
            QStringList qsl = Addon.split("T");
            Addon = qsl.join(" ");
            stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + "" + "|" + Addon);
        }
    }

}

void Database::SearchBlockNoByLotNO(QString LotNo, QStringList *stringList)
{
    /*
    m_Query.prepare("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, BLOCK_NO.ADDON from LOT_NO "
                         "left join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "where LOT_NO.LOT_NO = :LOT_NO");
                         */

    m_Query.prepare("select LOT_NO, BLOCK_NO, ADDON from BLOCK_NO where LOT_NO=:LOT_NO");

    m_Query.bindValue(0, LotNo);
    m_Query.exec();

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString Addon = m_Query.value(2).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        stringList->append(LotNo + "|" + BlockNo + "|" + Addon);
    }
}

void Database::SearchBlockNoByBlockNo(QString BlockNo, QStringList *stringList)
{
    m_Query.prepare("select BLOCK_NO.LOT_NO, BLOCK_NO.BLOCK_NO, BLOCK_NO.ADDON from BLOCK_NO "
                         "where BLOCK_NO.BLOCK_NO = :BLOCK_NO");


    m_Query.bindValue(0, BlockNo);
    m_Query.exec();

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString Addon = m_Query.value(2).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        stringList->append(LotNo + "|" + BlockNo + "|" + Addon);
    }
}

QString Database::GetLotNoByBlockNo(QString BlockNo)
{
    m_Query.prepare("select LOT_NO from BLOCK_NO "
                         "where BLOCK_NO=:BLOCK_NO");


    m_Query.bindValue(0, BlockNo);
    m_Query.exec();
\
    while(m_Query.next()){
        return m_Query.value(0).toString();
    }

    return "";
}

bool Database::IsExistLotNoAndBlockNo(QString LotNo, QString BlockNo)
{
    m_Query.prepare("select * from BLOCK_NO where LOT_NO = :LOT_NO and BLOCK_NO = :BLOCK_NO");


    m_Query.bindValue(0, LotNo);
    m_Query.bindValue(1, BlockNo);
    m_Query.exec();

    while(m_Query.next())
        return true;

    return false;
}

bool Database::IsExistSn(QString SN)
{
    m_Query.prepare("select SN from SN where SN = :SN and FLAG = 0");

    m_Query.bindValue(0, SN);
    m_Query.exec();

    while(m_Query.next())
        return true;

    return false;
}

bool Database::IsExistLotNo(QString LotNo)
{
    m_Query.prepare("select * from LOT_NO where LOT_NO=:LOT_NO");
    m_Query.bindValue(0, LotNo);
    m_Query.exec();

    while(m_Query.next())
        return true;

    return false;
}


bool Database::IsExistBlockNo(QString BlockNo)
{
    m_Query.prepare("select * from BLOCK_NO where BLOCK_NO=:BLOCK_NO");
    m_Query.bindValue(0, BlockNo);
    m_Query.exec();

    while(m_Query.next())
        return true;

    return false;
}
/*
 * 返修品录入
 */
bool Database::FanXiu_LR(QString LotNo, QString BlockNo, QString SN){
    m_Query.prepare("insert into FANXIU_SN (LOT_NO, BLOCK_NO, SN) values (:LOT_NO, :BLOCK_NO, :SN)");
    m_Query.bindValue(0, LotNo);
    m_Query.bindValue(1, BlockNo);
    m_Query.bindValue(2, SN);
    m_Query.exec();
    return true;
}

void Database::SearchFanXiu(QString no, QString flag, QStringList *stringList)
{
    QString sql;
    if("lot_no" == flag){
        m_Query.prepare("select LOT_NO, BLOCK_NO, SN, ADDON from FANXIU_SN where LOT_NO = :LOT_NO");
    }
    else if("block_no" == flag){
        m_Query.prepare("select LOT_NO, BLOCK_NO, SN, ADDON from FANXIU_SN where BLOCK_NO = :BLOCK_NO");
    }
    else if("sn" == flag){
        m_Query.prepare("select LOT_NO, BLOCK_NO, SN, ADDON from FANXIU_SN where SN = :SN");
    }
    m_Query.bindValue(0, no);
    m_Query.exec();

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Addon = m_Query.value(3).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + "" + "|" + Addon);
    }
}

bool Database::ClearSnByBlockNo(QString BlockNo)
{
    m_Query.prepare("delete from SN where BLOCK_NO = :BLOCK_NO and flag = 0");
    m_Query.bindValue(0, BlockNo);
    return m_Query.exec();
}

int Database::GetBlockNoNumByLotNo(QString LotNo)
{
    m_Query.prepare("select count(*) from BLOCK_NO where LOT_NO = :LOT_NO");
    m_Query.bindValue(0, LotNo);
    m_Query.exec();

    while(m_Query.next()){
        return m_Query.value(0).toInt();
    }

    return 0;
}

int Database::GetSnNumByBlockNo(QString BlockNo)
{
    m_Query.prepare("select count(*) from SN where BLOCK_NO = :BLOCK_NO");
    m_Query.bindValue(0, BlockNo);
    m_Query.exec();

    while(m_Query.next()){
        return m_Query.value(0).toInt();
    }

    return 0;
}

bool Database::ClearSn(QString SN)
{
    m_Query.prepare("delete from SN where SN = :SN and flag = 0");
    m_Query.bindValue(0, SN);
    return m_Query.exec();
}

int Database::m_count()
{
    m_Query.exec();
    while(m_Query.next()){
        return m_Query.value(0).toInt();
    }

    return 0;
}

bool Database::isLast_BlockNo(QString LotNo)
{
    m_Query.prepare("select BLOCK_NO from BLOCK_NO "
                         "where LOT_NO = :LOT_NO");

    m_Query.bindValue(0, LotNo);
    m_Query.exec();
    QStringList l;
    while(m_Query.next()){
        QString BlockNo = m_Query.value(0).toString();
        l.append(BlockNo);
    }

    for(int i = 0; i < l.size(); i++){
        QString BlockNo = l.at(i);
        m_Query.prepare("select count(*) from SN where BLOCK_NO=:BLOCK_NO");
        m_Query.bindValue(0, BlockNo);
        if(m_count() == 0)
            return false;
    }

    return true;
}

void Database::GetBadMarkSn(QString PanelId, QVector<int> *intList){
    m_BadMarkQuery.prepare("select BadMarkSeq from valorQM "
                         "where PanelId = :PanelId");

    m_BadMarkQuery.bindValue(0, PanelId);
    m_BadMarkQuery.exec();

    while(m_BadMarkQuery.next()){
        int sn = m_BadMarkQuery.value(0).toInt();
        intList->append(sn);
    }
}
