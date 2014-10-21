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

% MUTUAL_INFORMATION_NAIVE
% A mutual information estimate from samples.
%
% I = mutual_information_naive(S, bins)
%
% where
%
% S is a real (m x n)-matrix that contains n samples of an
% m-dimensional signal.
%
% BINS determines the number of bins to use for 1d
% distribution estimation. Default 100.

% Description: Naive mutual information estimation
% Documentation: tim_matlab.txt

function I = mutual_information_naive(S, bins)

if nargin < 1
    error('Not enough input arguments.');
end

if nargin > 2
    error('Too many input arguments.');
end

if nargout > 1
    error('Too many output arguments.');
end

if nargin < 2
    bins = 100;
end

if ~isa(S, 'double')
    error('S must be of type double.');
end

if size(bins, 1) ~= 1 || ...
   size(bins, 2) ~= 1
    error('BINS must be a scalar integer.');
end

I = timMutualInformationNaive(S, bins);
