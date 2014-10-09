/*****************************************************************************
 * File name: mxStructTool.h
 * Description: Defined operations for convert matlab struct to c++ struct bothway
 * Author: jebin
 * Date: 2014/07/10
 * History: see git log
 *****************************************************************************/

#ifndef MXSTRUCTTOOL_H
#define MXSTRUCTTOOL_H

#include "Connection.h"

#include "mex.h"
#include "matrix.h"

//转换行情数据
mxArray *GetMarketData(const CThostFtdcDepthMarketDataField &data)
{
    mwSize dims[2] = {1, 1};
    const char *field_names[] = {"TradingDay", "InstrumentID", "LastPrice", "PreSettlementPrice",\
            "PreClosePrice", "PreOpenInterest", "OpenPrice", "HighestPrice", \
            "LowestPrice", "Volume", "OpenInterest", "ClosePrice", "SettlementPrice",\
            "UpperLimitPrice", "LowerLimitPrice", "PreDelta", "CurrDelta", "UpdateTime", \
            "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1", "AveragePrice", "ActionDay",
    "UpdateMillisec"};
    mxArray *result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    mxSetField(result, 0, "TradingDay", mxCreateString(data.TradingDay));
    mxSetField(result, 0, "InstrumentID", mxCreateString(data.InstrumentID));
    mxSetField(result, 0, "PreSettlementPrice", mxCreateDoubleScalar(data.PreSettlementPrice));
    mxSetField(result, 0, "PreClosePrice", mxCreateDoubleScalar(data.PreClosePrice));
    mxSetField(result, 0, "PreOpenInterest", mxCreateDoubleScalar(data.PreOpenInterest));
    mxSetField(result, 0, "OpenPrice", mxCreateDoubleScalar(data.OpenPrice));
    mxSetField(result, 0, "HighestPrice", mxCreateDoubleScalar(data.HighestPrice));
    mxSetField(result, 0, "LowestPrice", mxCreateDoubleScalar(data.LowestPrice));
    mxSetField(result, 0, "LastPrice", mxCreateDoubleScalar(data.LastPrice));
    mxSetField(result, 0, "Volume", mxCreateDoubleScalar(data.Volume));
    mxSetField(result, 0, "OpenInterest", mxCreateDoubleScalar(data.OpenInterest));
    mxSetField(result, 0, "ClosePrice", mxCreateDoubleScalar(data.ClosePrice));
    mxSetField(result, 0, "SettlementPrice", mxCreateDoubleScalar(data.SettlementPrice));
    mxSetField(result, 0, "UpperLimitPrice", mxCreateDoubleScalar(data.UpperLimitPrice));
    mxSetField(result, 0, "LowerLimitPrice", mxCreateDoubleScalar(data.LowerLimitPrice));
    mxSetField(result, 0, "PreDelta", mxCreateDoubleScalar(data.PreDelta));
    mxSetField(result, 0, "CurrDelta", mxCreateDoubleScalar(data.CurrDelta));
    mxSetField(result, 0, "UpdateTime", mxCreateString(data.UpdateTime));
    mxSetField(result, 0, "BidPrice1", mxCreateDoubleScalar(data.BidPrice1));
    mxSetField(result, 0, "BidVolume1", mxCreateDoubleScalar(data.BidVolume1));
    mxSetField(result, 0, "AskPrice1", mxCreateDoubleScalar(data.AskPrice1));
    mxSetField(result, 0, "AskVolume1", mxCreateDoubleScalar(data.AskVolume1));
    mxSetField(result, 0, "AveragePrice", mxCreateDoubleScalar(data.AveragePrice));
    mxSetField(result, 0, "ActionDay", mxCreateString(data.ActionDay));
    mxSetField(result, 0, "UpdateMillisec", mxCreateDoubleScalar(data.UpdateMillisec));
    return result;
}

