function [ ] = open( )

    calllib('dynamixel', 'dxl_write_word', 5, 30, 512);

end

