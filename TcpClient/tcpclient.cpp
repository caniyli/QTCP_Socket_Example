#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
	: QObject{parent}
{

}

 TcpClient::~TcpClient()
 {
	delete socket;
 }

 void TcpClient::connectToHost(QString host, quint16 port)
 {
	this->host = QHostAddress{host};
	this->port = port;
	socket = new QTcpSocket{this};
	connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
	connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
	connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
	connect(socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &TcpClient::onError);
	socket->connectToHost(host, port);
 }

 void TcpClient::disconnectFromHost()
 {
	socket->disconnectFromHost();
 }

 void TcpClient::sendData(QString data)
 {
	QDataStream socketStream(socket);
	 socketStream.setVersion(QDataStream::Qt_5_15);
	 QByteArray byteArray = data.toUtf8();
	 socketStream.setVersion(QDataStream::Qt_5_15);
	 socketStream << byteArray;
 }

 void TcpClient::onConnected()
 {
	emit connected();
 }

 void TcpClient::onDisconnected()
 {
	emit disconnected();
 }


 void TcpClient::onReadyRead()
 {
	 QByteArray data;
	 data = socket->readAll();
	 QString message = QString::fromStdString(data.toStdString());
	 message.remove(0,4);
	emit dataReceived(message);
 }

 void TcpClient::onError(QAbstractSocket::SocketError error)
  {
	 qDebug() << "Error: " << error;
  }
