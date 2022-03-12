#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	server = new TcpServer();
	server->startServer();
	connect(server, &TcpServer::messageReceived,this,[=](QString message){
		ui->textBrowser->append(message);
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_buttonSend_clicked()
{
	server->sendMessage(ui->textEdit->toPlainText());
	ui->textEdit->clear();
}

