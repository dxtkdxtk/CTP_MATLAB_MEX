function Subscribe(varargin)
% 订阅行情，逗号或者分号隔开
inst = '';
if(nargin > 1)
    error('参数个数必须小于2');
elseif(nargin == 1)
    inst = varargin{1};
    if(~ischar(inst))
        error('订阅合约类型错误');
    end
end
TraderMain(3, inst);


end

