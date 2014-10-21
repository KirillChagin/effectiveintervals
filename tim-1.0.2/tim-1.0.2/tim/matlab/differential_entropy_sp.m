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

% DIFFERENTIAL_ENTROPY_SP
% A differential entropy estimate from samples
% using Stowell-Plumbley recursive partition estimator.
%
% H = differential_entropy_sp(S)
%
% where
%
% S is an arbitrary-dimensional cell-array whose linearization contains
% q trials of a signal. Each signal is a real (m x n)-matrix that 
% contains n samples of an m-dimensional signal.

% Description: Differential entropy estimation
% Detail: Stowell-Plumbley recursive partition estimator
% Documentation: tim_matlab.txt

function H = differential_entropy_sp(S)

if nargin < 1
    error('Not enough input arguments.');
end

if nargin > 1
    error('Too many input arguments.');
end

if nargout > 1
    error('Too many output arguments.');
end

checkSignalSet(S);

if (size(S{1}, 1) > 3)
	warning('This estimator has bad accuracy for dimensions > 3!');
end

H = timDifferentialEntropySp(S);
