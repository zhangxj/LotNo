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
#include <windows.h>

#define LOG_DIR  "Logformat"
#define LOG_DIR_1 "LogforPanelRegistration"
#define LOG_DIR_2 "LogforPanelBlockLinking"
extern QString WindowTitle;
extern QString Version;
extern QString SMF_Product;

DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    m_checkCode = s->value("CODE/VALUE").toString();
    m_Calendar = new QCalendarWidget();
    m_Calendar->setWindowTitle(WindowTitle);
    m_Calendar->setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(m_Calendar, SIGNAL(selectionChanged()), this, SLOT(calendarFormat()));

    createLogDir();
    m_string = "hello";
}


QString DataFilter::getBlockNo()
{
    return m_CurrentBlockNo;
}

bool DataFilter::showMessageBox(QString text, QString msg)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText(text + "                        ");
    msgBox.setInformativeText(msg);
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret == 0){
        return true;
    }
    return false;
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

QString DataFilter::getMssIp()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/MSS_IP").toString();
}

QString DataFilter::getMssUser()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/MSS_USER").toString();
}

QString DataFilter::getMssPwd()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/MSS_PWD").toString();
}
QString DataFilter::getMssDB()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("DATABASE/MSS_DB").toString();
}

QString DataFilter::getBadMarkIp()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("BadMark/IP").toString();
}

QString DataFilter::getBadMarkUser()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("BadMark/USER").toString();
}

QString DataFilter::getBadMarkPwd()
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    return s->value("BadMark/PWD").toString();
}

int DataFilter::GetBlockNoLimitSettings(){
    return m_DB.GetBlockNoLimitSettings();
}

void DataFilter::SetBlockNoLimitSettings(int limit){
    m_DB.SetBlockNoLimitSettings(limit);
    QMessageBox::information(NULL, "提示", "设置成功", QMessageBox::Ok);
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


void DataFilter::setDBConfig(QString ip, QString user, QString pwd,QString mss_ip, QString mss_user, QString mss_pwd, QString mss_db)
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    s->setValue("DATABASE/IP", ip);
    s->setValue("DATABASE/USER", user);
    s->setValue("DATABASE/PWD", pwd);

    s->setValue("DATABASE/MSS_IP", mss_ip);
    s->setValue("DATABASE/MSS_USER", mss_user);
    s->setValue("DATABASE/MSS_PWD", mss_pwd);
    s->setValue("DATABASE/MSS_DB", mss_db);
    if(m_DB.isOpen()){
        m_DB.close();
    }

    m_string = "数据库连接成功!";
    if(SMF_Product == "SMF_P2"){
        if(!m_DB.InitDB() || !m_DB.InitMssDB()){
            m_string = m_string = "数据库连接失败!";
        }
    }else{
        if(!m_DB.InitDB())
        {
            m_string = "数据库连接失败!";
        }
    }

    emit stringChanged();
}

void DataFilter::setBadMarkDBConfig(QString ip, QString user, QString pwd)
{
    QSettings *s = new QSettings("config.ini", QSettings::IniFormat);
    s->setValue("BadMark/IP", ip);
    s->setValue("BadMark/USER", user);
    s->setValue("BadMark/PWD", pwd);

    if(m_DB.InitBadMarkDB()){
        m_string = "数据库连接成功!";

    }else{
        m_string = "数据库连接失败!";
    }
    emit stringChanged();
}

QString DataFilter::CheckDB()
{
    m_string = "数据库连接成功!";
    if(SMF_Product == "SMF_P2"){
        if(!m_DB.InitDB() || !m_DB.InitMssDB()){
            m_string = m_string = "数据库连接失败!";
        }
    }else{
        if(!m_DB.InitDB())
        {
            m_string = "数据库连接失败!";
        }
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
    //SYSTEM_INFO info;
    //GetSystemInfo(&info);
    //qDebug() << info.lpMaximumApplicationAddress;
    QString lpRootPathName = "C:\\";
    LPTSTR lpVolumeNameBuffer = new TCHAR[12];
    DWORD nVolumeNameSize = 12;
    DWORD VolumeSerialNumber;
    DWORD MaximumComponentLength;
    LPTSTR lpFileSystemNameBuffer = new TCHAR[10];
    DWORD nFileSystemNameSize = 10;
    DWORD FileSystemFlags;
    GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),lpVolumeNameBuffer,nVolumeNameSize, &VolumeSerialNumber,
                         &MaximumComponentLength, &FileSystemFlags, lpFileSystemNameBuffer,nFileSystemNameSize);
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    QString mac;
    foreach (QNetworkInterface i, list) {
        mac = mac + i.hardwareAddress() + i.name();
    }
    mac = QString("%1").arg(VolumeSerialNumber);
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
    m_CheckItems.clear();

    m_CurrentLotNo = "";
    m_CurrentBlockNo = "";
    m_Opt_ID = "";

    emit stringListChanged();
}

