function QryInstrument(varargin)
%QRYINSTRUMENT ��ѯ��Լ��Ϣ
inst = '';
if(nargin > 1)
    error('������������С��2');
elseif (nargin == 1)
    inst = varargin{1};
    if(~ischar(inst))
        error('�������ʹ���');
    end
end

TraderMain(4, inst);

disp('��ȡ��Լ��Ϣ���');

end

