#include "datafilter.h"
#include <QVariant>
#include "about.h"


DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{
    m_string = "hello";
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


void DataFilter::setScan(QString flag, QString no)
{
    if(no == "") return;

    m_string = "";
    emit stringChanged();

    if("lot_no" == flag){
        m_CurrentLotNo = no;
        if( !m_DB.InsertLotNo(no) )
        {
            m_string = "数据已存在";
            emit stringChanged();
        }
        if( !m_LotNoMap.contains(no) ){
            QSet<QString> block_no;
            m_LotNoMap.insert(no, block_no);
        }
        if( !m_LotNoList.contains(no) ) m_LotNoList.append(no);
        emit lotNoListChanged();
    }

    else if("block_no" == flag){
        QMap< QString, QSet< QString> >::Iterator it = m_LotNoMap.find(m_CurrentLotNo);
        if(it == m_LotNoMap.end()) {
            m_string = "没有对应的LotNo";
            emit stringChanged();
            return;
        }

        if( !m_DB.InsertBlockNo(no, m_CurrentLotNo) )
        {
            QString tmp_LotNO = m_DB.GetLotNoByBlockNo(no);

            if(tmp_LotNO != m_CurrentLotNo){
                m_string = QString("BlockNo %1 不属于 %2 属于 %3")
                        .arg(no)
                        .arg(m_CurrentLotNo)
                        .arg(tmp_LotNO);
                emit stringChanged();
                //QMessageBox::critical(NULL, "Waining", m_string, QMessageBox::Ok);
                return;
            }
        }

        m_CurrentBlockNo = no;
        QSet< QString >  *block_no = &(it.value());
        block_no->insert(no);

        QSet<QString> sn_no;
        m_BlockNoMap.insert(no, sn_no);

        if( !m_BlockNoList.contains(no) ) m_BlockNoList.append(no);
        emit blockNoListChanged();
    }
    else if("sn" == flag){
        QMap< QString, QSet< QString > >::Iterator it = m_BlockNoMap.find(m_CurrentBlockNo);

        if( it == m_BlockNoMap.end() ){
            m_string = "没有对应的BlockNo";
            emit stringChanged();
            return;
        }

        if( !m_DB.InsertSn(no, m_CurrentBlockNo) ){
            m_string = "数据已存在";
            emit stringChanged();
            return;
        }
        QSet< QString > *sn = &(it.value());
        sn->insert(no);
        if( !m_SnList.contains(no) ) m_SnList.append(no);
        emit snListChanged();
    }

    selectItem(flag, no);
    //QMessageBox::information(NULL, "Hello", QString.number(m_LotNoList.size()), QMessageBox::Yes);
}

void DataFilter::OnAbout()
{
    QMessageBox box;
    box.setIcon(QMessageBox::Information);
    box.setText("条码录入系统 V1.0 " + tr("\r\n\nCopyright 深圳市菲尼曼特科技有限公司 2013"));
    box.setStandardButtons(QMessageBox::Yes);
    box.exec();
    //::information(NULL, "关于", "CopyRight 深圳", QMessageBox::Yes);
    /*
    About *ab = new About();
    ab->setSource(QUrl("qml/LotNo/about.qml"));
    ab->show();
    */
}
