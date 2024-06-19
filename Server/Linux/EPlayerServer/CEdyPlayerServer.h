#pragma once
#include "Logger.h"
#include "CServer.h"
#include "HttpParser.h"
#include "Crypto.h"
#include "MysqlClient.h"
#include <map>


DECLARE_TABLE_CLASS(Login_user_mysql, _mysql_table_)
DECLARE_MYSQL_FIELD(TYPE_INT, user_id, NOT_NULL | PRIMARY_KEY | AUTOINCREMENT, "INTEGER", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_VARCHAR, user_qq, NOT_NULL, "VARCHAR", "(15)", "", "")  //QQ号
DECLARE_MYSQL_FIELD(TYPE_VARCHAR, user_phone, DEFAULT, "VARCHAR", "(11)", "'18888888888'", "")  //手机
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_name, NOT_NULL, "TEXT", "", "", "")    //姓名
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_nick, NOT_NULL, "TEXT", "", "", "")    //昵称
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_wechat, DEFAULT, "TEXT", "", "NULL", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_wechat_id, DEFAULT, "TEXT", "", "NULL", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_address, DEFAULT, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_province, DEFAULT, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_country, DEFAULT, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_INT, user_age, DEFAULT | CHECK, "INTEGER", "", "18", "")
DECLARE_MYSQL_FIELD(TYPE_INT, user_male, DEFAULT, "BOOL", "", "1", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_flags, DEFAULT, "TEXT", "", "0", "")
DECLARE_MYSQL_FIELD(TYPE_REAL, user_experience, DEFAULT, "REAL", "", "0.0", "")
DECLARE_MYSQL_FIELD(TYPE_INT, user_level, DEFAULT | CHECK, "INTEGER", "", "0", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_class_priority, DEFAULT, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_REAL, user_time_per_viewer, DEFAULT, "REAL", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_career, NONE, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_password, NOT_NULL, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_INT, user_birthday, NONE, "DATETIME", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_describe, NONE, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_TEXT, user_education, NONE, "TEXT", "", "", "")
DECLARE_MYSQL_FIELD(TYPE_INT, user_register_time, DEFAULT, "DATETIME", "", "LOCALTIME()", "")
DECLARE_TABLE_CLASS_EDN()

#define ERR_RETURN(ret, err) if(ret != 0){TRACEE("ret=%d errno=%s msg=[%s]", ret, errno, strerror(errno)); return err;}

#define WARN_CONTINUE(ret) if(ret != 0){TRACEW("ret=%d errno=%s msg=[%s]", ret, errno, strerror(errno)); continue;}

class CEdyPlayerServer : public CBusiness{
public:
	CEdyPlayerServer(unsigned count) : CBusiness() {
		m_count = count;
	}

	~CEdyPlayerServer() {
		if (m_db) {
			CDatabaseClient* db = m_db;
			m_db = NULL;
			db->Close();
			delete db;
		}
		m_epoll.Close();
		m_pool.Close();
		for (auto it : m_mapClients) {
			if (it.second) {
				delete it.second;
			}
		}
		m_mapClients.clear();
	}

	virtual int BusinessProcess(CProcess* proc) {
		using namespace std::placeholders;
		int ret = 0;
		m_db = new CMysqlClient();
		if (m_db == NULL) {
			TRACEE("no more memory!");
			return -1;
		}
		KeyValue args;
		args["host"] = "192.168.88.149";
		args["user"] = "root";
		args["password"] = "123456";
		args["port"] = 3306;
		args["db"] = "myim";
		ret = m_db->Connect(args);
		ERR_RETURN(ret, -2);

		ret = setConnectedCallback(&CEdyPlayerServer::Connected, this, _1);
		ERR_RETURN(ret, -3);
		ret = setRecvCallback(&CEdyPlayerServer::Received, this, _1, _2);
		ERR_RETURN(ret, -4);
		ret = m_epoll.Create(m_count);
		ERR_RETURN(ret, -5);
		ret = m_pool.Start(m_count);
		ERR_RETURN(ret, -6);
		for (unsigned i = 0; i < m_count; i++) {
			ret = m_pool.AddTask(&CEdyPlayerServer::ThreadFunc, this);
			ERR_RETURN(ret, -7);
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
		//客户端连接处理 简单打印客户端信息
		sockaddr_in* paddr = *pClient;
		
		TRACEI("client connected addr %s port:%d", inet_ntoa(paddr->sin_addr), paddr->sin_port);
		return 0;
	}
	int Received(CSocketBase* pClient, const Buffer& data) {
		//主要业务
		//HTTP解析
		int ret = 0;
		Buffer response = "";
		ret = HttpParser(data);
		if (ret != 0) { //验证失败
			TRACEE("http parser failed!%d", ret);
			//TODO:失败的应答

		}
		else { //验证成功
			//TODO:成功的应答
		}
		ret = pClient->Send(response);
		if (ret != 0) {
			TRACEE("http response failed! %d", ret);
		}
		else {
			TRACEI("http response success! %d", ret);
		}
		//验证结果的反馈
		return 0;
	}

	int HttpParser(const Buffer& data) {
		CHttpParser parser;
		size_t size = parser.Parser(data);
		if (size == 0 || (parser.Errno() != 0)) {
			TRACEE("size %llu errno:%u", size, parser.Errno());
			return -1;
		}
		if (parser.Method() == HTTP_GET) {
			//get处理
			UrlParser url("https://192.168.88.149" + parser.Url());
			int ret = url.Parser();
			if (ret != 0) {
				TRACEE("ret = %d url[%s]", ret, "https://192.168.88.149" + parser.Url());
				return -2;
			}
			Buffer uri = url.Uri();
			if (uri == "login") {
				//处理登录
				Buffer time = url["time"];
				Buffer salt = url["salt"];
				Buffer user = url["user"];
				Buffer sign = url["sign"];

				TRACEI("time:%s salt:%s user:%s sign:%s", (char*)time, (char*)salt, (char*)user, (char*)sign);
				//数据库查询
				Login_user_mysql dbuser;
				Result result;
				Buffer sql = dbuser.Query("username=\"" + user + "\"");
				ret = m_db->Exec(sql, result, dbuser);
				if (ret != 0) {
					TRACEE("sql=%s ret=%d", (char*)sql, ret);
					return -3;
				}
				if (result.size() == 0) {
					TRACEE("no result sql=%s ret=%d", (char*)sql, ret);
					return -4;
				}
				if (result.size() != 1) {
					TRACEE("more thar one sql=%s ret=%d", (char*)sql, ret);
					return -5;
				}
				auto user1 = result.front();
				Buffer pwd = *user1->Fields["user_password"]->Value.String;
				TRACEI("password = %s", (char*)pwd);
				//登录请求验证
				const char* MD5_KEY = "*&^%$#@b.v+h-b*g/h@n!h#n$d^ssx,.kl<kl";
				Buffer md5str = time + MD5_KEY + pwd + salt;
				Buffer md5 = Crypto::MD5(md5str);
				TRACEI("md5 = %s", (char*)md5);
				if (md5 == sign) {
					return 0;
				}
				return -6;
			}
		}
		else if (parser.Method() == HTTP_POST) {
			//post处理

		}
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
	CDatabaseClient* m_db;
};