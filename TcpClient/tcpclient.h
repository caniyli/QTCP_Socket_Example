#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
//#include <QTcpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QDataStream>

class TcpClient : public QObject
{
	Q_OBJECT
public:
	explicit TcpClient(QObject *parent = nullptr);
	~TcpClient();
	void connectToHost(QString host, quint16 port);
	void disconnectFromHost();
	void sendData(QString data);

signals:
	void dataReceived(QString data);
	void connected();
	void disconnected();
public slots:
	void onConnected();
	void onDisconnected();
	void onReadyRead();
	void onError(QAbstractSocket::SocketError error);
private:
	QTcpSocket *socket;
	QHostAddress host;
	quint16 port;
};

#endif // TCPCLIENT_H
