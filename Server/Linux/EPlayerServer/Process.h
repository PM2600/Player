#pragma once
#include "Function.h"
#include <memory.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <netinet/in.h>

class CProcess {
public:
    CProcess() {
        m_func = NULL;
        memset(pipes, 0, sizeof(pipes));
    }
    ~CProcess() {
        if (m_func != NULL) {
            delete m_func;
            m_func = NULL;
        }
    }
    template<typename _FUNCTION_, typename... _ARGS_>
    int SetEntryFunction(_FUNCTION_ func, _ARGS_... args) {
        m_func = new CFunction<_FUNCTION_, _ARGS_...>(func, args...);
        return 0;
    }

    int CreateSubProcess() {
        if (m_func == NULL) return -1;
        int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, pipes);
        if (ret == -1) return -2;
        pid_t pid = fork();
        if (pid == -1) return -3;
        if (pid == 0) {
            //�ӽ���
            close(pipes[1]); //�ر�д 
            pipes[1] = 0;
            ret = (*m_func)();
            exit(0);
        }
        close(pipes[0]);
        pipes[0] = 0;
        m_pid = pid;
        return 0;
    }

    int SendFD(int fd) {
        struct msghdr msg;
        iovec iov[2];
        char buf[2][10] = { "PM25", "PM26" };
        iov[0].iov_base = buf[0];
        iov[0].iov_len = sizeof(buf[0]);
        iov[1].iov_base = buf[1];
        iov[1].iov_len = sizeof(buf[1]);
        msg.msg_iov = iov;
        msg.msg_iovlen = 2;

        cmsghdr* cmsg = (cmsghdr*)calloc(1, CMSG_LEN(sizeof(int)));
        if (cmsg == NULL) return -1;
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        *(int*)CMSG_DATA(cmsg) = fd;
        msg.msg_control = cmsg;
        msg.msg_controllen = cmsg->cmsg_len;
        ssize_t ret = sendmsg(pipes[1], &msg, 0);
        free(cmsg);

        if (ret == -1) {
            return -2;
        }
        return 0;
    }

    int RecvFD(int& fd) {
        msghdr msg;
        iovec iov[2];
        char buf[][10] = { "", "" };
        iov[0].iov_base = buf[0];
        iov[0].iov_len = sizeof(buf[0]);
        iov[1].iov_base = buf[1];
        iov[1].iov_len = sizeof(buf[1]);
        msg.msg_iov = iov;
        msg.msg_iovlen = 2;

        cmsghdr* cmsg = (cmsghdr*)calloc(1, CMSG_LEN(sizeof(int)));
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        msg.msg_control = cmsg;
        msg.msg_controllen = CMSG_LEN(sizeof(int));
        ssize_t ret = recvmsg(pipes[0], &msg, 0);
        if (ret == -1) {
            free(cmsg);
            return -2;
        }
        fd = *(int*)CMSG_DATA(cmsg);
        free(cmsg);
        return 0;
    }

    int SendSocket(int fd, const sockaddr_in* addrin) {
        struct msghdr msg;
        iovec iov[2];
        char buf[2][10] = { "PM25", "PM26" };
        iov[0].iov_base = (void*)addrin;
        iov[0].iov_len = sizeof(sockaddr_in);
        iov[1].iov_base = buf[1];
        iov[1].iov_len = sizeof(buf[1]);
        msg.msg_iov = iov;
        msg.msg_iovlen = 2;

        cmsghdr* cmsg = (cmsghdr*)calloc(1, CMSG_LEN(sizeof(int)));
        if (cmsg == NULL) return -1;
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        *(int*)CMSG_DATA(cmsg) = fd;
        msg.msg_control = cmsg;
        msg.msg_controllen = cmsg->cmsg_len;
        ssize_t ret = sendmsg(pipes[1], &msg, 0);
        free(cmsg);

        if (ret == -1) {
            return -2;
        }
        return 0;
    }

    int RecvSocket(int& fd, sockaddr_in* addrin) {
        msghdr msg;
        iovec iov[2];
        char buf[][10] = { "", "" };
        iov[0].iov_base = addrin;
        iov[0].iov_len = sizeof(addrin);
        iov[1].iov_base = buf[1];
        iov[1].iov_len = sizeof(buf[1]);
        msg.msg_iov = iov;
        msg.msg_iovlen = 2;

        cmsghdr* cmsg = (cmsghdr*)calloc(1, CMSG_LEN(sizeof(int)));
        cmsg->cmsg_len = CMSG_LEN(sizeof(int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        msg.msg_control = cmsg;
        msg.msg_controllen = CMSG_LEN(sizeof(int));
        ssize_t ret = recvmsg(pipes[0], &msg, 0);
        if (ret == -1) {
            free(cmsg);
            return -2;
        }
        fd = *(int*)CMSG_DATA(cmsg);
        free(cmsg);
        return 0;
    }

    static int SwithchDeamon() {
        pid_t ret = fork();
        if (ret == -1) return -1;
        if (ret > 0) exit(0);

        ret = setsid();
        if (ret == -1) return -2;
        ret = fork();
        if (ret == -1) return -3;
        if (ret > 0) exit(0);

        for (int i = 0; i < 3; i++) {
            close(i);
        }
        umask(0);
        signal(SIGCHLD, SIG_IGN);
        return 0;
    }

private:
    CFunctionBase* m_func;
    pid_t m_pid;
    int pipes[2];
};
