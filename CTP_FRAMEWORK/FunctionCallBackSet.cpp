#include "FunctionCallBackSet.h"
#include <iostream>
#include <string>
#include "mex.h"
using namespace std;

//是否已获取合约
bool FunctionCallBackSet::bIsGetInst;
bool FunctionCallBackSet::bIsConnected;

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
CRITICAL_SECTION FunctionCallBackSet::v_csOrders;
vector<CThostFtdcOrderField> FunctionCallBackSet::v_orders;
map<string, int> FunctionCallBackSet::mapOrderRef;

//持仓信息
CRITICAL_SECTION FunctionCallBackSet::v_csPosition;
vector<CThostFtdcInvestorPositionField> FunctionCallBackSet::v_position;



void __stdcall FunctionCallBackSet::OnConnect(void* pApi, CThostFtdcRspUserLoginField *pRspUserLogin, ConnectionStatus result)
{
    if(result == E_confirmed)
    {    
        bIsConnected = true;
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
    
    CLock cl(&m_csMarketData);
    memcpy(&m_marketData[string(pDepthMarketData->InstrumentID)], pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
    
}

void __stdcall FunctionCallBackSet::OnRtnInstrumentStatus(void* pTraderApi, CThostFtdcInstrumentStatusField *pInstrumentStatus)
{

}

void __stdcall FunctionCallBackSet::OnRtnOrder(void* pTraderApi, CThostFtdcOrderField *pOrder)
{
    CLock cl(&v_csOrders);
    string ref = pOrder->OrderRef;
    //若不存报单则加入
    if(mapOrderRef[ref] == 0)
    {
        if(!(pOrder->OrderStatus == '0' || pOrder->OrderStatus == '5'))
        {
            mapOrderRef[ref] = v_orders.size() + 1;
            v_orders.push_back(*pOrder);
        }
    }
    //若存在则修改报单状态
    else
    {
        v_orders[mapOrderRef[ref] - 1].OrderStatus = pOrder->OrderStatus;
//         //如果状态为所有成交或者已撤单，则去除这个报单
//         if(pOrder->OrderStatus == '0' || pOrder->OrderStatus == '5')
//         {
//             v_orders.erase(v_orders.begin() + mapOrderRef[ref] - 1);
//             mapOrderRef[ref] = 0;
//         }
//         //其他状态则直接修改状态
//         else
//         {
//                 
//         }
    }
}

void __stdcall FunctionCallBackSet::OnRtnTrade(void* pTraderApi, CThostFtdcTradeField *pTrade)
{

}