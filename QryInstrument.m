function QryInstrument(varargin)
%QRYINSTRUMENT 查询合约信息
inst = '';
if(nargin > 1)
    error('参数个数必须小于2');
elseif (nargin == 1)
    inst = varargin{1};
    if(~ischar(inst))
        error('参数类型错误');
    end
end

TraderMain(4, inst);

disp('获取合约信息完成');

end

