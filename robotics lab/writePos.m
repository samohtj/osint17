function writePos(n,deg)
DEFAULT_PORTNUM = 5;
DEFAULT_BAUDNUM = 1;

pause on

loadlibrary('dynamixel','dynamixel.h');
res = calllib('dynamixel','dxl_initialize',DEFAULT_PORTNUM,DEFAULT_BAUDNUM);
if res == 1
    goalPos = 4096*deg/360;
    goalPos = mod(goalPos + 2048,4096);
    moveMotor(n,goalPos);
else
    disp('Failed to connect.')
end

% calllib('dynamixel','dxl_terminate');
% unloadlibrary('dynamixel');
end