#include "datafilter.h"
#include <QVariant>
#include "about.h"
#include <QNetworkInterface>
#include <QCryptographicHash>
#include <QSettings>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#define LOG_DIR  "Log format"
#define LOG_DIR_1 "Log for Panel Registration"
#define LOG_DIR_2 "Log for PanelBlockLinking"
extern QString WindowTitle;
extern QString Version;
extern QString SMF_Product;

DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    m_checkCode = s->value("CODE/VALUE").toString();
    createLogDir();
    m_string = "hello";
}

QString DataFilter::getIp()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/IP").toString();
}

QString DataFilter::getUser()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/USER").toString();
}

QString DataFilter::getPwd()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/PWD").toString();
}

void DataFilter::createLogDir()
{
    QDir d(getDirPath() + "\\" + LOG_DIR);
    if(!d.exists()){
        d.mkdir(getDirPath() + "\\" + LOG_DIR);
    }

    if(SMF_Product == "SMF_P2"){
        QDir d1(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_1);
        if(!d1.exists()){
            d1.mkdir(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_1);
        }
    }

    if(SMF_Product == "SMF_P1"){
        QDir d2(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_2);
        if(!d2.exists()){
            d2.mkdir(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_2);
        }
    }
}

QString DataFilter::getDirPath()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    QString path = s->value("SAVE/PATH").toString();
    if(path == ""){
        path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    }
    return path;

}

QString DataFilter::setFilePath()
{
    QFileDialog *fileDialog = new QFileDialog();
    fileDialog->setDirectory(getDirPath());
    QString path = fileDialog->getExistingDirectory();
    if(path != ""){
        QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
        s->setValue("SAVE/PATH", path);
    }
    createLogDir();
    return getDirPath();
}


void DataFilter::setDBConfig(QString ip, QString user, QString pwd)
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    s->setValue("DATABASE/IP", ip);
    s->setValue("DATABASE/USER", user);
    s->setValue("DATABASE/PWD", pwd);

    if(m_DB.isOpen()){
        m_DB.close();
    }

    if(m_DB.InitDB()){
        m_string = "数据库连接成功!";

    }else{
        m_string = "数据库连接失败!";
    }
    emit stringChanged();
}

QString DataFilter::CheckDB()
{
    if(!m_DB.isOpen() && !m_DB.InitDB())
    {
        m_string = "数据库连接失败!";
    }else{
        m_string = "数据库连接成功!";
    }
    emit stringChanged();
    return m_string;
}

QString DataFilter::JiaMi(QString code)
{
    QString r;
    QByteArray ba = code.toLatin1();

    for(int i = 0; i<ba.length(); i++){
        if(ba[i] >= 'A' && ba[i] <='Z'){
            ba[i] = ba[i] + 33;
        }else if(ba[i] >= 'b'&& ba[i] <= 'z'){
            ba[i] = ba[i] - 32;
        }else if(ba[i] >= '0'&& ba[i] <= '7'){
            ba[i] = ba[i] + 2;
        }
    }
    QCryptographicHash md(QCryptographicHash::Md5);
    md.addData(ba);
    r.append(md.result().toHex());
    return r;
}

void DataFilter::FirstCheck()
{
    QString src = getHardMD5();
    QString jiami = JiaMi(src);
    if(m_checkCode != jiami){
        emit checkCodeError();
    }else{
        emit checkCodeOk();
    }
}

void DataFilter::checkCode(QString code)
{
    QString src = getHardMD5();
    QString jiami = JiaMi(src);

    if(jiami == code){
        QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
        s->setValue("CODE/VALUE", code);
        emit checkCodeOk();
    }else{
        QMessageBox::critical(NULL, "错误", "请向厂家索要校验码", QMessageBox::Ok);
        emit checkCodeError();
    }
}

QString DataFilter::getHardMD5()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    QString mac;
    foreach (QNetworkInterface i, list) {
        mac = mac + i.hardwareAddress();
    }
    mac = list.at(1).hardwareAddress();
    mac = mac + SMF_Product;
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(mac);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());
    return md5;
}

