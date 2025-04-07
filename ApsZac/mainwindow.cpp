#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cB_msg_type->addItem("Состояние приема", QVariant(0));
    ui->cB_msg_type->addItem("Активные сеансы", QVariant(1));
    ui->cB_msg_type->addItem("Состояние Ас", QVariant(2));
    setDeviceController();

    model_ = new SimpleTableData();
    model_->populate();
    ui->tableView->setModel(model_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_celmodel = new CelModel;
    m_processor_ = new MessageProcessor(nullptr, &message_storage_, model_, m_celmodel);
    connect(this, &MainWindow::on_request, m_processor_, &MessageProcessor::set_request);
    connect(m_processor_, &MessageProcessor::message_ready, &controller_, &DeviceController::send);
    connect(&controller_, &DeviceController::data_ready, m_processor_, &MessageProcessor::device_data_ready);

    m_kamodel = new QStandardItemModel;
    ui->list_ka->setModel(m_kamodel);

    connect(m_celmodel, &CelModel::ka_added, this, &MainWindow::kaReceived);
    connect(m_celmodel, &CelModel::dataUpdated, this, &MainWindow::onDataUpdated);

    connect(ui->list_ka->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::onKaSelected);
    time_plotter = new TimePlotter(ui->pl_time, this);
    dft_plotter = new DftPlotter(ui->dft_plot, this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::device_connected()
{
    qDebug() <<("Connected to Device");
    ui->btnConnect->setText("Разорвать соединение");
    ui->grpSendData->setEnabled(true);
}

void MainWindow::device_disconnected()
{
    qDebug() << ("Disconnectec from Device");
    ui->btnConnect->setText("Установить соединеине");
    ui->grpSendData->setEnabled(false);
}

void MainWindow::device_state_changed(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug()<< metaEnum.valueToKey(state);
}

void MainWindow::device_error_occured(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    qDebug() << metaEnum.valueToKey(error);
}

void MainWindow::kaReceived(int kaNumber)
{
    QStandardItem *item = new QStandardItem(QString::number(kaNumber));
    m_kamodel->appendRow(item);
}

void MainWindow::setDeviceController()
{
    connect(&controller_, &DeviceController::connected, this, &MainWindow::device_connected);
    connect(&controller_, &DeviceController::disconnected, this, &MainWindow::device_disconnected);
    connect(&controller_, &DeviceController::state_changed, this, &MainWindow::device_state_changed);
    connect(&controller_, &DeviceController::error_occured, this, &MainWindow::device_error_occured);
 //   connect(&controller_, &DeviceController::data_ready, this, &MainWindow::device_data_ready);
}

void MainWindow::replotGraphs()
{
    if (selectedKa == -1) {
        return;
    }

    CelData cel = m_celmodel->getKaData(selectedKa);
    m_dsp.input(cel.iData, cel.qData);

    QVector<double> time_data;
    time_data.resize(cel.iData.count());

    for(qsizetype i = 0; i < cel.iData.count(); i++) {
        time_data[i] = i;
    }
    time_plotter->setIData(time_data, cel.iData);
    time_plotter->setQData(time_data, cel.qData);

    dft_plotter->setAmpDistData(m_dsp.freqVector(), m_dsp.ampDistDb());

}

void MainWindow::on_btnConnect_clicked()
{
    if(controller_.is_connected()) {
        controller_.disconnect();
    }
    else {
        auto ip = ui->lnIPAddress->text();
        auto port = ui->spinPort->value();
        QHostAddress address(ip);
        if (QAbstractSocket::IPv4Protocol == address.protocol()) {
        }
        controller_.connect_to_device(ip, port);
    }
}

void MainWindow::on_btnSend_clicked()
{
    auto data = ui->cB_msg_type->itemData(ui->cB_msg_type->currentIndex());
    Request_Type r_t = static_cast<Request_Type>(data.toInt());
    emit on_request(r_t);
}

void MainWindow::on_pushButton_clicked()
{
    QString str;
    str = ui->ln_number->text();
    if (str.isEmpty()) {
        return;
    }
    c_window= new C_window(str, this);
    connect(c_window, &C_window::cel_created, m_processor_, &MessageProcessor::set_cel);
    c_window->show();
}

void MainWindow::onKaSelected(const QModelIndex index)
{
    if(!index.isValid()) {
        return;
    }
    selectedKa = index.data().toInt();
    replotGraphs();
}

void MainWindow::onDataUpdated(int kaNumber)
{
    if (kaNumber == selectedKa) {
        replotGraphs();
    }
}
