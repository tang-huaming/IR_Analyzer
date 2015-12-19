#include "mainwindow.h"
#include "basicsettingsdlg.h"
#include <QCloseEvent>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>

#ifdef IR_FUNC_TEST
#include <QDebug>
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

#ifdef IR_FUNC_TEST
    // 获取主机名
    QString localHostName = QHostInfo::localHostName();
    qDebug() << "主机名: " << localHostName;

    // 获取本主机上的IP地址列表
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> addrList = hostInfo.addresses();
    qDebug() << "本主机上的IP地址列表，总计： " << addrList.count();
    foreach (QHostAddress var, addrList) {
        qDebug() << var.toString();
    }

    // 获取本机的网络接口列表
    QList<QNetworkInterface> ifaceList = QNetworkInterface::allInterfaces();
    for (int i = 0; i < ifaceList.count(); i++){
        QNetworkInterface var = ifaceList.at(i);
        qDebug() << tr("########## 设备%1 ############").arg(i);
        qDebug() << tr("接口名称：") << var.humanReadableName();
        qDebug() << tr("设备名称：") << var.name();
        qDebug() << tr("硬件地址：") << var.hardwareAddress();

        // 读取一个IP地址的关联信息列表
        QList<QNetworkAddressEntry> entryList = var.addressEntries();
        foreach(QNetworkAddressEntry entry, entryList){
            qDebug() << "IP: " << entry.ip().toString();
            qDebug() << "子网掩码：" << entry.netmask().toString();
            qDebug() << "广播地址：" << entry.broadcast().toString();
        }
    }

#endif

    // [01] Read System Settings
    readSettings();

    // [02] Create Main Window Components
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    // [03] Connect Signal and Slot
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
//    event->ignore();
}

void MainWindow::readSettings()
{}

void MainWindow::writeSettings()
{}

void MainWindow::createActions()
{
    exitAct = new QAction(QIcon(":/icons/exit.png"), tr("退出程序"), this);
    exitAct->setShortcut(QKeySequence::Close);
    exitAct->setStatusTip(tr("Exit This Application."));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exitApp()));

    basicSettingAct = new QAction(QIcon(":/icons/basicsetting.png"), tr("基本设置"), this);
//    basicSettingAct->setShortcut(QKeySequence::Close);
    basicSettingAct->setStatusTip(tr("the Basic Setting"));
    connect(basicSettingAct, SIGNAL(triggered()), this, SLOT(showBasicSetting()));

    helpAct = new QAction(QIcon(":/icons/about.png"), tr("关于"), this);
//    helpAct->setShortcut(QKeySequence::Close);
    helpAct->setStatusTip(tr("About This Application."));
    connect(helpAct, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void MainWindow::createMenus()
{
    mainMenu = menuBar()->addMenu(tr("主菜单"));
//    mainMenu->addSeparator();
    mainMenu->addAction(exitAct);

    settingMenu = menuBar()->addMenu(tr("设置"));
    settingMenu->addAction(basicSettingAct);

    helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(helpAct);
}

void MainWindow::createToolBars()
{
    commToolBar = addToolBar(tr("common"));
    commToolBar->setIconSize(QSize(32,32));
    commToolBar->addAction(exitAct);
    commToolBar->addAction(basicSettingAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::exitApp()
{
    this->close();
}

void MainWindow::showBasicSetting()
{
    BasicSettingsDlg bDlg;
    bDlg.setWindowFlags(Qt::WindowStaysOnTopHint);
    bDlg.setModal(true);//设置模态对话框
    bDlg.resize(QSize(640,480));
    bDlg.exec();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("IR Analyzer"),
                tr("The <b>Application</b> example demonstrates how to "
                   "write modern GUI applications using Qt, with a menu bar, "
                   "toolbars, and a status bar."));
}
