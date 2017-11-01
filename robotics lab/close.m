function [ ] = close( )

   calllib('dynamixel', 'dxl_write_word', 5, 30, 790);
end

