#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>

class TcpServer : public QObject
{
	Q_OBJECT
public:
	explicit TcpServer(QObject *parent = nullptr);
	~TcpServer();
	void startServer();
	void stopServer();
	void sendMessage(QString message);

signals:
	void messageReceived(QString message);
	
public slots:
	void onNewConnection();
	void onReadyRead();
	void onDisconnected();
	void onError(QAbstractSocket::SocketError socketError);

private:
	QTcpServer *m_server;
	QTcpSocket *m_socket;

};

#endif // TCPSERVER_H
