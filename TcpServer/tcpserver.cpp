#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
	: QObject{parent}
{

}

void TcpServer::startServer()
{
	m_server = new QTcpServer{this};
	connect(m_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
	m_server->listen(QHostAddress::LocalHost, 8080);
}

void TcpServer::stopServer()
{
	m_server->close();
}

void TcpServer::sendMessage(QString message)
{
	QDataStream socketStream(m_socket);
	socketStream.setVersion(QDataStream::Qt_5_15);
	QByteArray byteArray = message.toUtf8();
	socketStream.setVersion(QDataStream::Qt_5_15);
	socketStream << byteArray;
}

void TcpServer::onNewConnection()
{
	qDebug() << "new connection";
	m_socket = m_server->nextPendingConnection();
	connect(m_socket, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
	connect(m_socket, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
	connect(m_socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &TcpServer::onError);
}

void TcpServer::onReadyRead()
{
	QByteArray data;
	data = m_socket->readAll();
	QString message = QString::fromStdString(data.toStdString());
	message.remove(0,4);
	message = QString::number(m_socket->socketDescriptor()) + " >> " + message;
	emit messageReceived(message);
}

void TcpServer::onDisconnected()
{
	m_socket->deleteLater();
}

void TcpServer::onError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "Error: " << socketError;
}

TcpServer::~TcpServer()
{
	m_server->close();
	m_socket->deleteLater();
}
