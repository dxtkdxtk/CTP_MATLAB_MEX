function res = GetMarketData(inst)
%GETMARKETDATA 获取行情数据
% data = GetMarketData('IF1407');
if(~ischar(inst))
    error('输入类型错误');
end
res = TraderMain(5, inst);

end