QString DataFilter::getString()
{
    return m_string;
}

QStringList DataFilter::getStringList()
{
    return m_StringList;
}

void DataFilter::clearData()
{
    m_StringList.clear();

    m_CurrentLotNo = "";
    m_CurrentBlockNo = "";

    emit stringListChanged();
}

void DataFilter::clearBlockNo()
{
    m_StringList.clear();
    m_CurrentBlockNo = "";
    emit stringListChanged();
}

void DataFilter::searchData(QString flag, QString no, int sn_flag)
{
    if(no == "") return;

    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "Waining", "数据库连接异常 请配置", QMessageBox::Ok);
        return;
    }

    clearData();
    if(sn_flag == 0){
        if("lot_no" == flag){
            m_DB.SearchLotNo(no, &m_StringList, sn_flag);
        }
        else if("block_no" == flag){
            m_DB.SearchBlockNo(no, &m_StringList, sn_flag);
        }
        else if("sn" == flag){
            m_DB.SearchSn(no, &m_StringList, sn_flag);
        }
    }else if(sn_flag == 1){
        m_DB.SearchFanXiu(no, flag, &m_StringList);
    }

    emit stringListChanged();
}


bool DataFilter::setScan(QString flag, QString no, QString Location, int sn_flag)
{
    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "Waining", "数据库连接异常 请配置", QMessageBox::Ok);
        return false;
    }

    no = no.trimmed();
    if(no == "") return false;

    m_string = "";
    emit stringChanged();

    if(sn_flag == 0){
        if("lot_no" == flag){
            m_CurrentLotNo = no;
            m_DB.InsertLotNo(no);
        }else if("block_no" == flag){
            if(m_CurrentLotNo == "") {
                m_string = QString("请先录入 SMF Lot No.");
                QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
                return false;
            }
            QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);
            if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
                m_string = QString("Block No. %1 属于 %2")
                        .arg(no)
                        .arg(tmp_LotNO);
                QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
                return false;
            }
            m_CurrentBlockNo = no;

            if(!m_DB.IsExistLotNoAndBlockNo(m_CurrentLotNo, no)){
                m_DB.InsertBlockNo(no, m_CurrentLotNo);
            }
        }else if("sn" == flag){
            if( m_CurrentLotNo == "" || m_CurrentBlockNo == "" ){
                m_string = QString("请录入 SMF Lot No. Block No.");
                QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
                return false;
            }else if(no == "rescan" || no == "RESCAN"){
                m_DB.ClearSnByBlockNo(m_CurrentBlockNo);
                m_StringList.clear();
                emit stringListChanged();
                return true;
            }else if( no == "nosample" || no == "NOSAMPLE" ){
                m_StringList.append(no + "|" + Location);
                emit stringListChanged();
                return true;
            }else if( no == "newblock" || no == "NEWBLOCK" ){
                clearBlockNo();
                return true;
            }else if( no == "delete" || no == "DELETE" ){
                if( m_StringList.size() > 0 ){
                    QString del_sn = m_StringList.back();
                    m_StringList.pop_back();
                    del_sn = del_sn.split("|")[0];
                    m_DB.ClearSn(del_sn);
                }
                emit stringListChanged();
                return true;
            }

            if(m_DB.IsExistSn(no)) {
                m_string = "数据已存在";
                emit stringChanged();
                return false;
            }

            m_DB.InsertSn(no, m_CurrentBlockNo, Location, sn_flag);
            m_StringList.append(no + "|" + Location);

            emit stringListChanged();
        }
    }else if(sn_flag == 1){
        if("lot_no" == flag){
            m_CurrentLotNo = no;
        }
        else if("block_no" == flag){
            if(m_CurrentLotNo == "") {
                m_string = QString("请先录入 SMF Lot No.");
                QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
                return false;
            }
            m_CurrentBlockNo = no;
        }
        else if("sn" == flag){
            m_DB.FanXiu_LR(m_CurrentLotNo, m_CurrentBlockNo, no);
            m_StringList.append(no + "|" + Location);
            emit stringListChanged();
        }
    }
    return true;
}