mxArray *GetMarketData(set<string> &subInst, map<string, CThostFtdcDepthMarketDataField> &marketdata)
{
    int size = subInst.size();
    mwSize dims[2] = {size, 1};
    const char *field_names[] = {"TradingDay", "InstrumentID", "LastPrice", "PreSettlementPrice",\
            "PreClosePrice", "PreOpenInterest", "OpenPrice", "HighestPrice", \
            "LowestPrice", "Volume", "OpenInterest", "ClosePrice", "SettlementPrice",\
            "UpperLimitPrice", "LowerLimitPrice", "PreDelta", "CurrDelta", "UpdateTime", \
            "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1", "AveragePrice", "ActionDay",
    "UpdateMillisec"};
    mxArray *result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    int i = 0;
    set<string>::iterator iter;
    CThostFtdcDepthMarketDataField data;
    for(iter = subInst.begin(); iter != subInst.end(); ++iter)
    {
        data = marketdata[string(iter->c_str())];
//         memcpy(&data, &marketdata[iter->c_str()], sizeof(CThostFtdcDepthMarketDataField));
        mxSetField(result, i, "TradingDay", mxCreateString(data.TradingDay));
        mxSetField(result, i, "InstrumentID", mxCreateString(data.InstrumentID));
        mxSetField(result, i, "PreSettlementPrice", mxCreateDoubleScalar(data.PreSettlementPrice));
        mxSetField(result, i, "PreClosePrice", mxCreateDoubleScalar(data.PreClosePrice));
        mxSetField(result, i, "PreOpenInterest", mxCreateDoubleScalar(data.PreOpenInterest));
        mxSetField(result, i, "OpenPrice", mxCreateDoubleScalar(data.OpenPrice));
        mxSetField(result, i, "HighestPrice", mxCreateDoubleScalar(data.HighestPrice));
        mxSetField(result, i, "LowestPrice", mxCreateDoubleScalar(data.LowestPrice));
        mxSetField(result, i, "LastPrice", mxCreateDoubleScalar(data.LastPrice));
        mxSetField(result, i, "Volume", mxCreateDoubleScalar(data.Volume));
        mxSetField(result, i, "OpenInterest", mxCreateDoubleScalar(data.OpenInterest));
        mxSetField(result, i, "ClosePrice", mxCreateDoubleScalar(data.ClosePrice));
        mxSetField(result, i, "SettlementPrice", mxCreateDoubleScalar(data.SettlementPrice));
        mxSetField(result, i, "UpperLimitPrice", mxCreateDoubleScalar(data.UpperLimitPrice));
        mxSetField(result, i, "LowerLimitPrice", mxCreateDoubleScalar(data.LowerLimitPrice));
        mxSetField(result, i, "PreDelta", mxCreateDoubleScalar(data.PreDelta));
        mxSetField(result, i, "CurrDelta", mxCreateDoubleScalar(data.CurrDelta));
        mxSetField(result, i, "UpdateTime", mxCreateString(data.UpdateTime));
        mxSetField(result, i, "BidPrice1", mxCreateDoubleScalar(data.BidPrice1));
        mxSetField(result, i, "BidVolume1", mxCreateDoubleScalar(data.BidVolume1));
        mxSetField(result, i, "AskPrice1", mxCreateDoubleScalar(data.AskPrice1));
        mxSetField(result, i, "AskVolume1", mxCreateDoubleScalar(data.AskVolume1));
        mxSetField(result, i, "AveragePrice", mxCreateDoubleScalar(data.AveragePrice));
        mxSetField(result, i, "ActionDay", mxCreateString(data.ActionDay));
        mxSetField(result, i, "UpdateMillisec", mxCreateDoubleScalar(data.UpdateMillisec));
        ++i;
    }
    return result;
}

