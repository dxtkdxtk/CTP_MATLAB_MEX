function CancelOrder(varargin)
%CANCELORDER ����������ʹ��orderref�����������ñ����ṹ����
%��ָ����: CANCELORDER(orderInfo);
%��orderref��: CANCELORDER(orderref);
%��ָ�����ӵ�: CANCELORDER(frontid, sessionid, orderref);
if(nargin == 1)
    if(isnumeric(varargin{1}))
        TraderMain(8, num2str(varargin{1}));
    else
        TraderMain(8, varargin{1});
    end
elseif(nargin == 3)
    if(~isnumeric(varargin{1}) || ~isnumeric(varargin{2}) || ~isnumeric(varargin{3}))
        error('frontid, sessionid, orderref����Ϊ����!');
    end
    TraderMain(8, varargin{1}, varargin{2}, num2str(varargin{3}));
end

end

