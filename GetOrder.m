function order = GetOrder(orderref)
%GETORDER ��ȡ��ǰ����ָ������
if(~isnumeric(orderref))
    error('�������Ϊ����');
end
order = TraderMain(12, num2str(orderref));
end