void DataFilter::clearBlockNo()
{
    m_StringList.clear();
    m_CheckItems.clear();
    m_CurrentBlockNo = "";
    emit stringListChanged();
}

bool DataFilter::DeleteItem(){

    if(m_CheckItems.empty()){
        QMessageBox::critical(NULL, "警告", "请选择删除项", QMessageBox::Ok);
        return true;
    }

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText("删除操作， 请谨慎！                 ");
    msgBox.setInformativeText("确认删除?");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret != 0){
        return false;
    }

    QStringList sl;
    for(int i = 0; i < m_CheckItems.size(); i++)
    {
        QString Block_No = m_CheckItems.at(i);

        if(m_DB.GetSnNumByBlockNo(Block_No) == 0){
            m_DB.ExecuteSQL("delete from BLOCK_NO where BLOCK_NO = :BLOCK_NO", Block_No);
            m_DB.ClearSnByBlockNo(Block_No);
            for(int j = 0; j < m_StringList.size(); j++){
                QStringList str = m_StringList.at(j).split("|");
                if (str[1] == Block_No){
                    m_StringList.removeAt(j);
                }
            }
            sl.append(Block_No);
        }else{
            QString msg = QString("由于分割BLOCK_NO:%1 存在SN， 禁止删除！").arg(Block_No);
            QMessageBox::critical(NULL, "删除提醒", msg, QMessageBox::Ok);
        }
    }

    /*
    for(int i = 0; i < sl.size(); i++)
    {
        for(int j = 0; j<m_CheckItems.size(); j++){
            if(sl.at(i) == m_CheckItems.at(j)){
                m_CheckItems.removeAt(j);
            }
        }
    }
    */
    if(sl.size() != 0)
        m_CheckItems.clear();

    emit stringListChanged();
    return true;
}

bool DataFilter::DeleteSN(){

    if(m_CheckItems.empty()){
        QMessageBox::critical(NULL, "警告", "请选择删除项", QMessageBox::Ok);
        return true;
    }

    for(int i = 0; i < m_CheckItems.size(); i++)
    {
        QString SN = m_CheckItems.at(i);
        QString BlockNo = m_DB.GetBlockNoBySn(SN);

        QStringList sl;
        m_DB.GetSnListByBlockNo(BlockNo, &sl);
        for(int j = 0 ; j < sl.size(); j++){
            if(!m_CheckItems.contains(sl.at(j))){
                QMessageBox::critical(NULL, "警告", "请选择完整分割删除， 或者在录入界面扫码RESCAN删除！", QMessageBox::Ok);
                return true;
            }
        }
    }

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText("删除操作， 请谨慎！                 ");
    msgBox.setInformativeText("确认删除?");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret != 0){
        return false;
    }

    for(int i = 0; i < m_CheckItems.size(); i++)
    {
        QString SN = m_CheckItems.at(i);

        m_DB.ExecuteSQL("delete from SN where SN = :SN", SN);

        for(int j = 0; j < m_StringList.size(); j++){
            QStringList str = m_StringList.at(j).split("|");
            if (str[2] == SN){
                m_StringList.removeAt(j);
            }
        }
    }

    m_CheckItems.clear();
    emit stringListChanged();
    return true;
}
bool DataFilter::DeleteFanXiu(){

    if(m_CheckItems.empty()){
        QMessageBox::critical(NULL, "警告", "请选择删除项", QMessageBox::Ok);
        return true;
    }

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText("删除操作， 请谨慎！                 ");
    msgBox.setInformativeText("确认删除?");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret != 0){
        return false;
    }

    for(int i = 0; i < m_CheckItems.size(); i++)
    {
        QString SN = m_CheckItems.at(i);

        m_DB.ExecuteSQL("delete from FANXIU_SN where SN = :SN", SN);

        for(int j = 0; j < m_StringList.size(); j++){
            QStringList str = m_StringList.at(j).split("|");
            if (str[2] == SN){
                m_StringList.removeAt(j);
                j--;
            }
        }
    }

    m_CheckItems.clear();
    emit stringListChanged();
    return true;
}


