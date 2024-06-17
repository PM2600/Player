#pragma once
#include "Logger.h"
#include "CServer.h"
#include <map>

#define ERR_RETURN(ret, err) if(ret != 0){TRACEE("ret=%d errno=%s msg=[%s]", ret, errno, strerror(errno)); return err;}

#define WARN_CONTINUE(ret) if(ret != 0){TRACEW("ret=%d errno=%s msg=[%s]", ret, errno, strerror(errno)); continue;}

class CEdyPlayerServer : public CBusiness{
public:
	CEdyPlayerServer(unsigned count) : CBusiness() {
		m_count = count;
	}

	~CEdyPlayerServer() {
		m_epoll.Close();
		m_pool.Close();
		for (auto it : m_mapClients) {
			if (it.second) {
				delete it.second;
			}
		}
		m_mapClients.clear();
	}

	virtual int CBusinessProcess(CProcess* proc) {
		using namespace std::placeholders;
		int ret = 0;
		ret = setConnectedCallback(&CEdyPlayerServer::Connected, this, _1);
		ERR_RETURN(ret, -1);
		ret = setRecvCallback(&CEdyPlayerServer::Received, this, _1, _2);
		ERR_RETURN(ret, -2);

		ret = m_epoll.Create(m_count);
		ERR_RETURN(ret, -1);

		ret = m_pool.Start(m_count);
		ERR_RETURN(ret, -2);
		for (unsigned i = 0; i < m_count; i++) {
			ret = m_pool.AddTask(&CEdyPlayerServer::ThreadFunc, this);
			ERR_RETURN(ret, -3);
		}
		int sock = 0;
		sockaddr_in addrin;
		while (m_epoll != -1) {
			ret = proc->RecvSocket(sock, &addrin);
			if (ret < 0 || sock == 0) break;
			CSocketBase* pClient = new CSocket(sock);
			if (pClient == NULL) continue;
			pClient->Init(CSockParam(&addrin, SOCK_ISIP));
			WARN_CONTINUE(ret);
			ret = m_epoll.Add(sock, EpollData((void*)pClient));
			if (m_connectedcallback) {
				(*m_connectedcallback)(pClient);
			}
			WARN_CONTINUE(ret);
		}
		return 0;
	}
private:
	int Connected(CSocketBase* pClient) {
		//�ͻ������Ӵ��� �򵥴�ӡ�ͻ�����Ϣ
		sockaddr_in* paddr = *pClient;
		return 0;
	}
	int Received(CSocketBase* pClient, const Buffer& data) {
		//��Ҫҵ��
		//HTTP����
		//���ݿ��ѯ
		//��¼������֤
		//��֤����ķ���
		return 0;
	}
private:
	int ThreadFunc() {
		int ret = 0;
		EPEvents events;
		while (m_epoll != -1) {
			ssize_t size = m_epoll.WaitEvents(events);
			if (size < 0) break;
			if (size > 0) {
				for (ssize_t i = 0; i < size; i++) {
					if (events[i].events & EPOLLERR) {
						break;
					}
					else if (events[i].events & EPOLLIN) {
						CSocketBase* pClient = (CSocketBase*)events[i].data.ptr;
						if (pClient) {
							Buffer data;
							ret = pClient->Recv(data);
							WARN_CONTINUE(ret);
							if (m_recvcallback) {
								(*m_recvcallback)(pClient, data);
							}
						}
					}
				}
			}
		}
		return 0;
	}
private:
	CEpoll m_epoll;
	CThreadPool m_pool;
	std::map<int, CSocketBase*> m_mapClients;
	unsigned m_count;
};