//转换报单数据
mxArray *GetOrderData(map<pair<int, pair<int, string> >, CThostFtdcOrderField> &data, pair<int, pair<int, string> > &order)
{
    mxArray *result;
    const char *field_names[] = {"BrokerID", "InvestorID", "InstrumentID", "OrderRef", "UserID", "Direction",
    "CombOffsetFlag", "LimitPrice", "ExchangeID", "OrderSysID",
    "OrderStatus", "FrontID", "SessionID"};
    if(order.second.second.size() == 0)
    {
        int size = data.size();
        mwSize dims[2] = {1, size};
        
        result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
        map<pair<int, pair<int, string> >, CThostFtdcOrderField>::iterator iter;
        int i = 0;
        for(iter = data.begin(); iter != data.end(); ++iter)
        {
            string tmp;
            mxSetField(result, i, "BrokerID", mxCreateString(iter->second.BrokerID));
            mxSetField(result, i, "InvestorID", mxCreateString(iter->second.InvestorID));
            mxSetField(result, i, "InstrumentID", mxCreateString(iter->second.InstrumentID));
            mxSetField(result, i, "OrderRef", mxCreateString(iter->second.OrderRef));
            mxSetField(result, i, "UserID", mxCreateString(iter->second.UserID));
            tmp = string("") + iter->second.Direction;
            mxSetField(result, i, "Direction", mxCreateString(tmp.c_str()));
            mxSetField(result, i, "CombOffsetFlag", mxCreateString(iter->second.CombOffsetFlag));
            mxSetField(result, i, "LimitPrice", mxCreateDoubleScalar(iter->second.LimitPrice));
            mxSetField(result, i, "ExchangeID", mxCreateString(iter->second.ExchangeID));
            mxSetField(result, i, "OrderSysID", mxCreateString(iter->second.OrderSysID));
            tmp = string("") + iter->second.OrderStatus;
            mxSetField(result, i, "OrderStatus", mxCreateString(tmp.c_str()));
            mxSetField(result, i, "FrontID", mxCreateDoubleScalar(iter->second.FrontID));
            mxSetField(result, i, "SessionID", mxCreateDoubleScalar(iter->second.SessionID));
            ++i;
        }
    }
    else
    {
        mwSize dims[2] = {1, 1};
        result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
        map<pair<int, pair<int, string> >, CThostFtdcOrderField>::iterator iter;
        iter = data.find(order);
        if(iter == data.end())
            result = mxCreateDoubleScalar(0);
        else
        {
            string tmp;
            mxSetField(result, 0, "BrokerID", mxCreateString(iter->second.BrokerID));
            mxSetField(result, 0, "InvestorID", mxCreateString(iter->second.InvestorID));
            mxSetField(result, 0, "InstrumentID", mxCreateString(iter->second.InstrumentID));
            mxSetField(result, 0, "OrderRef", mxCreateString(iter->second.OrderRef));
            mxSetField(result, 0, "UserID", mxCreateString(iter->second.UserID));
            tmp = string("") + iter->second.Direction;
            mxSetField(result, 0, "Direction", mxCreateString(tmp.c_str()));
            mxSetField(result, 0, "CombOffsetFlag", mxCreateString(iter->second.CombOffsetFlag));
            mxSetField(result, 0, "LimitPrice", mxCreateDoubleScalar(iter->second.LimitPrice));
            mxSetField(result, 0, "ExchangeID", mxCreateString(iter->second.ExchangeID));
            mxSetField(result, 0, "OrderSysID", mxCreateString(iter->second.OrderSysID));
            tmp = string("") + iter->second.OrderStatus;
            mxSetField(result, 0, "OrderStatus", mxCreateString(tmp.c_str()));
            mxSetField(result, 0, "FrontID", mxCreateDoubleScalar(iter->second.FrontID));
            mxSetField(result, 0, "SessionID", mxCreateDoubleScalar(iter->second.SessionID));
        }
    }
    return result;
}

