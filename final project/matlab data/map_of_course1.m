map_matrix = zeros(95, 203);

%set boundary of outer perimter
map_matrix(:, 1) = 1;
map_matrix(:, 203) = 1;
map_matrix(1, :) = 1;
map_matrix(95, :) = 1;

%set search area boundaries
map_matrix(2:25, 46:203) = 1;
map_matrix(71:94, 46:203) = 1;

%surf(map_matrix);

map = binaryOccupancyMap(map_matrix);
show(map, 'grid');


% rover_radius_inches = ((12^2 + 10^2)^.5)/2;
% rover_radius_meters = .0254 * rover_radius_inches;
% 
% %inflate map boundaries based off of rover size
% inflated_map = copy(map);
% inflate(inflated_map,rover_radius_inches);
% show(inflated_map, 'grid');
% 
% %Construct prm and set paramters
% prm = mobileRobotPRM;
% prm.Map = inflated_map;
% prm.NumNodes = 500; %more nodes = better path, but greater computation time
% prm.ConnectionDistance = 10; %greatest distance between two connected nodes on map
% 
% %set starting and ending locations
% startLocation = [170 45];
% endLocation = [10 80];
% 
% path = findpath(prm, startLocation, endLocation)
% show(prm)

