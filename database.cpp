#include "database.h"
#include <QSettings>

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

bool Database::InsertSn(QString Sn, QString BlockNo, QString Location)
{
    m_Query.prepare("insert into SN (SN, BLOCK_NO, Location, FLAG) values (:SN, :BLOCK_NO, :LOCATION, 0)");
    m_Query.bindValue(0, Sn);
    m_Query.bindValue(1, BlockNo);
    m_Query.bindValue(2, Location);
    return m_Query.exec();
}

void Database::SearchLotNo(QString LotNo, QStringList *stringList)
{
    m_Query.exec(QString("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN, SN.LOCATION, SN.ADDON from LOT_NO "
                         "left join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO "
                         "where LOT_NO.LOT_NO = '%1' and sn.flag=0").arg(LotNo) );

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

void Database::SearchBlockNo(QString BlockNo, QStringList *stringList)
{

    m_Query.exec(QString("select LOT_NO.LOT_NO, BLOCK_NO.BLOCK_NO, SN.SN, SN.LOCATION, SN.ADDON from LOT_NO "
                         "join BLOCK_NO on LOT_NO.LOT_NO = BLOCK_NO.LOT_NO "
                         "left join SN on BLOCK_NO.BLOCK_NO = SN.BLOCK_NO "
                         "where BLOCK_NO.BLOCK_NO = '%1' and sn.flag=0").arg(BlockNo));
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

void Database::SearchSn(QString Sn, QStringList *stringList)
{
    m_Query.exec(QString("select b.LOT_NO, b.BLOCK_NO, s.SN, s.LOCATION, s.ADDON from BLOCK_NO b, SN s "
                         "where b.BLOCK_NO = S.BLOCK_NO "
                         "AND S.SN = '%1' and s.flag=0").arg(Sn));
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

QString Database::GetLotNoByBlockNo(QString BlockNo)
{
    m_Query.exec(QString("select LOT_NO from BLOCK_NO "
                         "where BLOCK_NO='%1'").arg(BlockNo));

    while(m_Query.next()){
        return m_Query.value(0).toString();
    }

    return "";
}

bool Database::IsExistSn(QString SN)
{
    m_Query.exec(QString("select SN from SN where SN = '%1' and FLAG = 0").arg(SN));

    while(m_Query.next())
        return true;

    return false;
}

bool Database::ClearSnByBlockNo(QString BlockNo)
{
    m_Query.prepare("delete from SN where BLOCK_NO = :BLOCK_NO and flag = 0");
    m_Query.bindValue(0, BlockNo);
    return m_Query.exec();
}

bool Database::ClearSn(QString SN)
{
    m_Query.prepare("delete from SN where SN = :SN and flag = 0");
    m_Query.bindValue(0, SN);
    return m_Query.exec();
}

