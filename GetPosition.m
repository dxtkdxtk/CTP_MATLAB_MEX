function position = GetPosition(varargin)
%GETPOSITION 获取持仓信息
%获取全部持仓: position = GETPOSITION;
%获取指定合约持仓: position = GETPOSITION(instrument);
if(nargin == 0)
    position = TraderMain(9);
elseif (nargin == 1)
    if(~ischar(varargin{1}))
        error('参数类型错误！');
    end
    position = TraderMain(9, varargin{1});
else
    error('参数个数错误！');
end


end

