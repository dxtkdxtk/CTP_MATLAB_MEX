/*****************************************************************************
File name: FunctionCallBackSet.cpp
Description: Implement of FunctionCallBackSet.h 
Author: jebin
Date: 2014/07/10
History: see git log
*****************************************************************************/

#include "FunctionCallBackSet.h"
#include "Connection.h"

#include "mex.h"

#include <iostream>
#include <string>


using namespace std;

extern Connection *Con;

//是否已获取合约
bool FunctionCallBackSet::bIsGetInst;
bool FunctionCallBackSet::bIsTdConnected;
bool FunctionCallBackSet::bIsMdConnected;

//是否连接CTP
HANDLE FunctionCallBackSet::h_connected;
HANDLE FunctionCallBackSet::h_hasInst;


//当日参与交易合约信息
CRITICAL_SECTION FunctionCallBackSet::v_csInstInfo;
vector<CThostFtdcInstrumentField> FunctionCallBackSet::v_instInfo;
string FunctionCallBackSet::strAllIns;

//合约行情信息
CRITICAL_SECTION FunctionCallBackSet::m_csMarketData;
map<string, CThostFtdcDepthMarketDataField> FunctionCallBackSet::m_marketData;

//有效报单信息
CRITICAL_SECTION FunctionCallBackSet::m_csOrders;
map<pair<int, pair<int, string> >, CThostFtdcOrderField> FunctionCallBackSet::m_orders;

//持仓信息
CRITICAL_SECTION FunctionCallBackSet::m_csPosition;
map<pair<string, char>, CThostFtdcInvestorPositionField> FunctionCallBackSet::m_position;



void __stdcall FunctionCallBackSet::OnConnect(void* pApi, CThostFtdcRspUserLoginField *pRspUserLogin, ConnectionStatus result)
{
    static bool isTd = false;
    if(result == E_confirmed)
    {    
        bIsTdConnected = true;
        SetEvent(h_connected);
        isTd = true;
    }
    else if(isTd && result == E_logined)
    {
        bIsMdConnected = true;
        SetEvent(h_connected);
    }
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
    CLock cl(&v_csInstInfo);
    

    strAllIns += pInstrument->InstrumentID;
    strAllIns += ';';
    v_instInfo.push_back(*pInstrument);
    if(v_instInfo.size() >= 100)
    {
        SetEvent(h_hasInst);
        bIsGetInst = true;
    }
       

}

void __stdcall FunctionCallBackSet::OnRspQryInstrumentCommissionRate(void* pTraderApi, CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryInstrumentMarginRate(void* pTraderApi, CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void __stdcall FunctionCallBackSet::OnRspQryInvestorPosition(void* pTraderApi, CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CLock cl(&m_csPosition);
    if(pInvestorPosition->Position == 0)
    {
        m_position.erase(make_pair(pInvestorPosition->InstrumentID, pInvestorPosition->PosiDirection));
    }
    else
    {
        m_position[make_pair(pInvestorPosition->InstrumentID, pInvestorPosition->PosiDirection)] = *pInvestorPosition;
    }
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
    Con->td->ReqQryInvestorPosition(pDepthMarketData->InstrumentID);

    CLock cl(&m_csMarketData);
//     memcpy(&m_marketData[string(pDepthMarketData->InstrumentID)], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
    m_marketData[string(pDepthMarketData->InstrumentID)] = *pDepthMarketData;
}

void __stdcall FunctionCallBackSet::OnRtnInstrumentStatus(void* pTraderApi, CThostFtdcInstrumentStatusField *pInstrumentStatus)
{

}

void __stdcall FunctionCallBackSet::OnRtnOrder(void* pTraderApi, CThostFtdcOrderField *pOrder)
{
    CLock cl(&m_csOrders);
    pair<int, pair<int, string> > ref = make_pair(pOrder->FrontID, make_pair(pOrder->SessionID, pOrder->OrderRef));
    m_orders[ref] = *pOrder;

    
}

void __stdcall FunctionCallBackSet::OnRtnTrade(void* pTraderApi, CThostFtdcTradeField *pTrade)
{

}