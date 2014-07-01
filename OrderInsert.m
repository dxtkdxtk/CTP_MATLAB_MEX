function OrderInsert(inst, direction, flag, volume, price)
%ORDERINSERT ÏÂµ¥²Ù×÷
if(~ischar(inst) || ~ischar(direction) || ~ischar(flag) || ~isnumeric(volume) || ~isnumeric(price))
    error('input type error');
end
TraderMain(6, inst, direction, flag, volume, price);


end

