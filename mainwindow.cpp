#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    /* Populate colors */
    line_colors{
        /* For channel data (gruvbox palette) */
        /* Light */
        "#E6B0AA",
        "#D2B4DE",
        "#AED6F1",
        "#76D7C4",
        "#F7DC6F",
        "#F0B27A",
        "#D7DBDD",
        /* Light */
        "#cc241d",
        "#98971a",
        "#d79921",
        "#458588",
        "#b16286",
        "#689d6a",
        "#d65d0e",
     }
{
    ui->setupUi(this);
    SerialConnector = new SerialPortConnector(this);

    connect(this, SIGNAL(portConfigureRequest()), SerialConnector, SLOT(showDialog()));
    connect(SerialConnector, SIGNAL(portOpenOK()), this, SLOT(onPortOpenSuccess()));
    connect(SerialConnector, SIGNAL(printData(QByteArray*)) , this, SLOT(newDataArrived(QByteArray*)));
    connect(SerialConnector, SIGNAL(portClosed()), this, SLOT(onPortClose()));

}

void MainWindow::initWindow()
{
    this->totalLineCount = 0;
    this->filteredLineCount = 0;
    this->showTimestamp = false;
    this->updateLineCount();
}

int MainWindow::getLineCount()
{

    return receivedStrings.size();
}

int MainWindow::getFilteredLineCount()
{
    return this->filteredLineCount;
    //return ui->textEdit_Main->document()->blockCount();
}

QString MainWindow::getFilteredLineCountStr()
{
    return (QString("%1").arg(getFilteredLineCount()));
}

QString MainWindow::getLineCountStr()
{
    return (QString("%1").arg(getLineCount()));
}

void MainWindow::updateLineCount()
{
    ui->label_lineCount->setText(this->getFilteredLineCountStr() + "/" + this->getLineCountStr());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int id;

    for (int i=0; i<filterArray.size(); i++)
    {
        if(filterArray[i].filterStr.contains(ui->lineEdit_2->text()))
        {
            return;
        }
    }
    id = filterArray.size();

    filterArray.append(filter_t(ui->lineEdit_2->text(), id, line_colors[id]));
    ui->comboBox_FilterSelection->addItem(ui->lineEdit_2->text());

    filteredLineCount = filteredStrings.size();
    ui->lineEdit_2->clear();
    ui->comboBox_FilterSelection->setCurrentIndex(ui->comboBox_FilterSelection->count() - 1);
}


void MainWindow::on_actionConfigure_triggered()
{
    emit portConfigureRequest();
}

void MainWindow::onPortOpenSuccess()
{
    ui->actionConnect->setEnabled(false);
    ui->actionDisconnect->setEnabled(true);
}

void MainWindow::onPortClose()
{
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
}

void MainWindow::newDataArrived(QByteArray *data)
{
    bool filteredLine = false;
    receivedStrings.append(QString(*data).trimmed());

    QStringList lines = QString(*data).trimmed().split("\n");
    for (int i=0;i<lines.size();i++)
    {
        tsList.append(QTime().currentTime());
        filteredLine = false;
        if(filterArray.size() > 0)
        {
            //for (int j=0;j<filterList.size();j++)
            for (int j=0;j<filterArray.size();j++)
            {
                if(lines[i].contains(filterArray[j].filterStr))
                {
                    //QString displayedStr = QString("<span style=\"color:#000000; background-color:%1;\">%2</span>").arg(line_colors[j], lines[i].trimmed());
                    ui->textEdit_Main->setTextColor("#000000");
                    ui->textEdit_Main->setTextBackgroundColor(filterArray[j].bgColor);
                    if(this->showTimestamp)
                    {
                        ui->textEdit_Main->append(tsList.last().toString(Qt::ISODateWithMs) + " - " + lines[i].trimmed());
                    }
                    else
                    {
                        ui->textEdit_Main->append(lines[i].trimmed());
                    }
                    ui->textEdit_Main->setTextBackgroundColor("#232629"); // Discusting hack
                    ui->textEdit_Main->setTextColor("#FFFFFF");
                    //ui->textEdit_Main->insertHtml(displayedStr);

                    ui->textEdit_filtered->setTextColor("#000000");
                    ui->textEdit_filtered->setTextBackgroundColor(line_colors[j]);
                    ui->textEdit_filtered->append(lines[i].trimmed());
                    ui->textEdit_filtered->setTextBackgroundColor("#232629"); // Discusting hack
                    ui->textEdit_filtered->setTextColor("#FFFFFF");

                    filteredLine = true;
                    break;
                }
            }
            if(!filteredLine)
            {
                ui->textEdit_Main->setTextBackgroundColor("#232629"); // Discusting hack to put back the old color, its based on the css original back color
                ui->textEdit_Main->setTextColor("#FFFFFF");
                if(this->showTimestamp)
                {
                    ui->textEdit_Main->append(tsList.last().toString(Qt::ISODateWithMs) + " - " + lines[i].trimmed());
                }
                else
                {
                    ui->textEdit_Main->append(lines[i].trimmed());
                }
            }
        }
        else {
            if(this->showTimestamp)
            {
                ui->textEdit_Main->append(tsList.last().toString(Qt::ISODateWithMs) + " - " + lines[i].trimmed());
            }
            else
            {
                ui->textEdit_Main->append(lines[i].trimmed());
            }
        }
    }

}

void MainWindow::on_actionDisconnect_triggered()
{
    SerialConnector->closePort();
}

void MainWindow::on_actionConnect_triggered()
{
    SerialConnector->openPort();
}

void MainWindow::on_textEdit_Main_textChanged()
{
    this->updateLineCount();
}

void MainWindow::on_pushButton_RemoveFilter_clicked()
{
   // filterList.removeAt(ui->comboBox_FilterSelection->currentIndex());
    filterArray.removeAt(ui->comboBox_FilterSelection->currentIndex());
    ui->comboBox_FilterSelection->removeItem(ui->comboBox_FilterSelection->currentIndex());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{

}

void MainWindow::on_checkBox_timestamp_stateChanged(int arg1)
{
    this->showTimestamp = (bool)arg1;
}
