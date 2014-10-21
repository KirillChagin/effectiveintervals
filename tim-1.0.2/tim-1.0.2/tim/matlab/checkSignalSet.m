% TIM 1.0.2
% Kalle Rutanen
% http://kaba.hilvi.org
% Copyright (c) 2009, 2010
%
% This library is free software: you can redistribute it and/or modify
% it under the terms of the GNU Lesser General Public License as published 
% by the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
% 
% This library is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
% GNU Lesser General Public License for more details.
% 
% You should have received a copy of the GNU Lesser General Public License
% along with this library. If not, see <http://www.gnu.org/licenses/>.

function checkSignalSet(X)

if ~iscell(X)
    error('A signal-set is not a cell-array.');
end

% The limit for the dimension is arbitrary, but
% protects for the case when the user accidentally
% passes the transpose of the intended data.

maxDimension = 32;

signals = numel(X);

if signals == 0
	error('Signal-set is empty.');
end

dimension = size(X{1}, 1);

for i = 1 : signals
    if ~isa(X{i}, 'double')
        error('Some signal is not of type double.');
    end

    if size(X{i}, 1) ~= dimension
        error(['The dimensions of the trials do not match.']);
    end

    if size(X{i}, 1) > maxDimension
        error(['Some signal has dimension greater than ', ...
            int2str(maxDimension), '.']);
    end
end

end
