function position = GetPosition(varargin)
%GETPOSITION 获取持仓信息
if(nargin == 0)
    position = TraderMain(9);
elseif (nargin == 1)
    if(~ischar(varargin{1}))
        error('参数类型错误！');
    end
    position = TraderMain(14, varargin{1});
else
    error('参数个数错误！');
end


end

