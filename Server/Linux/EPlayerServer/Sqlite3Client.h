#pragma once
#include "Public.h"
#include "DatabaseHelper.h"
#include "sqlite3/sqlite3.h"

class CSqlite3Client : public CDatabaseClient
{
public:
	CSqlite3Client(const CSqlite3Client&) = delete;
	CSqlite3Client& operator=(const CSqlite3Client&) = delete;
public:
	CSqlite3Client() { 
		m_db = NULL;
		m_stmt = NULL; 
	}
	virtual ~CSqlite3Client() {
		Close();
	}
public:
	//����
	virtual int Connect(const KeyValue& args);
	//ִ��
	virtual int Exec(const Buffer& sql);
	//�������ִ��
	virtual int Exec(const Buffer& sql, Result& result, const _Table_& table);
	//��������
	virtual int StartTransaction();
	//�ύ����
	virtual int CommitTransaction();
	//�ع�����
	virtual int RollbackTransaction();
	//�ر�����
	virtual int Close();
	//�Ƿ�����
	virtual bool IsConnected();

private:
	static int ExecCallback(void* arg, int count, char** names, char** values);
	int ExecCallback(Result& result, const _Table_& table, int count, char** name, char** values);
private:
	sqlite3_stmt* m_stmt;
	sqlite3* m_db;
private:
	class ExecParam {
	public:
		ExecParam(CSqlite3Client* obj, Result& result, const _Table_& table)
			:obj(obj), result(result), table(table) {}
		CSqlite3Client* obj;
		Result& result;
		const _Table_& table;
	};
};
