%Approximation of negentropy:
%J(x)=1/12(E(x^3))^2 + 1/48(kurt(x))^2 

function[negentropy] = calcnegentropy(interval)
%m3 = moment(interval, 3);
%k = kurtosis(interval);
%negentropy = (1/12)*(m3^2) + (1/48)*(k^2);

m2 = mean(interval.^2);
m3 = mean(interval.^3);
m4 = mean(interval.^4);
k = m4 - 3*(m2^2);
negentropy = (1/12)*(m3^2) + (1/48)*(k^2);