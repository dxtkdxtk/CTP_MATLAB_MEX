function res = GetInstrumentInfo(inst)
%GETINSTRUMENTINFO �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
if(~ischar(inst))
    error('�������ʹ���');
end
res = TraderMain(5, inst);

end

