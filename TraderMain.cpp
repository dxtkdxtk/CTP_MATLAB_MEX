#include "mex.h"
#include "matrix.h"

#include<iostream>
#include<cstring>
#include<string>
#include<set>
#include "Connection.h"
#include "StructToMx.h"

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
            plhs[0] = GetMarketData(Con->callbackSet->GetInstrumentInfo(inst));
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
