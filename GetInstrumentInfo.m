function res = GetInstrumentInfo(inst)
%GETINSTRUMENTINFO 此处显示有关此函数的摘要
%   此处显示详细说明
if(~ischar(inst))
    error('输入类型错误');
end
res = TraderMain(5, inst);

end

