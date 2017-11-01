function [T] = tmatrix_from_mdh(a, alpha, d, theta)
    T = [cosd(theta), -sind(theta), 0, a;
        sind(theta)*cosd(alpha), cosd(theta)*cosd(alpha), -sind(alpha), -1*d*sind(alpha);
        sind(theta)*sind(alpha), cosd(theta)*sind(alpha), cosd(alpha), d*cosd(alpha);
        0, 0, 0, 1];
end