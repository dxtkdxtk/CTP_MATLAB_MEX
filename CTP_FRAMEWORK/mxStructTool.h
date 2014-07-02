#include "Connection.h"
#include "mex.h"
#include "matrix.h"

//获取实时合约数据
mxArray *GetMarketData(const CThostFtdcDepthMarketDataField &data)
{
    mwSize dims[2] = {1, 1};
            const char *field_names[] = {"TradingDay", "InstrumentID", "LastPrice", "PreSettlementPrice",\
                                                            "PreClosePrice", "PreOpenInterest", "OpenPrice", "HighestPrice", \
                                                            "LowestPrice", "Volume", "OpenInterest", "ClosePrice", "SettlementPrice",\
                                                            "UpperLimitPrice", "LowerLimitPrice", "PreDelta", "CurrDelta", "UpdateTime", \
                                                            "BidPrice1", "BidVolume1", "AskPrice1", "AskVolume1", "AveragePrice", "ActionDay"};
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
            return result;
}

//获取当前未结束报单
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
        string dire;
        dire += data[i].Direction;
        mxSetField(result, i, "BrokerID", mxCreateString(data[i].BrokerID));
        mxSetField(result, i, "InvestorID", mxCreateString(data[i].InvestorID));
        mxSetField(result, i, "InstrumentID", mxCreateString(data[i].InstrumentID));
        mxSetField(result, i, "OrderRef", mxCreateString(data[i].OrderRef));
        mxSetField(result, i, "UserID", mxCreateString(data[i].UserID));
        mxSetField(result, i, "Direction", mxCreateString(dire.c_str()));
        mxSetField(result, i, "CombOffsetFlag", mxCreateString(data[i].CombOffsetFlag));
        mxSetField(result, i, "LimitPrice", mxCreateDoubleScalar(data[i].LimitPrice));
        mxSetField(result, i, "ExchangeID", mxCreateString(data[i].ExchangeID));
        mxSetField(result, i, "OrderSysID", mxCreateString(data[i].OrderSysID));
        dire = string("") + data[i].OrderStatus;
        mxSetField(result, i, "OrderStatus", mxCreateString(dire.c_str()));
        mxSetField(result, i, "FrontID", mxCreateDoubleScalar(data[i].FrontID));
        mxSetField(result, i, "SessionID", mxCreateDoubleScalar(data[i].SessionID));
    }
    return result;
}

void MxToOrder(CThostFtdcOrderField &order, mxArray *data)
{
    char *bufBrokerID, *bufInvestorID, *bufOrderRef, *bufExchangeID, *bufOrderSysID, *bufInstrumentID;
    
    mxArray *BrokerID = mxGetField(data, 0, "BrokerID");
    mxArray *OrderRef = mxGetField(data, 0, "OrderRef");
    mxArray *ExchangeID = mxGetField(data, 0, "ExchangeID");
    mxArray *OrderSysID = mxGetField(data, 0, "OrderSysID");
    mxArray *InstrumentID = mxGetField(data, 0, "InstrumentID");
    mxArray *InvestorID = mxGetField(data, 0, "InvestorID");
    
    mwSize lenBrokerID = mxGetN(BrokerID)*sizeof(mxChar)+1;
    mwSize lenOrderRef = mxGetN(OrderRef)*sizeof(mxChar)+1;
    mwSize lenExchangeID = mxGetN(ExchangeID)*sizeof(mxChar)+1;
    mwSize lenOrderSysID = mxGetN(OrderSysID)*sizeof(mxChar)+1;
    mwSize lenInstrumentID = mxGetN(InstrumentID)*sizeof(mxChar)+1;
    mwSize lenInvestorID = mxGetN(InvestorID)*sizeof(mxChar)+1;
    
    bufBrokerID = (char *)mxMalloc(lenBrokerID);
    bufOrderRef = (char *)mxMalloc(lenOrderRef);
    bufExchangeID = (char *)mxMalloc(lenExchangeID);
    bufOrderSysID = (char *)mxMalloc(lenOrderSysID);
    bufInstrumentID = (char *)mxMalloc(lenInstrumentID);
    bufInvestorID = (char *)mxMalloc(lenInvestorID);
    
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
    
    mxFree(bufBrokerID);
    mxFree(bufOrderRef);
    mxFree(bufExchangeID);
    mxFree(bufOrderSysID);
    mxFree(bufInstrumentID);
    mxFree(bufInvestorID);
}
