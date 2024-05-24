#include "Process.h"
#include "Logger.h"

int CreateLogServer(CProcess* proc) {//日志服务器
    //printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());
    CLoggerServer server;
    int ret = server.Start();
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    if (ret != 0) {
        printf("%s(%d):%s pid=%d errno:%d msg:%s ret:%d\n", __FILE__, __LINE__, __FUNCTION__, getpid(), errno, strerror(errno), ret);
    }
    int fd = 0;
    while (true) {
        ret = proc->RecvFD(fd);
        if (fd == -1) break;
    }
    server.Close();
    return 0;
}

int CreateClientServer(CProcess* proc) {//处理客户端的服务器
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());
    int fd = -1;
    int ret = proc->RecvFD(fd);
    printf("%s(%d):%s ret=%d\n", __FILE__, __LINE__, __FUNCTION__, ret);
    printf("%s(%d):%s fd=%d\n", __FILE__, __LINE__, __FUNCTION__, fd);
    sleep(1);
    char buf[10] = "";
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, sizeof(buf));
    printf("%s(%d):%s buf=%s\n", __FILE__, __LINE__, __FUNCTION__, buf);
    close(fd);
    return 0;
}

int LogTest() {
    char buffer[] = "hello pm2600! 你好";
    usleep(1000 * 100);
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    TRACEI("here is log &d %c %f %g %s 哈哈 嘻嘻 大家好", 10, 'A', 1.0f, 2.0, buffer);
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    DUMPD((void*)buffer, (size_t)sizeof(buffer));
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    LOGE << 100 << " " << 'S' << " " << 0.12345f << " " << 1.23456789 << " " << buffer << " 你好世界";
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    return 0;
}

int main()
{
    //CProcess::SwithchDeamon();
    CProcess proclog, procclients;
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    proclog.SetEntryFunction(CreateLogServer, &proclog);
    int ret = proclog.CreateSubProcess();
    if (ret != 0) {
        printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());
        return -1;
    }
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    LogTest();

    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());
    procclients.SetEntryFunction(CreateClientServer, &procclients);
    ret = procclients.CreateSubProcess();
    if (ret != 0) {
        printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());
        return -2;
    }
    printf("%s(%d):%s pid=%d\n", __FILE__, __LINE__, __FUNCTION__, getpid());

    int fd = open("./test.txt", O_RDWR | O_CREAT | O_APPEND);
    printf("%s(%d):%s fd=%d\n", __FILE__, __LINE__, __FUNCTION__, fd);
    if (fd == -1) return -3;

    ret = procclients.SendFD(fd);
    printf("%s(%d):%s ret=%d\n", __FILE__, __LINE__, __FUNCTION__, ret);
    if (ret != 0) printf("errno:%d msg:%s\n", errno, strerror(errno));
    write(fd, "hello", 5);
    close(fd);
    proclog.SendFD(-1);
    return 0;
}