void DataFilter::searchData(QString flag, QString no, int sn_flag)
{
    if(no == "") return;

    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "警告", "数据库连接异常 请配置", QMessageBox::Ok);
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

    QString opt_id = "无";
    if(m_StringList.size() == 0){
        QMessageBox::information(NULL, "提示", "当前查询无结果", QMessageBox::Ok);
    }else{
        QString content = m_StringList[0];
        QStringList l = content.split("|");
        opt_id = l[6];
    }

    m_string = "操作员: " + opt_id;
    emit stringChanged();
    emit stringListChanged();
}

void DataFilter::searchDataByDate()
{
    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "警告", "数据库连接异常 请配置", QMessageBox::Ok);
        return;
    }
    clearData();
    m_DB.searchByDate(m_StartDate, m_EndDate, &m_StringList);

    if(m_StringList.size() == 0){
        QMessageBox::information(NULL, "提示", "当前查询无结果", QMessageBox::Ok);
    }

    emit stringListChanged();
}

void DataFilter::setMaxLuRu(int max_LuRu)
{
    m_CurrentMax_LuRu = max_LuRu;
}

bool DataFilter::setScan(QString flag, QString no, QString Location, int sn_flag, QString product)
{
    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "警告", "数据库连接异常 请配置", QMessageBox::Ok);
        return false;
    }

    no = no.trimmed();
    if(no == "") return false;

    m_string = "";
    emit stringChanged();

    if(product == "6ADKN" || product == "5FDKN"){
        return this->setScan_1(flag, no, Location, sn_flag, product);
    }

    if(flag == "opt_id"){
        m_Opt_ID = no;
    }

    m_Product = product;
    if(sn_flag == 0){
        if("lot_no" == flag){
            if(!m_DB.IsExistLotNo(no)){
                m_string = QString("SMF Lot No. 不存在");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }else{
                m_CurrentLotNo = no;
            }
            //m_DB.InsertLotNo(no);
        }else if("block_no" == flag){
            if(m_CurrentLotNo == "") {
                m_string = QString("请先录入 SMF Lot No.");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }
            if(!m_DB.IsExistBlockNo(no)){
                m_string = QString("Block No. 不存在");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }else{
                QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);
                if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
                    m_string = QString("Block No. %1 属于 %2")
                            .arg(no)
                            .arg(tmp_LotNO);
                    QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                    return false;
                }
                m_CurrentBlockNo = no;

                m_IntList.clear();
                m_DB.GetBadMarkSn(no, &m_IntList);
            }
        }else if("sn" == flag){
            if( m_CurrentLotNo == "" || m_CurrentBlockNo == "" ){
                m_string = QString("请录入 SMF Lot No. Block No.");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }else if(no == "rescan" || no == "RESCAN"){
                m_DB.ClearSnByBlockNo(m_CurrentBlockNo);
                m_StringList.clear();
                emit stringListChanged();
                return true;
            }else if(no == "NOSAMPLE"){
                no = "*";
                m_StringList.append(no + "|" + Location);
                emit stringListChanged();
                return true;
            }else if(no == "BADMARK"){
                no = "BADMARK";
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
                    //del_sn = del_sn.split("|")[0];
                    //m_DB.ClearSn(del_sn);
                }
                emit stringListChanged();
                return true;
            }


            if((m_DB.GetSnNumByBlockNo(m_CurrentBlockNo) + m_StringList.size()) >= m_CurrentMax_LuRu){
                m_string = "录入超过产品设定数量";
                emit stringChanged();
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }
            for(int i = 0; i < m_StringList.size(); i++){
                QString str = m_StringList.at(i);
                if (str.split("|")[0] == no){
                    m_string = "数据已存在";
                    emit stringChanged();
                    return false;
                }
            }

            if(m_DB.IsExistSn(no)) {
                m_string = "数据已存在";
                emit stringChanged();
                return false;
            }
            QString BadMarkStr = "BADMARK";
            for(int l = Location.toInt(); l <= m_CurrentMax_LuRu; l++){
                if(m_IntList.contains(l)){
                    m_StringList.append(BadMarkStr + "|" + QString("%1").arg(l));
                }else{
                    Location = QString("%1").arg(l);
                    break;
                }
            }

            if(m_StringList.size() < m_CurrentMax_LuRu){
                m_StringList.append(no + "|" + Location);
            }

            if(m_StringList.size() < m_CurrentMax_LuRu){

                for(int l = Location.toInt() + 1; l <= m_CurrentMax_LuRu; l++){
                    if(m_IntList.contains(l)){
                        m_StringList.append(BadMarkStr + "|" + QString("%1").arg(l));
                    }else{
                        break;
                    }
                }
            }

            emit stringListChanged();
        }
    }else if(sn_flag == 1){
        if("lot_no" == flag){
            m_CurrentLotNo = no;
        }
        else if("block_no" == flag){
            if(m_CurrentLotNo == "") {
                m_string = QString("请先录入 SMF Lot No.");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
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



bool DataFilter::setScan_1(QString flag, QString no, QString Location, int sn_flag, QString product)
{
    QMap<QString, QString> m_6ADKN;
    QMap<QString, QString> m_5FDKN;

    m_6ADKN.insert("B", "FYQM");
    m_6ADKN.insert("W", "G5P8");
    m_6ADKN.insert("G", "G5P9");

    m_5FDKN.insert("B", "FQ4R");
    m_5FDKN.insert("W", "G5C4");
    m_5FDKN.insert("G", "G5C3");

    //BLOCK 5   -----    SN 12:15
    m_Product = product;

    if("lot_no" == flag){
        m_CurrentLotNo = no;
    }else if("block_no" == flag){
        if(m_CurrentLotNo == "") {
            m_string = QString("请先录入 SMF Lot No.");
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }
        QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);
        if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
            m_string = QString("Block No. %1 属于 %2")
                    .arg(no)
                    .arg(tmp_LotNO);
            //QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            //return false;
            emit stringChanged();
            m_CurrentLotNo = tmp_LotNO;
        }
        m_CurrentBlockNo = no;
    }else if("sn" == flag){
        if( m_CurrentLotNo == "" || m_CurrentBlockNo == "" ){
            m_string = QString("请录入 SMF Lot No. Block No.");
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }else if(no == "rescan" || no == "RESCAN"){
            m_DB.ClearSnByBlockNo(m_CurrentBlockNo);
            m_StringList.clear();
            emit stringListChanged();
            return true;
        }else if(no == "NOSAMPLE"){
            no = "*";
            m_StringList.append(no + "|" + Location);
            emit stringListChanged();
            return true;
        }else if(no == "BADMARK"){
            no = "BADMARK";
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
            }
            emit stringListChanged();
            return true;
        }


        if((m_DB.GetSnNumByBlockNo(m_CurrentBlockNo) + m_StringList.size()) >= m_CurrentMax_LuRu){
            m_string = "录入超过产品设定数量";
            emit stringChanged();
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }
        for(int i = 0; i < m_StringList.size(); i++){
            QString str = m_StringList.at(i);
            if (str.split("|")[0] == no){
                m_string = "数据已存在";
                emit stringChanged();
                return false;
            }
        }

        if(m_DB.IsExistSn(no)) {
            m_string = "数据已存在";
            emit stringChanged();
            return false;
        }

        QString color_sn, eeee;
        if(m_Product == "6ADKN"){
            color_sn = m_CurrentBlockNo.left(5).right(1);
            eeee = m_6ADKN.value(color_sn);
        }else{
            color_sn = m_CurrentBlockNo.left(5).right(1);
            eeee = m_5FDKN.value(color_sn);
        }

        QString no_eeee = no.left(15).right(4);
        if(no_eeee != eeee){
            m_string = QString("Block No COLOR位 %1 与 SN EEEE: %2 不匹配").arg(color_sn).arg(no_eeee);
            emit stringChanged();
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }



        if(m_StringList.size() < m_CurrentMax_LuRu){
            m_StringList.append(no + "|" + Location);
        }

        emit stringListChanged();
    }
    return true;
}

