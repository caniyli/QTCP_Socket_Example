#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	client = new TcpClient();
	client->connectToHost("127.0.0.1", 8080);
	connect(client, &TcpClient::dataReceived, this, [=](QString data){
		ui->textBrowser->append(data);
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_buttonSend_clicked()
{
	client->sendData(ui->textEdit->toPlainText());
	ui->textEdit->clear();
}

