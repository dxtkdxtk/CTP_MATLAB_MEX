function order = GetOrder(varargin)
%GETORDER 获取报单
% 获取所有报单：order = GETORDER;
% 获取当下连接报单：order = GETORDER(orderref); orderref为报单引用数字
% 获取指定连接报单：order = GETORDER(frontid, session, orderref); 全部参数为数字
% 若不存在order，则order返回0
if(nargin == 0)
    order = TraderMain(7);
elseif (nargin == 1)
    if(~isnumeric(varargin{1}))
        error('输入必须为数字!');
    end
    order = TraderMain(7, num2str(varargin{1}));
elseif (nargin == 3)
    if(~isnumeric(varargin{1}) || ~isnumeric(varargin{2}) || ~isnumeric(varargin{3}))
        error('输入必须全部为数字!');
    end
    order = TraderMain(7, varargin{1}, varargin{2}, num2str(varargin{3}));
else
    error('参数个数错误!');
end

end

