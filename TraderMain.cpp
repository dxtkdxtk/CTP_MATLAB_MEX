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

//�����ܲ���
Connection *Con;

void CheckIsConnect()
{
    if(NULL == Con)
        mexErrMsgTxt("δ����CTP!");
}

//mex���������
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    //Ϊ��֤�ٶȣ�δ��Ӱ�ȫ�ж�
    int choise = (int)mxGetScalar(prhs[0]);
    switch(choise)
    {
        
        //����CTP
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
                    mexPrintf("���׶�����ʧ��\n");
                }
                else
                {
                    mexPrintf("���׶����ӳɹ�\n");
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
                        mexPrintf("���������ʧ��\n");
                    }
                    else
                    {
                        mexPrintf("��������ӳɹ�\n");
                        Con->td->ReqQryInstrument("");
                        mexPrintf("��ȡ��Լ�ɹ�\n");
                    }
                }
            }
            else
                mexWarnMsgTxt("�Ѿ�����!");
            break;
        }
        
        //�Ͽ�CTP
        case 2:
        {
            CheckIsConnect();
            delete Con;
            Con = NULL;
            mexPrintf("�Ͽ����ӳɹ�\n");
            break;
        }
        
        //��������
        case 3:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            if(inst.size() == 0)
            {
                if(Con->callbackSet->bIsGetInst)
                {
                    Con->md->Subscribe(Con->callbackSet->strAllIns);
                    mexPrintf("�������\n");
                }
                else
                    mexWarnMsgTxt("δ��ѯ���к�Լ������ʹ�ö���ȫ����Լ");
            }
            else
            {
                Con->md->Subscribe(inst);
                mexPrintf("�������\n");
            }
            break;
        }
        
//         ��ѯ��Լ��Ϣ
        case 4:
        {
            CheckIsConnect();

            plhs[0] = GetInstInfo(Con->callbackSet->GetInstInfo());
            break;
        }
        
//         ��ȡ��Լ��ǰ��������������Ϣ
        case 5:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            plhs[0] = GetMarketData(Con->callbackSet->GetMarketData(inst));
            break;
        }
        
        //�µ�����
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
        
        //��ȡ���б�����Ϣ
        case 7:
        {
            CheckIsConnect();
            pair<int, pair<int, string> > order = make_pair(0, make_pair(0, ""));
            plhs[0] = GetOrderData(Con->callbackSet->GetOrderInfo(), order);
            break;
        }
        
        //����
        case 8:
        {
            CheckIsConnect();
            CThostFtdcOrderField order;
            MxToOrder(order, prhs[1]);
            Con->td->ReqOrderAction(&order);
            break;
        }
        
        //��ȡ���гֲ���Ϣ
        case 9:
        {
            CheckIsConnect();
            plhs[0] = GetPositionData(Con->callbackSet->GetPosition());
            break;
        }
        
        //�ж��Ƿ�����
        case 10:
        {
            bool isconnect = !(NULL == Con);
            plhs[0] = mxCreateLogicalScalar(isconnect);
            break;
        }
        //���������ó���
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
                mexErrMsgTxt("δ���ڴ˱���\n");
            break;
        }
        //���������û�ȡ������Ϣ(��ǰ����)
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
                mexErrMsgTxt("δ���ڴ˱���\n");
            break;
        }
        //��ȡָ�����ӱ���
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
                mexErrMsgTxt("δ���ڴ˱���\n");
            break;
        }
        case 14: 
        {
            CheckIsConnect();
            plhs[0] = GetPositionData(Con->callbackSet->GetPosition(), mxArrayToString(prhs[1]));
            break;
        }
        default:
            mexErrMsgTxt("û���ҵ���ز���");
    
    }

}
