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

//转换报单数据
mxArray *GetOrderData(vector<CThostFtdcOrderField> &data)
{
    mxArray *result;
    int size = data.size();
    mwSize dims[2] = {1, size};
    const char *field_names[] = {"BrokerID", "InvestorID", "InstrumentID", "OrderRef", "UserID", "Direction", 
                                                   "CombOffsetFlag", "LimitPrice", "ExchangeID", "OrderSysID", 
                                                   "OrderStatus", "FrontID", "SessionID"};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    for(int i = 0; i < size; ++i)
    {
        string tmp;
        mxSetField(result, i, "BrokerID", mxCreateString(data[i].BrokerID));
        mxSetField(result, i, "InvestorID", mxCreateString(data[i].InvestorID));
        mxSetField(result, i, "InstrumentID", mxCreateString(data[i].InstrumentID));
        mxSetField(result, i, "OrderRef", mxCreateString(data[i].OrderRef));
        mxSetField(result, i, "UserID", mxCreateString(data[i].UserID));
        tmp = string("") + data[i].Direction;
        mxSetField(result, i, "Direction", mxCreateString(tmp.c_str()));
        mxSetField(result, i, "CombOffsetFlag", mxCreateString(data[i].CombOffsetFlag));
        mxSetField(result, i, "LimitPrice", mxCreateDoubleScalar(data[i].LimitPrice));
        mxSetField(result, i, "ExchangeID", mxCreateString(data[i].ExchangeID));
        mxSetField(result, i, "OrderSysID", mxCreateString(data[i].OrderSysID));
        tmp = string("") + data[i].OrderStatus;
        mxSetField(result, i, "OrderStatus", mxCreateString(tmp.c_str()));
        mxSetField(result, i, "FrontID", mxCreateDoubleScalar(data[i].FrontID));
        mxSetField(result, i, "SessionID", mxCreateDoubleScalar(data[i].SessionID));
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
mxArray *GetPositionData(vector<CThostFtdcInvestorPositionField> &data)
{
    mxArray *result;
    int size = data.size();
    mwSize dims[2] = {1, size};
    const char *field_names[] = {"BrokerID", "InvestorID", "InstrumentID", "PosiDirection", "PositionDate",
                                                   "YdPosition", "Position", "OpenVolume", "CloseVolume", "PositionCost", 
                                                   "CloseProfit", "PositionProfit", "TodayPosition"};
    result = mxCreateStructArray(2, dims, sizeof(field_names)/sizeof(*field_names), field_names);
    for(int i = 0; i < size; ++i)
    {
        string tmp;
        mxSetField(result, i, "BrokerID", mxCreateString(data[i].BrokerID));
        mxSetField(result, i, "InvestorID", mxCreateString(data[i].InvestorID));
        mxSetField(result, i, "InstrumentID", mxCreateString(data[i].InstrumentID));
        tmp = string("") + data[i].PosiDirection;
        mxSetField(result, i, "PosiDirection", mxCreateString(tmp.c_str()));
        tmp = string("") + data[i].PositionDate;
        mxSetField(result, i, "PositionDate", mxCreateString(tmp.c_str()));
        mxSetField(result, i, "YdPosition", mxCreateDoubleScalar(data[i].YdPosition));
        mxSetField(result, i, "Position", mxCreateDoubleScalar(data[i].Position));
        mxSetField(result, i, "OpenVolume", mxCreateDoubleScalar(data[i].OpenVolume));
        mxSetField(result, i, "CloseVolume", mxCreateDoubleScalar(data[i].CloseVolume));
        mxSetField(result, i, "PositionCost", mxCreateDoubleScalar(data[i].PositionCost));
        mxSetField(result, i, "CloseProfit", mxCreateDoubleScalar(data[i].CloseProfit));
        mxSetField(result, i, "PositionProfit", mxCreateDoubleScalar(data[i].PositionProfit));
        mxSetField(result, i, "TodayPosition", mxCreateDoubleScalar(data[i].TodayPosition));
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
#endif