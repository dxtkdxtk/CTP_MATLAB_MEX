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
        mexErrMsgTxt("δ����!");
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    if(nrhs > 7)
        mexErrMsgTxt("�������̫��");
    else if(nrhs < 1)
        mexErrMsgTxt("�������̫��");
    
    if(!mxIsDouble(prhs[0]))
        mexErrMsgTxt("��һ����������Ϊ����");
    if(mxGetM(prhs[0]) != 1 || mxGetN(prhs[0]) != 1)
        mexErrMsgTxt("��һ�����������Ǿ���");
    int choise = (int)mxGetScalar(prhs[0]);
    
    
    
    switch(choise)
    {
        case 1:
        {
            if(nrhs != 2)
            {
                mexErrMsgTxt("������������Ϊ2");
            }
            if(NULL == Con)
            {
                Con = new Connection();
                CheckIsConnect();
                if(!mxIsChar(prhs[1]))
                        mexErrMsgTxt("�������ֶ�Ϊ�ַ���");
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
                mexPrintf("�������齻�׶˳ɹ�\n");
            }
            else
                mexWarnMsgTxt("�Ѿ�����!");
            break;
        }
        case 2:
        {
            CheckIsConnect();
            delete Con;
            Con = NULL;
            mexPrintf("�Ͽ����ӳɹ�\n");
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
            mexWarnMsgTxt("û���ҵ���ز���");
    
    }

}
