/*****************************************************************************
File name: TraderMain.cpp
Description: CTP for matlab mex. Designed a series of operations to operate the CTP
Author: jebin
Version: 0.0.1
Date: 2014/07/10
History: see git log
*****************************************************************************/

#include "Connection.h"
#include "mxStructTool.h"

#include "mex.h"
#include "matrix.h"

#include<iostream>
#include<cstring>
#include<string>
#include<set>
#include<utility>

using namespace std;

//连接总参数
Connection *Con;

void CheckIsConnect()
{
    if(NULL == Con)
        mexErrMsgTxt("未连接CTP!");
}

//mex主函数入口
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
                        THOST_TERT_RESTART, "", "");
                WaitForSingleObject(Con->callbackSet->h_connected, 5000);
                if(Con->callbackSet->bIsTdConnected == false)
                {
                    delete Con;
                    Con = NULL;
                    mexPrintf("交易端连接失败\n");
                }
                else
                {
                    mexPrintf("交易端连接成功\n");
                    Con->md->Connect(Con->streamPath, 
                            Con->mdServer, 
                            Con->brokerId, 
                            Con->investorId, 
                            Con->password);
                    WaitForSingleObject(Con->callbackSet->h_connected, 5000);
                    if(Con->callbackSet->bIsMdConnected == false)
                    {
                        delete Con;
                        Con = NULL;
                        mexPrintf("行情端连接失败\n");
                    }
                    else
                    {
                        mexPrintf("行情端连接成功\n");
                        Con->td->ReqQryInstrument("");
                        mexPrintf("获取合约成功\n");
                    }
                }
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

            plhs[0] = GetInstInfo(Con->callbackSet->GetInstInfo());
            break;
        }
        
//         获取合约当前所有行情数据信息
        case 5:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            plhs[0] = GetMarketData(Con->callbackSet->GetMarketData(inst));
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
            int ref = Con->td->ReqOrderInsert(inst, direction[0], offsetFlag.c_str(), "1", (int)volume, price, 
                    THOST_FTDC_OPT_LimitPrice, THOST_FTDC_TC_GFD, THOST_FTDC_CC_Immediately, 
                    0, THOST_FTDC_VC_AV);
            plhs[0] = mxCreateDoubleScalar(ref);
            break;
        }   
        
        //获取所有报单信息
        case 7:
        {
            CheckIsConnect();
            pair<int, pair<int, string> > order = make_pair(0, make_pair(0, ""));
            plhs[0] = GetOrderData(Con->callbackSet->GetOrderInfo(), order);
            break;
        }
        
        //撤单
        case 8:
        {
            CheckIsConnect();
            CThostFtdcOrderField order;
            MxToOrder(order, prhs[1]);
            Con->td->ReqOrderAction(&order);
            break;
        }
        
        //获取所有持仓信息
        case 9:
        {
            CheckIsConnect();
            plhs[0] = GetPositionData(Con->callbackSet->GetPosition());
            break;
        }
        
        //判断是否连接
        case 10:
        {
            bool isconnect = !(NULL == Con);
            plhs[0] = mxCreateLogicalScalar(isconnect);
            break;
        }
        //按报单引用撤单
        case 11:
        {
            CheckIsConnect();
            map<pair<int, pair<int, string> >, CThostFtdcOrderField> &orders = Con->callbackSet->m_orders;
            string ref = mxArrayToString(prhs[1]);
            pair<int, pair<int, string> > order = 
                    make_pair(Con->td->m_RspUserLogin.FrontID, make_pair(Con->td->m_RspUserLogin.SessionID, ref));
            if(orders.find(order) != orders.end())
                Con->td->ReqOrderAction(&orders[order]);
            else
                mexErrMsgTxt("未存在此报单\n");
            break;
        }
        //按报单引用获取报单信息(当前连接)
        case 12:
        {
            CheckIsConnect();
            map<pair<int, pair<int, string> >, CThostFtdcOrderField> &orders = Con->callbackSet->m_orders;
            string ref = mxArrayToString(prhs[1]);
             pair<int, pair<int, string> > order = 
                    make_pair(Con->td->m_RspUserLogin.FrontID, make_pair(Con->td->m_RspUserLogin.SessionID, ref));
             if(orders.find(order) != orders.end())
                plhs[0] = GetOrderData(Con->callbackSet->GetOrderInfo(), order);
            else
                mexErrMsgTxt("未存在此报单\n");
            break;
        }
        //获取指定连接报单
        case 13: 
        {
            CheckIsConnect();
            map<pair<int, pair<int, string> >, CThostFtdcOrderField> &orders = Con->callbackSet->m_orders;
            
            int frontid = (int)mxGetScalar(prhs[1]);
            int session = (int)mxGetScalar(prhs[2]);
            string ref = mxArrayToString(prhs[3]);
            
            pair<int, pair<int, string> > order = 
                    make_pair(frontid, make_pair(session, ref));
            if(orders.find(order) != orders.end())
                plhs[0] = GetOrderData(Con->callbackSet->GetOrderInfo(), order);
            else
                mexErrMsgTxt("未存在此报单\n");
            break;
        }
        case 14: 
        {
            CheckIsConnect();
            plhs[0] = GetPositionData(Con->callbackSet->GetPosition(), mxArrayToString(prhs[1]));
            break;
        }
        default:
            mexErrMsgTxt("没有找到相关操作");
    
    }

}
