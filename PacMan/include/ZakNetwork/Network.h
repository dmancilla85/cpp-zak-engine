#ifndef _Network_H_
#define _Network_H_

#include "enet/enet.h"
#include <windows.h>

#ifdef ZAKNETWORK_EXPORTS
#define NETWORK_API __declspec(dllexport)
#else
#define NETWORK_API __declspec(dllimport)
#endif // ZAKNETWORK_EXPORTS

#define MAX_CHARS 100

typedef ENetHost ZakNetHost;
typedef ENetPeer ZakNetPeer;
typedef ENetEvent ZakNetEvent;
typedef enet_uint16 Zakuint16;

enum ZAK_NETWORK_STATE {
	ZAK_STATE_NONE = 0,
	ZAK_STATE_CONNECTED = 1,
	ZAK_STATE_DISCONNECTED = 2,
	ZAK_STATE_CONNECTING = 3,
	ZAK_STATE_DISCONNECTING = 4,
	ZAK_STATE_WAITING = 5
};

enum ZAK_NETWORK_WAITTYPE {
	ZAK_WAIT_NONE = 0,
	ZAK_WAIT_ATLEASTONE = 1,
	ZAK_WAIT_FORALL = 2,
};

namespace zak {

class NETWORK_API Network
{
public:
	bool StartUp();
	bool ShutDown();
	bool CreateServerHost(Zakuint16 iPort, size_t peerCount, ZAK_NETWORK_WAITTYPE waitType=ZAK_WAIT_NONE);
	bool CreateClientHost(char *szName);
	bool DestroyHost();
	void Update(enet_uint32 iTimeOut=1);
	void Send(ZakNetPeer* peerTo, char *data, size_t size, int iChannel, bool bReliable);
    void SendBroadcast(char *data, size_t size, int iChannel, bool bReliable);
	bool ConnectToHost(char *to, Zakuint16 port, int iChannels);
	void Disconnect();
	void ResetPeers();
	int	 ConnectionsCount() { return m_iConnectedPeers; }
	ZAK_NETWORK_STATE GetState() { return m_State; }

	ZakNetHost *GetHost() { return m_Host; }	
	ZakNetPeer *GetPeer() { return m_Peer; }

	virtual void OnConnect(ZakNetEvent connect){}
	virtual void OnReceived(ZakNetEvent received){}
	virtual void OnDisconnect(ZakNetEvent disconnect){}


	Network();
	~Network();

protected:
	ZakNetHost	*m_Host;
	ZakNetPeer	*m_Peer;
    ENetEvent	m_Event;
	char		m_szPeerData[MAX_CHARS];

	ZAK_NETWORK_STATE		m_State;
	ZAK_NETWORK_WAITTYPE	m_WaitType;

	bool		m_bServer;
	int			m_iConnectedPeers;
	int			m_iMaxConnections;
	
private:
};

} // End namespace

#endif // _Network_H_