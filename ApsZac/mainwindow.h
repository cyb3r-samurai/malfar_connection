#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DeviceController.h"
#include "simpletabledata.h"
#include "Message.h"
#include "packet.h"
#include "messageprocessor.h"
#include "c_window.h"
#include "timeplotter.h"
#include "celmodel.h"
#include "dftplotter.h"
#include "dsp.h"

#include <QAbstractSocket>
#include <QMainWindow>
#include <QMetaEnum>
#include <QTcpSocket>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void device_connected();
    void device_disconnected();
    void device_state_changed(QAbstractSocket::SocketState state);
    void device_error_occured(QAbstractSocket::SocketError error);

    void kaReceived(int kaNumber);

    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void on_pushButton_clicked();

    void onKaSelected(const QModelIndex);
    void onDataUpdated(int kaNumber);

signals:
    void on_request(Request_Type);

private:
    Ui::MainWindow* ui;
    DeviceController* controller_;
    MessageProcessor* m_processor_;
    SimpleTableData* model_;
    MessageStorage message_storage_;
    QList<SubSessionInfo> * test_data_;
    C_window *c_window;
    TimePlotter *time_plotter;
    DftPlotter *dft_plotter;
    CelModel *m_celmodel;
    QStandardItemModel *m_kamodel;
    Dsp m_dsp;
    QThread *client_thread;


    int selectedKa;

    void setDeviceController();
    void replotGraphs();
};
#endif // MAINWINDOW_H
