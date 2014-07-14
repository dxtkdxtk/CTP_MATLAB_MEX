function order = GetOrder(orderref)
%GETORDER 获取当前连接指定报单
if(~isnumeric(orderref))
    error('输入必须为数字');
end
order = TraderMain(12, num2str(orderref));
end

