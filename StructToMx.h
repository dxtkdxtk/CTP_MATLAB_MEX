#include "Connection.h"
#include "mex.h"
#include "matrix.h"

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