function res = GetMarketData(inst)
%GETMARKETDATA ��ȡ��������
% data = GetMarketData('IF1407');
if(~ischar(inst))
    error('�������ʹ���');
end
res = TraderMain(5, inst);

end