void DataFilter::SNLuRuDone()
{
    QDateTime dt = QDateTime::currentDateTime();
    m_LogFile2 = m_CurrentBlockNo + "_" + dt.toString("yyyyMMddhhmmss") + ".txt";
    for(int i = 0; i < m_StringList.size(); i++){
        QString str = m_StringList.at(i);
        QStringList l = str.split("|");
        saveLog2(m_CurrentLotNo, m_CurrentBlockNo, l[0], l[1]);
    }
}

void DataFilter::saveLog1(QString LotNo, QString BlockNo)
{
    QDir d(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_1);
    QDateTime dt = QDateTime::currentDateTime();
    QString fileName = BlockNo + "_" + dt.toString("yyyyMMddhhmmss") + ".txt";
    QFile f(d.filePath(fileName));
    f.open(QIODevice::ReadWrite);
    QString msg = LotNo + "," + BlockNo + "," + dt.toString("yyyy-MM-dd hh:mm:ss");
    QTextStream in(&f);
    in << "LotID,PanelID,CreateDateTime" << "\r\n" << msg << "\r\n";
    f.close();
}

void DataFilter::saveLog2(QString LotNo, QString BlockNo, QString SN, QString Location)
{
    QDir d(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_2);
    QDateTime dt = QDateTime::currentDateTime();
    QString fileName = m_LogFile2;
    QFile f(d.filePath(fileName));

    QString msg = LotNo + "," + BlockNo + "," + Location + "," + SN + "," + dt.toString("yyyy-MM-dd hh:mm:ss");

    if(f.exists()){
        f.open(QIODevice::Append);
    }else {
        f.open(QIODevice::ReadWrite);
        msg = "LotID,PanelID,SequenceID,BlockSN,CreateDateTime\r\n" + msg;
    }

    QTextStream in(&f);
    in << msg << "\r\n";
    f.close();
}

bool DataFilter::record_LotNoBlockNo(QString flag, QString no)
{
    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "Waining", "数据库连接异常 请配置", QMessageBox::Ok);
        return false;
    }

    no = no.trimmed();
    if(no == "") return false;

    m_string = "";
    emit stringChanged();

    if("lot_no" == flag){
        m_CurrentLotNo = no;
        m_DB.InsertLotNo(no);
    }
    else if("block_no" == flag){
        if(m_CurrentLotNo == "") {
            m_string = QString("请先录入 SMF Lot No.");
            QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
            return false;
        }

        QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);
        if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
            m_string = QString("Block No. %1 属于 %2")
                    .arg(no)
                    .arg(tmp_LotNO);
            QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
            return false;
        }

        m_CurrentBlockNo = no;
        if(! m_DB.InsertBlockNo(no, m_CurrentLotNo)){
            m_string = "数据已存在";
            emit stringChanged();
            return false;
        }

        saveLog1(m_CurrentLotNo, no);
        m_StringList.append(m_CurrentLotNo + "|" + no);
    }

    emit stringListChanged();
    return true;
}

void DataFilter::searchLotNoBlockNo(QString flag, QString no)
{
    if(no == "") return;

    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "Waining", "数据库连接异常 请配置", QMessageBox::Ok);
        return;
    }

    clearData();
    if("lot_no" == flag){
        m_DB.SearchBlockNoByLotNO(no, &m_StringList);
    }else if("block_no" == flag){
        m_DB.SearchBlockNoByBlockNo(no, &m_StringList);
    }

    emit stringListChanged();
}

void DataFilter::OnAbout()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText(WindowTitle + " " + Version + "                            ");
    msgBox.setInformativeText("Copyright 深圳市菲尼曼特科技有限公司 2013");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.exec();
    /*
    About *ab = new About();
    ab->setSource(QUrl("qml/LotNo/about.qml"));
    ab->show();
    */
}

void DataFilter::quit()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText("当前操作将退出系统                 ");
    msgBox.setInformativeText("确定退出?");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret == 0){
        exit(0);
    }
}
