function order = GetOrder(varagin)
%GETORDER 获取报单
% 获取所有报单：order = GETORDER;
% 获取当下连接报单：order = GETORDER(orderref); orderref为报单引用数字
% 获取指定连接报单：order = GETORDER(frontid, session, orderref); 全部参数为数字
if(nargin == 0)
    order = TraderMain(7);
elseif (nargin == 1)
    if(~isnumeric(varagin{1}))
        error('输入必须为数字!');
    end
    order = TraderMain(12, num2str(varagin{1}));
elseif (nargin == 3)
    if(~isnumeric(varagin{1}) || ~isnumeric(varagin{2}) || ~isnumeric(varagin{3}))
        error('输入必须全部为数字!');
    end
    order = TraderMain(13, varagin{1}, varagin{2}, num2str(varagin{3}));
else
    error('参数个数错误!');
end

end

