function writePos(n,deg)
DEFAULT_PORTNUM = 5;
DEFAULT_BAUDNUM = 1;

pause on

if libisloaded('dynamixel') == false
    loadlibrary('dynamixel','dynamixel.h');
end
res = calllib('dynamixel','dxl_initialize',DEFAULT_PORTNUM,DEFAULT_BAUDNUM);
if res == 1
    goalPos = 4096*deg/360;
    goalPos = mod(goalPos + 2048,4096);
    current_speed = calllib('dynamixel', 'dxl_read_word', n, 32);
%     calllib('dynamixel', 'dxl_write_word', 2, 32, 1);
    moveMotor(n,goalPos);
else
    disp('Failed to connect.')
end

% calllib('dynamixel','dxl_terminate');
% unloadlibrary('dynamixel');
end