void DataFilter::SNLuRuDone()
{
    QDateTime dt = QDateTime::currentDateTime();
    m_LogFile2 = m_CurrentBlockNo + "_" + dt.toString("yyyyMMddhhmmss") + ".txt";

    m_DB.InsertLotNo(m_CurrentLotNo);

    QString tmp_LotNO = m_DB.GetLotNoByBlockNo(m_CurrentBlockNo);
    if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
        m_string = QString("Block No. %1 属于 %2")
                .arg(m_CurrentBlockNo)
                .arg(tmp_LotNO);
        QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
        return;
    }
    m_DB.InsertBlockNo(m_CurrentBlockNo, m_CurrentLotNo);

    QString msg = "";
    for(int i = 0; i < m_StringList.size(); i++){
        QString str = m_StringList.at(i);
        QStringList l = str.split("|");
        if(l[0] == "*"){
            continue;
        }
        if(l[0] == "BADMARK"){
            msg = msg + m_CurrentLotNo + "," + m_CurrentBlockNo + "," + l[1] + "," + "BADMARK" + "," + dt.toString("yyyy-MM-dd hh:mm:ss") + "\r\n";
            continue;
        }
        m_DB.InsertSn(l[0], m_CurrentBlockNo, l[1], 0, m_Product, m_Opt_ID);

        msg = msg + m_CurrentLotNo + "," + m_CurrentBlockNo + "," + l[1] + "," + l[0] + "," + dt.toString("yyyy-MM-dd hh:mm:ss") + "\r\n";
    }


    QDir d(getDirPath() + "\\" + LOG_DIR + "\\" + LOG_DIR_2);
    QString fileName = m_LogFile2;
    QFile f(d.filePath(fileName));

    if(f.exists()){
        f.open(QIODevice::Append);
    }else {
        f.open(QIODevice::ReadWrite);
        msg = "LotID,PanelID,SequenceID,BlockSN,CreateDateTime\r\n" + msg;
    }

    QTextStream in(&f);
    in << msg;
    f.close();
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
        QMessageBox::critical(NULL, "警告", "数据库连接异常 请配置", QMessageBox::Ok);
        return false;
    }

    no = no.trimmed();
    if(no == "") return false;

    m_string = "";
    emit stringChanged();

    if("lot_no" == flag){
        QString MssConfig = m_DB.getMssConfig(no);
        if(MssConfig != ""){
            QString status = MssConfig.split("|")[3];
            if(status == "1" || status == "5"){}
            else if(status == "0"){
                m_string = QString("MSS 系统工单匹配错误 [0---新建工单未释放]");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }else if(status == "6"){
                m_string = QString("MSS 系统工单匹配错误 [6---已终止]");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }else if(status == "8"){
                m_string = QString("MSS 系统工单匹配错误 [8---已完成]");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }else if(status == "9"){
                m_string = QString("MSS 系统工单匹配错误 [9---已计划]");
                QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
                return false;
            }
        }else{
            m_string = QString("MSS 系统工单匹配错误 [未查询到状态]");
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }
    }

    if("lot_no" == flag){
        m_CurrentLotNo = no;
        //m_DB.InsertLotNo(no);
        m_StringList.clear();
    }
    else if("block_no" == flag){
        if(m_CurrentLotNo == "") {
            m_string = QString("请先录入 SMF Lot No.");
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }

//        int count = m_DB.GetBlockNoNumByLotNo(m_CurrentLotNo);
//        int limit = m_DB.GetBlockNoLimitSettings();
//        if (count >= limit){
//            m_string = QString("BLOCK_NO 数量超限, 请在设置菜单调整.");
//            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
//            return false;
//        }

        QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);
        if(tmp_LotNO != "" && tmp_LotNO != m_CurrentLotNo){
            m_string = QString("Block No. %1 属于 %2")
                    .arg(no)
                    .arg(tmp_LotNO);
            QMessageBox::critical(NULL, "警告", m_string, QMessageBox::Ok);
            return false;
        }

        m_CurrentBlockNo = no;
        m_DB.InsertLotNo(m_CurrentLotNo);
        if(! m_DB.InsertBlockNo(no, m_CurrentLotNo)){
            m_string = "数据已存在";
            emit stringChanged();
            return false;
        }

        saveLog1(m_CurrentLotNo, no);
        QDateTime dt = QDateTime::currentDateTime();
        m_StringList.append(m_CurrentLotNo + "|" + no + "|" + dt.toString("yyyy-MM-dd hh:mm:ss"));
    }
    emit stringListChanged();
    return true;
}

