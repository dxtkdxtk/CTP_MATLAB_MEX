function res = GetMarketData(varargin)
%GETMARKETDATA ��ȡ��������
% data = GetMarketData('IF1407');
if(nargin == 0)
    res = TraderMain(5);
elseif(nargin == 1)
    res = TraderMain(5, varargin{1});
else
    error('���������������');
end


end

