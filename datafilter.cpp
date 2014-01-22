#include "datafilter.h"
#include <QVariant>
#include "about.h"
#include <QNetworkInterface>
#include <QCryptographicHash>
#include <QSettings>

extern QString WindowTitle;

DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    m_checkCode = s->value("CODE/VALUE").toString();
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

QStringList DataFilter::getLotNoList()
{
    return m_LotNoList;
}

QStringList DataFilter::getBlockNoList()
{
    return m_BlockNoList;
}

QStringList DataFilter::getSnList()
{
    return m_SnList;
}

void DataFilter::selectItem(QString flag, QString no)
{
    if("lot_no" == flag){
        m_CurrentLotNo = no;
        m_BlockNoList.clear();
        m_SnList.clear();
        QSet< QString > block_no = m_LotNoMap.value(no);
        foreach (const QString &value, block_no) {
            m_BlockNoList.append(value);
            QSet< QString > sn = m_BlockNoMap.value(value);
            foreach (const QString &value, sn) {
                m_SnList.append(value);
            }
        }
        emit blockNoListChanged();
        emit snListChanged();
    }
    else if("block_no" == flag){
        m_CurrentBlockNo = no;
        m_SnList.clear();
        QSet< QString > sn = m_BlockNoMap.value(no);
        foreach (const QString &value, sn) {
            m_SnList.append(value);
        }
        emit snListChanged();
    }
}
void DataFilter::clearData()
{
    m_LotNoMap.clear();
    m_BlockNoMap.clear();
    m_LotNoList.clear();
    m_BlockNoList.clear();
    m_SnList.clear();

    m_CurrentLotNo = "";
    m_CurrentBlockNo = "";

    emit lotNoListChanged();
    emit blockNoListChanged();
    emit snListChanged();
}

void DataFilter::searchData(QString flag, QString no)
{
    if(no == "") return;

    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "Waining", "数据库连接异常 请配置", QMessageBox::Ok);
        return;
    }

    clearData();
    if("lot_no" == flag){
        qDebug() << flag << no << "search lotno";
        m_DB.SearchLotNo(no, &m_LotNoMap, &m_BlockNoMap);
    }
    else if("block_no" == flag){
        m_DB.SearchBlockNo(no, &m_LotNoMap, &m_BlockNoMap);
    }
    else if("sn" == flag){
        m_DB.SearchSn(no, &m_LotNoMap, &m_BlockNoMap);
    }

    QMap< QString, QSet<QString> >::Iterator it;
    for(it = m_LotNoMap.begin(); it != m_LotNoMap.end(); ++it){
        m_LotNoList.append(it.key());
        QSet< QString > block_no_set = it.value();

        foreach (const QString &value, block_no_set) {
            m_BlockNoList.append(value);
            QSet< QString > sn_set = m_BlockNoMap.value(value);
            foreach (const QString &value, sn_set) {
                m_SnList.append(value);
            }
        }
    }
    emit lotNoListChanged();
    emit blockNoListChanged();
    emit snListChanged();
}


void DataFilter::setScan(QString flag, QString no, QString Location)
{
    qDebug() << flag << no << Location;
    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "Waining", "数据库连接异常 请配置", QMessageBox::Ok);
        return;
    }

    no = no.trimmed();
    if(no == "") return;

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
            return;
        }

        QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);
        if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
            m_string = QString("Block No. %1 属于 %2")
                    .arg(no)
                    .arg(tmp_LotNO);
            QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
            return;
        }
        m_CurrentBlockNo = no;
        m_DB.InsertBlockNo(no, m_CurrentLotNo);
    }
    else if("sn" == flag){
        if( m_CurrentLotNo == "" || m_CurrentBlockNo == "" ){
            m_string = QString("请录入 SMF Lot No. Block No.");
            QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
            return;
        }

        if(no == "rescan" || no == "RESCAN"){
            m_DB.ClearSnByBlockNo(m_CurrentBlockNo);
            m_SnList.clear();
            emit snListChanged();
            return;
        }

        if( m_DB.IsExistSn(no)) {
            m_string = "数据已存在";
            emit stringChanged();
            return;
        }

        m_DB.InsertSn(no, m_CurrentBlockNo, Location);
        m_SnList.append(no + "|" + Location);
        emit snListChanged();
    }

    //selectItem(flag, no);
}

void DataFilter::OnAbout()
{
    /*
    QMessageBox::information(NULL, WindowTitle,
                            "条码录入系统 V1.0 " + tr("\r\n\nCopyright 深圳市菲尼曼特科技有限公司 2013"),
                            QMessageBox::Yes);
                            */

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText(WindowTitle + " V1.1                           ");
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
    msgBox.setText("当前操作将退出系统              ");
    msgBox.setInformativeText("确定退出?");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret == 0){
        exit(0);
    }
}
