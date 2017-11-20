#include "gatewaymgr.h"
#include "NeZipDrv.h"
#include "servicemgr.h"
#include <QCoreApplication>
#include <QDir>

GatewayMgr::GatewayMgr(QObject* parent)
    : QObject(parent)
{
}

void GatewayMgr::init()
{
    g_sm->checkCurrentOn(ServiceMgr::BLOGIC);

    // qRegisterMetaType
    qRegisterMetaType<AskDataTag>("AskDataTag");

    nezip_ = new NeZipDrv();
}

void GatewayMgr::shutdown()
{
    g_sm->checkCurrentOn(ServiceMgr::BLOGIC);

    delete nezip_;
    nezip_ = nullptr;
}

void GatewayMgr::loadDrv()
{
    BfLog(__FUNCTION__);
    g_sm->checkCurrentOn(ServiceMgr::BLOGIC);

    QString drvPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("Nezip/System/Stockdrv.dll"));
    bool ok = nezip_->load(qPrintable(drvPath));
    if (ok) {
        BfLog("load nezipdrv ok: (%s)", qPrintable(drvPath));
    } else {
        BfLog("load nezipdrv fail: (%s)", qPrintable(drvPath));
    }
}

void GatewayMgr::askData(const AskDataTag& tag)
{
    //BfLog(__FUNCTION__);
    g_sm->checkCurrentOn(ServiceMgr::BLOGIC);

    if (!nezip_->inited()) {
        BfLog("please loaddrv first");
        return;
    }

    BfLog("askdata:(%s)-->(%s.%s)", qPrintable(tag.nezipCode), qPrintable(tag.ctpSymbol), qPrintable(tag.ctpExchange));
    QMutexLocker locker(&mu_);
    if (tags_.contains(tag.nezipCode)) {
        BfLog("ask already:(%s)", qPrintable(tag.nezipCode));
        return;
    }
    tags_.insert(tag.nezipCode, tag);

    //askServer设置为true则向远程服器同步数据，完成后主动推送数据=
    KLINETYPE klineType = TRACE_KLINE;
    nezip_->askdata(qPrintable(tag.nezipCode), klineType, true, true, 1, true);

    //askServer设置为true则向远程服器同步数据，完成后主动推送数据=
    klineType = MIN1_KLINE;
    nezip_->askdata(qPrintable(tag.nezipCode), klineType, true, true, 1, true);

    //askServer设置为true则向远程服器同步数据，完成后主动推送数据=
    klineType = MIN5_KLINE;
    nezip_->askdata(qPrintable(tag.nezipCode), klineType, true, true, 1, true);

    //askServer设置为true则向远程服器同步数据，完成后主动推送数据=
    klineType = DAY_KLINE;
    nezip_->askdata(qPrintable(tag.nezipCode), klineType, true, true, 1, true);
}

QMap<QString, AskDataTag> GatewayMgr::tags()
{
    QMutexLocker locker(&mu_);
    return tags_;
}
