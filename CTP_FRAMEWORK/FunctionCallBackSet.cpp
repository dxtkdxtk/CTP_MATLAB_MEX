#include "FunctionCallBackSet.h"
#include <iostream>
#include <string>

#include "mex.h"
using namespace std;


bool FunctionCallBackSet::bIsGetInst;

HANDLE FunctionCallBackSet::h_connected;

CRITICAL_SECTION FunctionCallBackSet::f_csInstrument;
list<string> FunctionCallBackSet::lstAllInstruments;
string FunctionCallBackSet::strAllIns;

CRITICAL_SECTION FunctionCallBackSet::m_csInstPrice;
map<string, CThostFtdcDepthMarketDataField> FunctionCallBackSet::m_instPrice;

vector<CThostFtdcOrderField> FunctionCallBackSet::v_orders;
CRITICAL_SECTION FunctionCallBackSet::v_csOrders;
map<string, int> FunctionCallBackSet::mapOrderRef;

CRITICAL_SECTION FunctionCallBackSet::v_csPosition;
vector<CThostFtdcInvestorPositionField> FunctionCallBackSet::v_position;
    
    
void __stdcall FunctionCallBackSet::OnConnect(void* pApi, CThostFtdcRspUserLoginField *pRspUserLogin, ConnectionStatus result)
{
    SetEvent(h_connected);
}

void __stdcall FunctionCallBackSet::OnDisconnect(void* pApi, CThostFtdcRspInfoField *pRspInfo, ConnectionStatus step)
{

}

void __stdcall FunctionCallBackSet::OnErrRtnOrderAction(void* pTraderApi, CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{

}

void __stdcall FunctionCallBackSet::OnErrRtnOrderInsert(void* pTraderApi, CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{

}

void __stdcall FunctionCallBackSet::OnRspError(void* pApi, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspOrderAction(void* pTraderApi, CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspOrderInsert(void* pTraderApi, CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryDepthMarketData(void* pTraderApi, CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    
}

void __stdcall FunctionCallBackSet::OnRspQryInstrument(void* pTraderApi, CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CLock cl(&f_csInstrument);
    bIsGetInst = true;
//     cout << "合约名：" << pInstrument->InstrumentID;
//     string aa = pInstrument->InstrumentID;
//     string bb = pInstrument->CreateDate;
//     mexPrintf("%s  %s\n", aa.c_str(), bb.c_str());
//     
    strAllIns += pInstrument->InstrumentID;
    strAllIns += ';';
    lstAllInstruments.push_back(string(pInstrument->InstrumentID));
    
    
//     mexEvalString("OnRspQryInstrument");
//     mexCallMATLAB(0, NULL, 0, NULL, "OnRspQryInstrument");
    //Sleep(1);
//     cout << "  开始时间：" << pInstrument->CreateDate;
//     cout << "  结束时间：" << pInstrument->ExpireDate << endl;
}

void __stdcall FunctionCallBackSet::OnRspQryInstrumentCommissionRate(void* pTraderApi, CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryInstrumentMarginRate(void* pTraderApi, CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryInvestorPosition(void* pTraderApi, CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CLock cl(&v_csPosition);
    v_position.push_back(*pInvestorPosition);
}

void __stdcall FunctionCallBackSet::OnRspQryInvestorPositionDetail(void* pTraderApi, CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryOrder(void* pTraderApi, CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryTrade(void* pTraderApi, CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryTradingAccount(void* pTraderApi, CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRtnDepthMarketData(void* pMdUserApi, CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    CLock cl(&m_csInstPrice);
    
    memcpy(&m_instPrice[string(pDepthMarketData->InstrumentID)], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
    
}

void __stdcall FunctionCallBackSet::OnRtnInstrumentStatus(void* pTraderApi, CThostFtdcInstrumentStatusField *pInstrumentStatus)
{

}

void __stdcall FunctionCallBackSet::OnRtnOrder(void* pTraderApi, CThostFtdcOrderField *pOrder)
{
    CLock cl(&v_csOrders);
    string ref = pOrder->OrderRef;
    if(mapOrderRef[ref] == 0)
    {
        mapOrderRef[ref] = v_orders.size() + 1;
        v_orders.push_back(*pOrder);
    }
    //then change status
    else
    {
        if(pOrder->OrderStatus == '0' || pOrder->OrderStatus == '5')
        {
            v_orders.erase(v_orders.begin() + mapOrderRef[ref] - 1);
            mapOrderRef[ref] = 0;
        }
        else
            v_orders[mapOrderRef[ref] - 1].OrderStatus = pOrder->OrderStatus;
    }
}

void __stdcall FunctionCallBackSet::OnRtnTrade(void* pTraderApi, CThostFtdcTradeField *pTrade)
{

}