//转换报单至CPP格式，用于撤单操作。
void MxToOrder(CThostFtdcOrderField &order, mxArray *data)
{
    char *bufBrokerID, *bufInvestorID, *bufOrderRef, *bufExchangeID, *bufOrderSysID, *bufInstrumentID;
    //获取matlab数据
    mxArray *BrokerID = mxGetField(data, 0, "BrokerID");
    mxArray *OrderRef = mxGetField(data, 0, "OrderRef");
    mxArray *ExchangeID = mxGetField(data, 0, "ExchangeID");
    mxArray *OrderSysID = mxGetField(data, 0, "OrderSysID");
    mxArray *InstrumentID = mxGetField(data, 0, "InstrumentID");
    mxArray *InvestorID = mxGetField(data, 0, "InvestorID");
    //获取空间大小
    mwSize lenBrokerID = mxGetN(BrokerID)*sizeof(mxChar)+1;
    mwSize lenOrderRef = mxGetN(OrderRef)*sizeof(mxChar)+1;
    mwSize lenExchangeID = mxGetN(ExchangeID)*sizeof(mxChar)+1;
    mwSize lenOrderSysID = mxGetN(OrderSysID)*sizeof(mxChar)+1;
    mwSize lenInstrumentID = mxGetN(InstrumentID)*sizeof(mxChar)+1;
    mwSize lenInvestorID = mxGetN(InvestorID)*sizeof(mxChar)+1;
    //开辟空间
    bufBrokerID = (char *)mxMalloc(lenBrokerID);
    bufOrderRef = (char *)mxMalloc(lenOrderRef);
    bufExchangeID = (char *)mxMalloc(lenExchangeID);
    bufOrderSysID = (char *)mxMalloc(lenOrderSysID);
    bufInstrumentID = (char *)mxMalloc(lenInstrumentID);
    bufInvestorID = (char *)mxMalloc(lenInvestorID);
    //复制数据
    mxGetString(BrokerID, bufBrokerID, lenBrokerID);
    strcpy(order.BrokerID, bufBrokerID);
    mxGetString(OrderRef, bufOrderRef, lenOrderRef);
    strcpy(order.OrderRef, bufOrderRef);
    mxGetString(ExchangeID, bufExchangeID, lenExchangeID);
    strcpy(order.ExchangeID, bufExchangeID);
    mxGetString(OrderSysID, bufOrderSysID, lenOrderSysID);
    strcpy(order.OrderSysID, bufOrderSysID);
    mxGetString(InstrumentID, bufInstrumentID, lenInstrumentID);
    strcpy(order.InstrumentID, bufInstrumentID);
    mxGetString(InvestorID, bufInvestorID, lenInvestorID);
    strcpy(order.InvestorID, bufInvestorID);
    
    order.SessionID = (int)mxGetScalar(mxGetField(data, 0, "SessionID"));
    order.FrontID = (int)mxGetScalar(mxGetField(data, 0, "FrontID"));
    //释放空间
    mxFree(bufBrokerID);
    mxFree(bufOrderRef);
    mxFree(bufExchangeID);
    mxFree(bufOrderSysID);
    mxFree(bufInstrumentID);
    mxFree(bufInvestorID);
}

//转换持仓数据
mxArray *GetPositionData(map<pair<string, char>, CThostFtdcInvestorPositionField> &data, string inst = "")
{
    mxArray *result;
    const char *field_names[] = {"BrokerID", "InvestorID", "InstrumentID", "PosiDirection", "PositionDate",
    "YdPosition", "Position", "OpenVolume", "CloseVolume", "PositionCost",
    "CloseProfit", "PositionProfit", "TodayPosition", "UseMargin"};
    if(inst.size() == 0)
    {
        int size = data.size();
        mwSize dims[2] = {1, size};
        result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
        map<pair<string, char>, CThostFtdcInvestorPositionField>::iterator iter;
        int i = 0;
        for(iter = data.begin(); iter != data.end(); ++iter)
        {
            string tmp;
            mxSetField(result, i, "BrokerID", mxCreateString(iter->second.BrokerID));
            mxSetField(result, i, "InvestorID", mxCreateString(iter->second.InvestorID));
            mxSetField(result, i, "InstrumentID", mxCreateString(iter->second.InstrumentID));
            tmp = string("") + iter->second.PosiDirection;
            mxSetField(result, i, "PosiDirection", mxCreateString(tmp.c_str()));
            tmp = string("") + iter->second.PositionDate;
            mxSetField(result, i, "PositionDate", mxCreateString(tmp.c_str()));
            mxSetField(result, i, "YdPosition", mxCreateDoubleScalar(iter->second.YdPosition));
            mxSetField(result, i, "Position", mxCreateDoubleScalar(iter->second.Position));
            mxSetField(result, i, "OpenVolume", mxCreateDoubleScalar(iter->second.OpenVolume));
            mxSetField(result, i, "CloseVolume", mxCreateDoubleScalar(iter->second.CloseVolume));
            mxSetField(result, i, "PositionCost", mxCreateDoubleScalar(iter->second.PositionCost));
            mxSetField(result, i, "CloseProfit", mxCreateDoubleScalar(iter->second.CloseProfit));
            mxSetField(result, i, "PositionProfit", mxCreateDoubleScalar(iter->second.PositionProfit));
            mxSetField(result, i, "TodayPosition", mxCreateDoubleScalar(iter->second.TodayPosition));
            mxSetField(result, i, "UseMargin", mxCreateDoubleScalar(iter->second.UseMargin));
            ++i;
        }
    }
    else
    {
        int size = 0;
        for(int j = 1; j <= 3; ++j)
        {
            pair<string, char> p = make_pair(inst, char(j+48));
            if( data.find(p) != data.end() )
            {
                ++size;
            }
        }
        mwSize dims[2] = {1, size};
        result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
        map<pair<string, char>, CThostFtdcInvestorPositionField>::iterator iter;
        int i = 0;
        
        for(int j = 1; j <= 3; ++j)
        {
            pair<string, char> p = make_pair(inst, char(j+48));
            if( (iter = data.find(p)) != data.end() )
            {
                string tmp;
                mxSetField(result, i, "BrokerID", mxCreateString(iter->second.BrokerID));
                mxSetField(result, i, "InvestorID", mxCreateString(iter->second.InvestorID));
                mxSetField(result, i, "InstrumentID", mxCreateString(iter->second.InstrumentID));
                tmp = string("") + iter->second.PosiDirection;
                mxSetField(result, i, "PosiDirection", mxCreateString(tmp.c_str()));
                tmp = string("") + iter->second.PositionDate;
                mxSetField(result, i, "PositionDate", mxCreateString(tmp.c_str()));
                mxSetField(result, i, "YdPosition", mxCreateDoubleScalar(iter->second.YdPosition));
                mxSetField(result, i, "Position", mxCreateDoubleScalar(iter->second.Position));
                mxSetField(result, i, "OpenVolume", mxCreateDoubleScalar(iter->second.OpenVolume));
                mxSetField(result, i, "CloseVolume", mxCreateDoubleScalar(iter->second.CloseVolume));
                mxSetField(result, i, "PositionCost", mxCreateDoubleScalar(iter->second.PositionCost));
                mxSetField(result, i, "CloseProfit", mxCreateDoubleScalar(iter->second.CloseProfit));
                mxSetField(result, i, "PositionProfit", mxCreateDoubleScalar(iter->second.PositionProfit));
                mxSetField(result, i, "TodayPosition", mxCreateDoubleScalar(iter->second.TodayPosition));
                mxSetField(result, i, "UseMargin", mxCreateDoubleScalar(iter->second.UseMargin));
                ++i;
            }
        }
    }
    return result;
}


