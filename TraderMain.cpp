#include "mex.h"
#include "matrix.h"

#include<iostream>
#include<cstring>
#include<string>
#include<set>
#include "Connection.h"
#include "mxStructTool.h"

using namespace std;

Connection *Con;

void CheckIsConnect()
{
    if(NULL == Con)
        mexErrMsgTxt("未连接!");
}
bool isNull(mxArray *tmp)
{
    return NULL == tmp;
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    //为保证速度，未添加安全判断
    int choise = (int)mxGetScalar(prhs[0]);
    switch(choise)
    {
        
        //连接CTP
        case 1:
        {
            if(NULL == Con)
            {
                Con = new Connection();
                CheckIsConnect();
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
                WaitForSingleObject(Con->callbackSet->h_connected, INFINITE);
                mexPrintf("连接行情交易端成功\n");
            }
            else
                mexWarnMsgTxt("已经连接!");
            break;
        }
        
        //断开CTP
        case 2:
        {
            CheckIsConnect();
            delete Con;
            Con = NULL;
            mexPrintf("断开连接成功\n");
            break;
        }
        
        //订阅行情
        case 3:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            if(inst.size() == 0)
            {
                if(Con->callbackSet->bIsGetInst)
                {
                    Con->md->Subscribe(Con->callbackSet->strAllIns);
                    mexPrintf("订阅完成\n");
                }
                else
                    mexWarnMsgTxt("未查询所有合约，不能使用订阅全部合约");
            }
            else
            {
                Con->md->Subscribe(inst);
                mexPrintf("订阅完成\n");
            }
            break;
        }
        
//         查询合约信息
        case 4:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            Con->td->ReqQryInstrument(inst);
            break;
        }
        
//         获取合约当前所有行情数据信息
        case 5:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            plhs[0] = GetMarketData(Con->callbackSet->GetInstrumentInfo(inst));
            break;
        }
        
        //下单操作
        case 6:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            string direction = mxArrayToString(prhs[2]);
            string offsetFlag = mxArrayToString(prhs[3]);
            double volume = mxGetScalar(prhs[4]);
            double price = mxGetScalar(prhs[5]);
            Con->td->ReqOrderInsert(inst, direction[0], offsetFlag.c_str(), "1", (int)volume, price, 
                    THOST_FTDC_OPT_LimitPrice, THOST_FTDC_TC_GFD, THOST_FTDC_CC_Immediately, 
                    0, THOST_FTDC_VC_AV);
            break;
        }   
        
        //获取所有报单信息
        case 7:
        {
            CheckIsConnect();
            plhs[0] = GetOrderData(Con->callbackSet->GetOrderInfo());
            break;
        }
        
        //撤单
        case 8:
        {
            CheckIsConnect();
            CThostFtdcOrderField order;
            MxToOrder(order, prhs[1]);
//             mexPrintf("%s\n", order.BrokerID);
//             mexPrintf("%d  %d\n", order.SessionID, order.FrontID);
            Con->td->ReqOrderAction(&order);
            break;
        }
        default:
            mexWarnMsgTxt("没有找到相关操作");
    
    }

}
