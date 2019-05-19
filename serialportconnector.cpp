#include "serialportconnector.h"
#include "ui_portconfig.h"
#include <QtSerialPort/qserialportinfo.h>
#include <QObject>
#include <QDialog>

SerialPortConnector::SerialPortConnector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    populateDialog();
    retranslateSettingDialog();
}

SerialPortConnector::~SerialPortConnector()
{
}

void SerialPortConnector::populateDialog()
{
    /* Populate baud rate combo box with standard rates */
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    /* And some not-so-standard */
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");
    ui->comboBox_baudrate->addItem ("");

    /* Select 115200 bits by default */
    ui->comboBox_baudrate->setCurrentIndex (7);

    /* Populate data bits combo box */
    ui->comboBox_databit->addItem ("");
    ui->comboBox_databit->addItem ("");
    /* Default is 8 bits */
    ui->comboBox_databit->setCurrentIndex(1);

    /* Populate parity combo box */
    ui->comboBox_parity->addItem ("");
    ui->comboBox_parity->addItem ("");
    ui->comboBox_parity->addItem ("");

    /* Populate stop bits combo box */
    ui->comboBox_stopbit->addItem ("");
    ui->comboBox_stopbit->addItem ("");
    ui->comboBox_stopbit->addItem ("");

    /* Populate flow control combo box */
    ui->comboBox_flow->addItem("");
    ui->comboBox_flow->addItem("");
    ui->comboBox_flow->addItem("");
    ui->comboBox_flow->addItem("");
}

void SerialPortConnector::closePort()
{
    serialPort->close();
    disconnect (serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    emit portClosed();
}

void SerialPortConnector::openPort()
{
    openPort(portList.at(portIndex), baudRate, databit, parity, stopbit);
}

void SerialPortConnector::showDialog()
{
    portList.clear();
    ui->comboBox_port->clear();
    QSerialPortInfo portInfo;

    /* List all available serial ports and populate ports combo box */
    for (QSerialPortInfo port : portInfo.availablePorts())
    {
        ui->comboBox_port->addItem (port.portName());
        portList.append(port);
    }
    retranslateSettingDialog();
    this->show();
}

void SerialPortConnector::retranslateSettingDialog()
{
    ui->comboBox_baudrate->setItemText(0,"1200");
    ui->comboBox_baudrate->setItemText(1,"2400");
    ui->comboBox_baudrate->setItemText(2,"4800");
    ui->comboBox_baudrate->setItemText(3,"9600");
    ui->comboBox_baudrate->setItemText(4,"19200");
    ui->comboBox_baudrate->setItemText(5,"38400");
    ui->comboBox_baudrate->setItemText(6,"57600");
    ui->comboBox_baudrate->setItemText(7,"115200");
    ui->comboBox_baudrate->setItemText(8,"128000");
    ui->comboBox_baudrate->setItemText(9,"153600");
    ui->comboBox_baudrate->setItemText(10,"230400");
    ui->comboBox_baudrate->setItemText(11,"256000");
    ui->comboBox_baudrate->setItemText(12,"460800");
    ui->comboBox_baudrate->setItemText(13,"921600");

    ui->comboBox_databit->setItemText(0,"7 bits");
    ui->comboBox_databit->setItemText(1,"8 bits");

    ui->comboBox_parity->setItemText(0, "none");
    ui->comboBox_parity->setItemText(1, "odd");
    ui->comboBox_parity->setItemText(2, "even");

    ui->comboBox_stopbit->setItemText(0, "1 bit");
    ui->comboBox_stopbit->setItemText(1, "1.5 bits");
    ui->comboBox_stopbit->setItemText(2, "2 bits");

    ui->comboBox_flow->setItemText(0,"none");
    ui->comboBox_flow->setItemText(1,"RTS/CTS");
    ui->comboBox_flow->setItemText(2,"DSR/DTR");
    ui->comboBox_flow->setItemText(3,"XON/XOFF");
}

void SerialPortConnector::openPort(QSerialPortInfo portInfo, int baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    serialPort = new QSerialPort(portInfo, nullptr);                                        // Create a new serial port
    currentPortName = portInfo.portName();

    if (serialPort->open (QIODevice::ReadWrite))
    {
        serialPort->setBaudRate(baudRate);
        serialPort->setParity(parity);
        serialPort->setDataBits(dataBits);
        serialPort->setStopBits(stopBits);
        connect (serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
        emit portOpenOK();
    }
    else
    {
        emit portOpenFail();
        //qDebug() << serialPort->errorString();
    }
}

void SerialPortConnector::on_buttonBox_accepted()
{
    baudRate = (ui->comboBox_baudrate->currentText().toInt());
    portIndex = ui->comboBox_port->currentIndex();

    switch(ui->comboBox_databit->currentIndex())
    {
        case 0: databit = QSerialPort::Data7; break;
        case 1: databit = QSerialPort::Data8; break;
    }

    switch(ui->comboBox_parity->currentIndex())
    {
        case 0: parity = QSerialPort::NoParity; break;
        case 1: parity = QSerialPort::OddParity; break;
        case 2: parity = QSerialPort::EvenParity; break;
    }

    switch(ui->comboBox_stopbit->currentIndex())
    {
        case 0: stopbit = QSerialPort::OneStop; break;
        case 1: stopbit = QSerialPort::OneAndHalfStop; break;
        case 2: stopbit = QSerialPort::TwoStop; break;
    }

    openPort();
    this->close();
}



void SerialPortConnector::readData()
{
    if(serialPort->bytesAvailable()) {                                                    // If any bytes are available
        QByteArray data = serialPort->readAll();                                          // Read all data in QByteArray
        emit printData(&data);
    }
}

