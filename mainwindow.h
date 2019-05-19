#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDatetime>
#include "serialportconnector.h"

#define CUSTOM_LINE_COLORS  14

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow();

    int getLineCount();
    int getFilteredLineCount();
    QString getLineCountStr();
    QString getFilteredLineCountStr();
Ui::MainWindow *ui;
signals:

    void portConfigureRequest(void);


private slots:
    void on_pushButton_clicked();
    void on_actionConfigure_triggered();
    void newDataArrived(QByteArray *data);
    void onPortOpenSuccess(void);
    void onPortClose(void);
    void on_actionDisconnect_triggered();

    void on_actionConnect_triggered();

    void on_textEdit_Main_textChanged();

    void on_pushButton_RemoveFilter_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_checkBox_timestamp_stateChanged(int arg1);

private:

    /* Line colors */
    QString line_colors[CUSTOM_LINE_COLORS];

    bool showTimestamp;
    int totalLineCount;
    int filteredLineCount;
    int scrollBackLen();

    // Stored data
    QStringList receivedStrings;
    QList <QTime> tsList;
    QStringList filteredStrings;
    QStringList filterList;
    struct filter_t
    {
        QString filterStr;
        int id;
        QColor bgColor;
        filter_t(QString filterStr, int id, QColor bgColor)
            :filterStr(filterStr), id(id), bgColor(bgColor)
        {

        }
    };
    QList <filter_t> filterArray;
    SerialPortConnector *SerialConnector;

    void updateLineCount();

};

#endif // MAINWINDOW_H
