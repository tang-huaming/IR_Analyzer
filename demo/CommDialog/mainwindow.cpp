#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("通信方式设置对话框"));

    // 初始化界面状态
    initialize();

    connect(ui->boxSPort, SIGNAL(currentIndexChanged(int)),\
                this, SLOT(updatePortInfo(int)));
    connect(ui->boxNetDevice, SIGNAL(currentIndexChanged(int)),\
            this, SLOT(updateNetworkInfo(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    // 通信方式选择
    ui->radioTCPServer->setChecked(true);
    // 读取串口设备信息
    ui->boxBaudRate->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->boxBaudRate->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->boxBaudRate->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->boxBaudRate->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->boxBaudRate->setCurrentIndex(3);

    ui->boxDataBits->addItem(QLatin1String("5"), QSerialPort::Data5);
    ui->boxDataBits->addItem(QLatin1String("6"), QSerialPort::Data6);
    ui->boxDataBits->addItem(QLatin1String("7"), QSerialPort::Data7);
    ui->boxDataBits->addItem(QLatin1String("8"), QSerialPort::Data8);
    ui->boxDataBits->setCurrentIndex(3);

    ui->boxStopBits->addItem(QLatin1String("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->boxStopBits->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->boxStopBits->addItem(QLatin1String("2"), QSerialPort::TwoStop);
    ui->boxStopBits->setCurrentIndex(0);

    ui->boxParity->addItem(QLatin1String("None"), QSerialPort::NoParity);
    ui->boxParity->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
    ui->boxParity->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
    ui->boxParity->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
    ui->boxParity->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);
    ui->boxParity->setCurrentIndex(0);

    ui->boxSPort->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QStringList sp;
        sp << info.portName()\
           << info.description()\
           << info.manufacturer()\
           << info.systemLocation()\
           << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString())
           << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : QString());

        ui->boxSPort->addItem(sp.first(), sp);
    }

    // 读取网络接口信息
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    foreach(const QNetworkInterface &interface, list)
    {
        QString detail ;
        detail += tr("HardwareAddress:") + interface.hardwareAddress() + "\n";
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        foreach(const QNetworkAddressEntry entry, entryList)
        {
            detail += tr("IP Address:") + entry.ip().toString() + "\n";
            detail += tr("Netmask:") + entry.netmask().toString() + "\n";
            detail += tr("Broadcast:") + entry.broadcast().toString() + "\n";
        }

        ui->boxNetDevice->addItem(interface.humanReadableName(), detail );
    }

    // 设置默认网络端口号
    ui->editPortNum->setText(tr("8899"));
    ui->editDestAddress->setText(tr("127.0.0.1"));
    if (ui->radioTCPClient->isChecked()){
        ui->editDestAddress->setEnabled(true);
    }else{
        ui->editDestAddress->setEnabled(false);
    }
}

void MainWindow::updatePortInfo(int index)
{
    if (index != -1)
    {
        QStringList list = ui->boxSPort->itemData(index).toStringList();
        QString portInfo;
        portInfo += tr("Description: %1").arg(list.at(1)) + "\n";
        portInfo += tr("Manufacturer: %1").arg(list.at(2)) + "\n";
        portInfo += tr("Location: %1").arg(list.at(3)) + "\n";
        portInfo += tr("Vendor Identifier: %1").arg(list.at(4)) + "\n";
        portInfo += tr("Product Identifier: %1").arg(list.at(5));
        ui->textBrowser->setText(portInfo);
    }
}

void MainWindow::updateNetworkInfo(int index)
{
    if (index != -1)
    {
        ui->textBrowser->setText(ui->boxNetDevice->itemData(index).toString());
    }
}
