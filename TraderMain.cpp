#include "mex.h"
#include "matrix.h"

#include<iostream>
#include<cstring>
#include<string>
#include<set>
#include "Connection.h"

using namespace std;

Connection *Con;

void CheckIsConnect()
{
    if(NULL == Con)
        mexErrMsgTxt("未连接!");
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    if(nrhs > 7)
        mexErrMsgTxt("输入参数太多");
    else if(nrhs < 1)
        mexErrMsgTxt("输入参数太少");
    
    if(!mxIsDouble(prhs[0]))
        mexErrMsgTxt("第一个参数必须为数字");
    if(mxGetM(prhs[0]) != 1 || mxGetN(prhs[0]) != 1)
        mexErrMsgTxt("第一个参数不能是矩阵");
    int choise = (int)mxGetScalar(prhs[0]);
    
    
    
    switch(choise)
    {
        case 1:
        {
            if(nrhs != 2)
            {
                mexErrMsgTxt("参数个数必须为2");
            }
            if(NULL == Con)
            {
                Con = new Connection();
                CheckIsConnect();
                if(!mxIsChar(prhs[1]))
                        mexErrMsgTxt("服务器字段为字符串");
                Con->readInifile(".\\server.ini", mxArrayToString(prhs[1]));
                Con->td->Connect(Con->streamPath, 
                        Con->tdServer, 
                        Con->brokerId, 
                        Con->investorId,
                        Con->password, 
                        THOST_TERT_QUICK, "", "");
                Con->md->Connect(Con->streamPath, 
                        Con->mdServer, 
                        Con->brokerId, 
                        Con->investorId, 
                        Con->password);
                mexPrintf("连接行情交易端成功\n");
            }
            else
                mexWarnMsgTxt("已经连接!");
            break;
        }
        case 2:
        {
            CheckIsConnect();
            delete Con;
            Con = NULL;
            mexPrintf("断开连接成功\n");
            break;
        }
        case 3:
            CheckIsConnect();
            break;
        case 4:
            CheckIsConnect();
            break;
        case 5:
            CheckIsConnect();
            break;
        case 6:
            CheckIsConnect();
            break;
            
            
            
        default:
            mexWarnMsgTxt("没有找到相关操作");
    
    }

}
