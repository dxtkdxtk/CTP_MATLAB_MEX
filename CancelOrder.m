function CancelOrder(order)
%CANCELORDER ³·µ¥
if(isnumeric(order))
    TraderMain(11, order);
else
    TraderMain(8, order);
end

end

