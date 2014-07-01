#ifndef FUNCTION_CALL_BACK_H
#define FUNCTION_CALL_BACK_H

#include "CTPStruct.h"
#include "ThostTraderApi\ThostFtdcUserApiStruct.h"
#include "CLock.h"
#include <list>
#include <Windows.h>
#include <map>
#include <vector>
#include <set>
using namespace std;
class FunctionCallBackSet
{

    
public:
    //是否已获取合约
    static bool bIsGetInst;
    
    //所有合约，以分号隔开形式
    static string strAllIns;
    
    //是否连接事件
    static HANDLE h_connected;
    
    //所有合约list
    static CRITICAL_SECTION f_csInstrument;
    static list<string> lstAllInstruments;
    
    //当前合约价格
    static CRITICAL_SECTION m_csInstPrice;
    static map<string, CThostFtdcDepthMarketDataField> m_instPrice;
    
   //所有当前未结束有效报单
    static CRITICAL_SECTION v_csOrders;
    static vector<CThostFtdcOrderField> v_orders;
    static set<string> orderRef;
    
    
    FunctionCallBackSet()
    {
        bIsGetInst = false;
        h_connected = CreateEvent(NULL, TRUE, FALSE, NULL);
        lstAllInstruments.clear();
        strAllIns = "";
        orderRef.clear();
        m_instPrice.clear();
        v_orders.clear();
        InitializeCriticalSection(&f_csInstrument);
        InitializeCriticalSection(&m_csInstPrice);
        InitializeCriticalSection(&v_csOrders);
    }
    ~FunctionCallBackSet()
    {
        CloseHandle(h_connected);
        DeleteCriticalSection(&f_csInstrument);
        DeleteCriticalSection(&m_csInstPrice);
        DeleteCriticalSection(&v_csOrders);
    }

    CThostFtdcDepthMarketDataField &GetInstrumentInfo(string ins)
    {
        CLock cl(&m_csInstPrice);
        return m_instPrice[ins];
    }
    vector<CThostFtdcOrderField> &GetOrderInfo()
    {
        CLock cl(&v_csOrders);
        return v_orders;
    }
    static void __stdcall OnConnect(void* pApi, CThostFtdcRspUserLoginField *pRspUserLogin, ConnectionStatus result);//连接后的结果状态
    static void __stdcall OnDisconnect(void* pApi, CThostFtdcRspInfoField *pRspInfo, ConnectionStatus step);//出错时所处的状态
    static void __stdcall OnErrRtnOrderAction(void* pTraderApi, CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
    static void __stdcall OnErrRtnOrderInsert(void* pTraderApi, CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
    static void __stdcall OnRspError(void* pApi, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspOrderAction(void* pTraderApi, CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspOrderInsert(void* pTraderApi, CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryDepthMarketData(void* pTraderApi, CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInstrument(void* pTraderApi, CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInstrumentCommissionRate(void* pTraderApi, CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInstrumentMarginRate(void* pTraderApi, CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInvestorPosition(void* pTraderApi, CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInvestorPositionDetail(void* pTraderApi, CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryOrder(void* pTraderApi, CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryTrade(void* pTraderApi, CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryTradingAccount(void* pTraderApi, CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRtnDepthMarketData(void* pMdUserApi, CThostFtdcDepthMarketDataField *pDepthMarketData);
    static void __stdcall OnRtnInstrumentStatus(void* pTraderApi, CThostFtdcInstrumentStatusField *pInstrumentStatus);
    static void __stdcall OnRtnOrder(void* pTraderApi, CThostFtdcOrderField *pOrder);
    static void __stdcall OnRtnTrade(void* pTraderApi, CThostFtdcTradeField *pTrade);
    
};

#endif