mxArray *GetInstInfo(vector<CThostFtdcInstrumentField> &data)
{
    mxArray *result;
    int size = data.size();
    mwSize dims[2] = {1, size};
    const char *field_names[] = {"InstrumentID", "ExchangeID", "InstrumentName", "ExchangeInstID", "DeliveryYear",
    "DeliveryMonth", "PriceTick", "CreateDate", "OpenDate", "ExpireDate",
    "IsTrading"};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    for(int i = 0; i < size; ++i)
    {
        mxSetField(result, i, "InstrumentID", mxCreateString(data[i].InstrumentID));
        mxSetField(result, i, "ExchangeID", mxCreateString(data[i].ExchangeID));
        mxSetField(result, i, "InstrumentName", mxCreateString(data[i].InstrumentName));
        mxSetField(result, i, "ExchangeInstID", mxCreateString(data[i].ExchangeInstID));
        mxSetField(result, i, "DeliveryYear", mxCreateDoubleScalar(data[i].DeliveryYear));
        mxSetField(result, i, "DeliveryMonth", mxCreateDoubleScalar(data[i].DeliveryMonth));
        mxSetField(result, i, "PriceTick", mxCreateDoubleScalar(data[i].PriceTick));
        mxSetField(result, i, "CreateDate", mxCreateString(data[i].CreateDate));
        mxSetField(result, i, "OpenDate", mxCreateString(data[i].OpenDate));
        mxSetField(result, i, "ExpireDate", mxCreateString(data[i].ExpireDate));
        mxSetField(result, i, "IsTrading", mxCreateDoubleScalar(data[i].IsTrading));
    }
    return result;
}

mxArray *GetErrorInfo(vector<string> &data)
{
    mxArray *result;
    int size = data.size();
    mwSize dims[2] = {size, 1};
    result = mxCreateCellArray(2, dims);
    for(int i = 0; i < size; ++i)
    {
        mxSetCell(result, i, mxCreateString(data[i].c_str()) );
    }
    return result;
}
#endif