function CancelOrder(order)
%CANCELORDER ����
if(isnumeric(order))
    TraderMain(11, order);
else
    TraderMain(8, order);
end

end

