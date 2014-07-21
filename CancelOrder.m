function CancelOrder(varargin)
%CANCELORDER 撤单，可以使用orderref撤单，或者用报单结构撤单
%撤指定单: CANCELORDER(orderInfo);
%撤orderref单: CANCELORDER(orderref);
if(nargin == 1)
    if(isnumeric(varargin{1}))
        TraderMain(8, num2str(varargin{1}));
    else
        TraderMain(8, varargin{1});
    end
elseif(nargin == 3)
    if(~isnumeric(varargin{1}) || ~isnumeric(varargin{2}) || ~isnumeric(varargin{3}))
        error('frontid, sessionid, orderref必须为数字!');
    end
    TraderMain(8, varargin{1}, varargin{2}, num2str(varargin{3}));
end

end

