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

    QString db = "barcode";
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

bool Database::isOpen()
{
    return m_Conn.isOpen();
}

void Database::close()
{
    if(m_Query.isActive()) m_Query.clear();
    if(m_Conn.isOpen()) m_Conn.close();
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

bool Database::InsertSn(QString Sn, QString BlockNo, QString Location, int FLAG)
{
    m_Query.prepare("insert into SN (SN, BLOCK_NO, Location, FLAG) values (:SN, :BLOCK_NO, :LOCATION, :FLAG)");
    m_Query.bindValue(0, Sn);
    m_Query.bindValue(1, BlockNo);
    m_Query.bindValue(2, Location);
    m_Query.bindValue(3, FLAG);
    return m_Query.exec();
}

void Database::SearchLotNo(QString LotNo, QStringList *stringList, int sn_flag)
{
    m_Query.exec(QString("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN, SN.LOCATION, SN.ADDON from LOT_NO "
                         "left join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO "
                         "where LOT_NO.LOT_NO = '%1' and sn.flag=%2").arg(LotNo).arg(sn_flag) );

    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Location = m_Query.value(3).toString();
        QString Addon = m_Query.value(4).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        if(sn_flag == 1 && BlockNo == LotNo){
            BlockNo = "";
        }
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon);
    }
}

void Database::SearchBlockNo(QString BlockNo, QStringList *stringList, int sn_flag)
{
    m_Query.exec(QString("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN, SN.LOCATION, SN.ADDON from LOT_NO "
                         "join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO "
                         "where BLOCK_NO.BLOCK_NO = '%1' and sn.flag=%2").arg(BlockNo).arg(sn_flag));
    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Location = m_Query.value(3).toString();
        QString Addon = m_Query.value(4).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon);
    }
}

void Database::SearchSn(QString Sn, QStringList *stringList, int sn_flag)
{
    m_Query.exec(QString("select b.LOT_NO, b.BLOCK_NO, s.SN, s.LOCATION, s.ADDON from BLOCK_NO b, SN s "
                         "where b.BLOCK_NO = S.BLOCK_NO "
                         "AND S.SN = '%1' and s.flag=%2").arg(Sn).arg(sn_flag));
    while(m_Query.next()){
        QString LotNo = m_Query.value(0).toString();
        QString BlockNo = m_Query.value(1).toString();
        QString SN = m_Query.value(2).toString();
        QString Location = m_Query.value(3).toString();
        QString Addon = m_Query.value(4).toString();
        QStringList qsl = Addon.split("T");
        Addon = qsl.join(" ");
        if(sn_flag == 1 && BlockNo == LotNo){
            BlockNo = "";
        }
        stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon);
    }
}

