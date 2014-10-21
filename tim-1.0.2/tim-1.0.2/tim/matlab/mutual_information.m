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

% MUTUAL_INFORMATION 
% A mutual information estimate from samples.
%
% I = mutual_information(X, Y, xLag, yLag, k, threads)
%
% where
%
% X and Y are arbitrary-dimensional cell-arrays whose linearizations
% contain q trials of signals X and Y, respectively.
%
% XLAG and YLAG are the lags in samples that are applied to 
% signals X and Y, respectively.
%
% K determines which k:th nearest neighbor the algorithm
% uses for estimation. Default 1.
%
% THREADS determines the number of threads to use for parallelization.
% To fully take advantage of multiple cores in your machine, set this
% to the number of cores in your machine. Note however that this makes 
% your computer unresponsive to other tasks. When you need responsiveness, 
% spare one core for other work. Default maxNumCompThreads.
%
% Each signal is a real (m x n)-matrix that contains n samples of an
% m-dimensional signal. The signals contained in X (Y) must all have equal
% dimensionality, but their number of samples may vary. 
% If the number of samples varies with trials, the function uses 
% the minimum sample count among the trials of X and Y.
% The number of trials in X and Y must be equal.

% Description: Mutual information estimation
% Documentation: tim_matlab.txt

function I = mutual_information(X, Y, xLag, yLag, k, threads)

if nargin < 2
    error('Not enough input arguments.');
end
 
if nargin >= 3 && nargin < 4
    error('Lags must be specified all at once to avoid errors.');
end

if nargin < 3
    xLag = 0;
    yLag = 0;
end

if nargin < 5
    k = 1;
end

if nargin < 6
    threads = maxNumCompThreads;
end

if ~iscell(X) || ~iscell(Y)
    error('X or Y is not a cell-array.');
end

if numel(X) ~= numel(Y)
    error('The number of trials in X and Y differ.');
end

% Pass parameter error checking to entropy_combination.

I = entropy_combination(...
    [X(:), Y(:)]', ...
    [1, 1, 1; 2, 2, 1], [xLag, yLag], k, threads);
