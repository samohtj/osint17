function [error] = question6()
    
    a1 = [20;
        0;
        35.814
        ;
        100];
    b1 = [39.878;
        0;
        24.3;
        100];
    c1 = [15.24;
        3;
        21.7;
        100]
    d1 = [29.5;
        -32.258;
        19.4;
        100];
    measured = [a1 b1 c1 d1] .* 0.01;
    
    a2 = fk([0,0,0]);
    b2 = fk([0,-45,45]);
    c2 = fk([10,0,-45]);
    d2 = fk([-45,-45,30]);
    calculated = [a2 b2 c2 d2];
    
    error = (measured-calculated);

end


% ERRORS
% Trial 1: [0 0 0] 
% X: 2.5cm
% Y: 0
% Z: 1.5cm

% Trial 2: [0 -45 45]
% X: 1.1cm
% Y: 0
% Z: 3.7cm

% Trial 3: [10 0 -45] 
% X: 1.0cm
% Y: 0.1cm
% Z: 1.1cm

% Trial 4: [-45 -45 30] 
% X: 1.0cm
% Y: 3.8cm
% Z: 3.3cm