void Database::searchByDate(QString start, QString end, QStringList *stringList)
{
    if(SMF_Product == "SMF_P1"){
        m_Query.exec(QString("select b.LOT_NO, b.BLOCK_NO, s.SN, s.LOCATION, s.ADDON "
                         "from BLOCK_NO b, SN s "
                         "where b.BLOCK_NO = s.BLOCK_NO "
                         "AND s.ADDON >= '%1' and s.ADDON <= '%2' order by s.ADDON").arg(start + " 00:00:00").arg(end + " 23:59:59"));
        while(m_Query.next()){
            QString LotNo = m_Query.value(0).toString();
            QString BlockNo = m_Query.value(1).toString();
            QString SN = m_Query.value(2).toString();
            QString Location = m_Query.value(3).toString();
            QString Addon = m_Query.value(4).toString();
            QStringList qsl = Addon.split("T");
            Addon = qsl.join(" ");
            stringList->append(LotNo + "|" + BlockNo + "|" + SN + "|" + Location + "|" + Addon);
        }
    }else if(SMF_Product == "SMF_P2"){
        m_Query.exec(QString("select BLOCK_NO.LOT_NO, BLOCK_NO.BLOCK_NO, BLOCK_NO.ADDON "
                             "from BLOCK_NO "
                             "where BLOCK_NO.ADDON >= '%1' and BLOCK_NO.ADDON <= '%2' "
                             "order by BLOCK_NO.ADDON")
                     .arg(start + " 00:00:00").arg(end + " 23:59:59"));

        while(m_Query.next()){
            QString LotNo = m_Query.value(0).toString();
            QString BlockNo = m_Query.value(1).toString();
            QString Addon = m_Query.value(2).toString();
            QStringList qsl = Addon.split("T");
            Addon = qsl.join(" ");
            stringList->append(LotNo + "|" + BlockNo + "|" + Addon);
        }
    }else if(SMF_Product == "SMF_P3"){
        m_Query.exec(QString("select LOT_NO, BLOCK_NO, SN, ADDON "
                             "from FANXIU_SN "
                             "where ADDON >= '%1' and ADDON <= '%2' "
                             "order by ADDON")
                     .arg(start + " 00:00:00").arg(end + " 23:59:59"));
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
    m_Query.exec(QString("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, BLOCK_NO.ADDON from LOT_NO "
                         "left join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "where LOT_NO.LOT_NO = '%1'").arg(LotNo) );

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
    m_Query.exec(QString("select BLOCK_NO.LOT_NO, BLOCK_NO.BLOCK_NO, BLOCK_NO.ADDON from BLOCK_NO "
                         "where BLOCK_NO.BLOCK_NO = '%1'").arg(BlockNo));
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
    m_Query.exec(QString("select LOT_NO from BLOCK_NO "
                         "where BLOCK_NO='%1'").arg(BlockNo));

    while(m_Query.next()){
        return m_Query.value(0).toString();
    }

    return "";
}

bool Database::IsExistLotNoAndBlockNo(QString LotNo, QString BlockNo)
{
    m_Query.exec(QString("select * from BLOCK_NO where LOT_NO = '%1' and BLOCK_NO = '%2'").arg(LotNo).arg(BlockNo));

    while(m_Query.next())
        return true;

    return false;
}

bool Database::IsExistSn(QString SN)
{
    m_Query.exec(QString("select SN from SN where SN = '%1' and FLAG = 0").arg(SN));

    while(m_Query.next())
        return true;

    return false;
}

bool Database::IsExist(QString sql)
{
    m_Query.exec(sql);

    while(m_Query.next())
        return true;

    return false;
}
/*
 * 返修品录入
 */
bool Database::FanXiu_LR(QString LotNo, QString BlockNo, QString SN){
    ExecuteSQL(QString("insert into FANXIU_SN (LOT_NO, BLOCK_NO, SN) values ('%1', '%2', '%3')").arg(LotNo).arg(BlockNo).arg(SN));
    return true;
    QString sql = QString("SELECT * FROM FANXIU_SN WHERE LOT_NO = '%1' AND BLOCK_NO = '%2' ").arg(LotNo).arg(BlockNo);
    if(IsExist(sql)){
        ExecuteSQL(QString("update FANXIU_SN set SN = '%1' where LOT_NO = '%2' and BLOCK_NO = '%3'").arg(SN).arg(LotNo).arg(BlockNo));
    }else{
        ExecuteSQL(QString("insert into FANXIU_SN (LOT_NO, BLOCK_NO, SN) values ('%1', '%2', '%3')").arg(LotNo).arg(BlockNo).arg(SN));
    }
    return true;
}

void Database::SearchFanXiu(QString no, QString flag, QStringList *stringList)
{
    QString sql;
    if("lot_no" == flag){
        sql = QString("select LOT_NO, BLOCK_NO, SN, ADDON from FANXIU_SN where LOT_NO = '%1'").arg(no);
    }
    else if("block_no" == flag){
        sql = QString("select LOT_NO, BLOCK_NO, SN, ADDON from FANXIU_SN where BLOCK_NO = '%1'").arg(no);
    }
    else if("sn" == flag){
        sql = QString("select LOT_NO, BLOCK_NO, SN, ADDON from FANXIU_SN where SN = '%1'").arg(no);
    }

    ExecuteSQL(sql);
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

int Database::GetSnNumByBlockNo(QString BlockNo)
{
    QString sql = QString("select count(*) from SN where BLOCK_NO = '%1'").arg(BlockNo);
    ExecuteSQL(sql);
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

int Database::m_count(QString Sql)
{
    ExecuteSQL(Sql);
    while(m_Query.next()){
        return m_Query.value(0).toInt();
    }

    return 0;
}

bool Database::isLast_BlockNo(QString LotNo)
{
    m_Query.exec(QString("select BLOCK_NO from BLOCK_NO "
                         "where LOT_NO = '%1'").arg(LotNo) );
    QStringList l;
    while(m_Query.next()){
        QString BlockNo = m_Query.value(0).toString();
        l.append(BlockNo);
    }

    for(int i = 0; i < l.size(); i++){
        QString BlockNo = l.at(i);
        if(m_count(QString("select count(*) from SN where BLOCK_NO='%1'").arg(BlockNo)) == 0)
            return false;
    }

    return true;
}

