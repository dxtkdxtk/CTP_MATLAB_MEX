function CancelOrder(order)
%CANCELORDER ����������ʹ��orderref�����������ñ����ṹ����
if(isnumeric(order))
    TraderMain(11, num2str(order));
else
    TraderMain(8, order);
end

end