void DataFilter::searchLotNoBlockNo(QString flag, QString no)
{
    if(no == "") return;

    if(! m_DB.isOpen()){
        QMessageBox::critical(NULL, "警告", "数据库连接异常 请配置", QMessageBox::Ok);
        return;
    }

    clearData();
    if("lot_no" == flag){
        m_DB.SearchBlockNoByLotNO(no, &m_StringList);
    }else if("block_no" == flag){
        m_DB.SearchBlockNoByBlockNo(no, &m_StringList);
    }

    if(m_StringList.size() == 0){
        QMessageBox::information(NULL, "提示", "当前查询无结果", QMessageBox::Ok);
    }

    emit stringListChanged();
}

bool DataFilter::isLast_BlockNo()
{
    return m_DB.isLast_BlockNo(m_CurrentLotNo);
}

void DataFilter::CheckItem(QString item)
{
    if(m_CheckItems.contains(item)){
        m_CheckItems.removeOne(item);
    }else{
        m_CheckItems.append(item);
    }
}

void DataFilter::OnAbout()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText(WindowTitle + " " + Version + "                            ");
    msgBox.setInformativeText("Copyright 深圳市菲尼曼特科技有限公司 2015");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.exec();
    /*
    About *ab = new About();
    ab->setSource(QUrl("qml/LotNo/about.qml"));
    ab->show();
    */
}

