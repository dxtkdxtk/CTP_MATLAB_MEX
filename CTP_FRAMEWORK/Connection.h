#ifndef CONNECTION_H
#define CONNECTION_H

#include "MdUserApi.h"
#include "TraderApi.h"
using namespace std;
//定义连接结构
class Connection
{
    
public:
    Connection()
    {
        
        msgQueue = new CTPMsgQueue();
        callbackSet = new FunctionCallBackSet();
        
        msgQueue->RegisterCallback(callbackSet);
        md = new MdUserApi();
        md->RegisterMsgQueue(msgQueue);
        td = new TraderApi();
        td->RegisterMsgQueue(msgQueue);
        msgQueue->StartThread();
        
    }
    ~Connection()
    {
        msgQueue->StopThread();
        msgQueue->Clear();
        td->Disconnect();
        md->Disconnect();
        
        delete td;
        delete md;
        delete callbackSet;
        delete msgQueue;
    }
    void readInifile(const char* file, const char *servername)
    {
        GetPrivateProfileStringA(servername, "path", "", tmp, sizeof(tmp), file);
        streamPath = tmp;
        GetPrivateProfileStringA(servername, "mdserver", "", tmp, sizeof(tmp), file);
        mdServer = tmp;
        GetPrivateProfileStringA(servername, "tdserver", "", tmp, sizeof(tmp), file);
        tdServer = tmp;
        GetPrivateProfileStringA(servername, "brokerid", "", tmp, sizeof(tmp), file);
        brokerId = tmp;
        GetPrivateProfileStringA(servername, "investorid", "", tmp, sizeof(tmp), file);
        investorId = tmp;
        GetPrivateProfileStringA(servername, "password", "", tmp, sizeof(tmp), file);
        password = tmp;
        GetPrivateProfileStringA(servername, "instrument", "", tmp, sizeof(tmp), file);
        instrumentId = tmp;
        
    }
    char tmp[105];
    CTPMsgQueue *msgQueue;
    FunctionCallBackSet *callbackSet;
    MdUserApi *md;
    TraderApi *td;
    
    string streamPath;
    string mdServer;
    string tdServer;
    string brokerId;
    string investorId;
    string password;
    string instrumentId;
    
    
    

};

#endif

