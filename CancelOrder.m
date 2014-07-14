function CancelOrder(order)
%CANCELORDER 撤单，可以使用orderref撤单，或者用报单结构撤单
if(isnumeric(order))
    TraderMain(11, num2str(order));
else
    TraderMain(8, order);
end

end

