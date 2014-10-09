function res = GetMarketData(varargin)
%GETMARKETDATA 获取行情数据
% data = GetMarketData('IF1407');
if(nargin == 0)
    res = TraderMain(5);
elseif(nargin == 1)
    res = TraderMain(5, varargin{1});
else
    error('输入参数个数错误');
end


end

