%Cartesian Plane Min Distance Graph

%Clear All 
%clear all;
clc;
close all;

%Import in Data
load('data', '-mat');

%find closest object distance(2nd row in data) + angle(1st row in data); 
[pos, ind] = min(data(2,:));
min_angle = deg2rad(data(1,ind));

%set r and theta
r = data(2,:);
theta = deg2rad(data(1,:));

%initialize figure object(plot)
figure(1);

%plot raw data in polar coords
polarplot(theta, r, 'LineWidth', 2);

%keep plot active and mutable 
hold on;

%keep theta axis from 0-180
thetalim([0,180]);

%add marker to indicate where min distance is 
polarplot(min_angle, pos, '.', 'MarkerSize', 50);

%title for plot
title('Object Distance Polar');



