#ifndef SERIALPORTCONNECTOR_H
#define SERIALPORTCONNECTOR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include "ui_portconfig.h"

namespace Ui {
class ConnectDialog;
}

class SerialPortConnector : public QDialog
{
    Q_OBJECT

public:
    SerialPortConnector(QWidget *parent = nullptr);
    ~SerialPortConnector();

    void populateDialog();
    void closePort();
    void openPort();

signals:

    void portOpenFail();                                                                  // Emitted when cannot open port
    void portClosed();                                                                    // Emitted when port is closed
    void portOpenOK();                                                   // Emitted when port is open
    void printData(QByteArray *);
    void updateTargetStatus(bool status);

public slots:

    void showDialog();
    void readData();

private slots:
    void on_buttonBox_accepted();

private:

    void retranslateSettingDialog();
    Ui::ConnectDialog *ui;
    QMainWindow *parent;

    void openPort (QSerialPortInfo portInfo, int baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits);

    QSerialPort *serialPort = nullptr;                                                    // Serial port; runs in this thread

    QString currentPortName;

    // Serial port config
    int portIndex;
    int baudRate;
    QList<QSerialPortInfo> portList;
    QSerialPort::DataBits databit;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopbit;

};

#endif // SERIALPORTCONNECTOR_H
