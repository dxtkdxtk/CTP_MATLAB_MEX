#include "mex.h"
#include "matrix.h"

#include<iostream>
#include<cstring>
#include<string>
#include<set>
#include "Connection.h"

using namespace std;

void mexExit(void)
{
    mexPrintf("exit now \n");
}
Connection *Con;

void CheckIsConnect()
{
    if(NULL == Con)
        mexErrMsgTxt("δ����!");
}
bool isNull(mxArray *tmp)
{
    return NULL == tmp;
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    int choise = (int)mxGetScalar(prhs[0]);
    mexAtExit(mexExit);
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
                        THOST_TERT_QUICK, "", "");
                Con->md->Connect(Con->streamPath, 
                        Con->mdServer, 
                        Con->brokerId, 
                        Con->investorId, 
                        Con->password);
                WaitForSingleObject(Con->callbackSet->h_connected, INFINITE);
                mexPrintf("�������齻�׶˳ɹ�\n");
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
            string inst = mxArrayToString(prhs[1]);
            Con->td->ReqQryInstrument(inst);
            break;
        }
        
//         ��ȡ��Լ��ǰ��������������Ϣ
        case 5:
        {
            CheckIsConnect();
            string inst = mxArrayToString(prhs[1]);
            CThostFtdcDepthMarketDataField res = Con->callbackSet->GetInstrumentInfo(inst);
            mwSize dims[2] = {1, 1};
            const char *field_names[] = {"TradingDay", "InstrumentID", "LastPrice", "PreSettlementPrice",\
                                                            "PreClosePrice", "PreOpenInterest", "OpenPrice", "HighestPrice", \
                                                            "LowestPrice", "Volume", "OpenInterest", "ClosePrice", "SettlementPrice",\
                                                            "UpperLimitPrice", "LowerLimitPrice", "PreDelta", "CurrDelta", "UpdateTime", \
                                                            "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1", "AveragePrice", "ActionDay"};
            
                                                            
            plhs[0] = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
            mxSetField(plhs[0], 0, "TradingDay", mxCreateString(res.TradingDay));
            mxSetField(plhs[0], 0, "InstrumentID", mxCreateString(res.InstrumentID));
            mxSetField(plhs[0], 0, "PreSettlementPrice", mxCreateDoubleScalar(res.PreSettlementPrice));
            mxSetField(plhs[0], 0, "PreClosePrice", mxCreateDoubleScalar(res.PreClosePrice));
            mxSetField(plhs[0], 0, "PreOpenInterest", mxCreateDoubleScalar(res.PreOpenInterest));
            mxSetField(plhs[0], 0, "OpenPrice", mxCreateDoubleScalar(res.OpenPrice));
            mxSetField(plhs[0], 0, "HighestPrice", mxCreateDoubleScalar(res.HighestPrice));
            mxSetField(plhs[0], 0, "LowestPrice", mxCreateDoubleScalar(res.LowestPrice));
            mxSetField(plhs[0], 0, "LastPrice", mxCreateDoubleScalar(res.LastPrice));
            
            mxSetField(plhs[0], 0, "Volume", mxCreateDoubleScalar(res.Volume));
            mxSetField(plhs[0], 0, "OpenInterest", mxCreateDoubleScalar(res.OpenInterest));
            mxSetField(plhs[0], 0, "ClosePrice", mxCreateDoubleScalar(res.ClosePrice));
            mxSetField(plhs[0], 0, "SettlementPrice", mxCreateDoubleScalar(res.SettlementPrice));
            mxSetField(plhs[0], 0, "UpperLimitPrice", mxCreateDoubleScalar(res.UpperLimitPrice));
            mxSetField(plhs[0], 0, "LowerLimitPrice", mxCreateDoubleScalar(res.LowerLimitPrice));
            mxSetField(plhs[0], 0, "PreDelta", mxCreateDoubleScalar(res.PreDelta));
            mxSetField(plhs[0], 0, "CurrDelta", mxCreateDoubleScalar(res.CurrDelta));
            mxSetField(plhs[0], 0, "UpdateTime", mxCreateString(res.UpdateTime));
            mxSetField(plhs[0], 0, "BidPrice1", mxCreateDoubleScalar(res.BidPrice1));
            mxSetField(plhs[0], 0, "BidVolume1", mxCreateDoubleScalar(res.BidVolume1));
            mxSetField(plhs[0], 0, "AskPrice1", mxCreateDoubleScalar(res.AskPrice1));
            mxSetField(plhs[0], 0, "AskVolume1", mxCreateDoubleScalar(res.AskVolume1));
            mxSetField(plhs[0], 0, "AveragePrice", mxCreateDoubleScalar(res.AveragePrice));
            mxSetField(plhs[0], 0, "ActionDay", mxCreateString(res.ActionDay));
//             mexPrintf("%lf\n", res.LastPrice);
//             plhs[0] = mxCreateDoubleScalar(res.LastPrice);
            break;
        }
            
        case 6:
        {
            CheckIsConnect();
            break;
        }   
            
        
        default:
            mexWarnMsgTxt("û���ҵ���ز���");
    
    }

}