void DataFilter::calendarFormat()
{
    m_Calendar->hide();
    if(m_DateType == "start"){
        m_StartDate = m_Calendar->selectedDate().toString("yyyy-MM-dd");
    }else if(m_DateType == "end"){
        m_EndDate = m_Calendar->selectedDate().toString("yyyy-MM-dd");
    }

    emit stringChanged();
}

void DataFilter::calendarShow(QString type, int x, int y)
{
    m_DateType = type;
    m_Calendar->move(x, y);
    m_Calendar->show();
}
QString DataFilter::getDate(QString type)
{
    if(m_StartDate == ""){m_StartDate = m_Calendar->selectedDate().toString("yyyy-MM-dd");}
    if(m_EndDate == "") {m_EndDate = m_Calendar->selectedDate().toString("yyyy-MM-dd");}
    if(type == "start")
        return "开始时间: " + m_StartDate;
    return "结束时间: " + m_EndDate;
}
/*
 *return true 切换产品录入
 *return false 停留当前位置
 */
bool DataFilter::ChangeProductItem(QString item)
{
    QStringList sl;
    sl.append("record_6ADKN");
    sl.append("record_5FDKN");
    sl.append("record_32FGRX_12");
    sl.append("record_32FGRX_16");
    sl.append("record_8AGRX");
    sl.append("record_6FDKN");
    sl.append("record_7ADKN");
    sl.append("record");
    sl.append("record_fanxiu");
    sl.append("record_6FDKN_P2");
    sl.append("record_7ADKN_EVT");

    if(!sl.contains(m_CurrentProduct)){
        m_CurrentProduct = item;
        return true;
    }
    if(m_CurrentProduct == item)
        return false;

    if(m_CurrentLotNo == "" && m_CurrentBlockNo == "" && m_StringList.size() == 0){
        m_CurrentProduct = item;
        return true;
    }

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(WindowTitle);
    msgBox.setText("终止录入提示                 ");
    msgBox.setInformativeText("确定终止当前录入操作， 放弃完整分割录入?");
    msgBox.addButton("确定", QMessageBox::YesRole);
    msgBox.addButton("取消", QMessageBox::NoRole);
    int ret = msgBox.exec();
    if(ret == 0){
        m_CurrentProduct = item;
        return true;
    }
    return false;
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
