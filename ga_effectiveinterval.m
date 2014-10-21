function[effinterval] = ga_effectiveinterval(interval, timeinterval, offset)

max_right_value = length(interval);
if and(timeinterval > 0, timeinterval < length(interval))
    max_right_value = timeinterval;
end

full_interval = interval(1:max_right_value);
FitnessFunction = @(x) ga_negentropy_fitness(x, full_interval);
numberOfVariables = 2;
A = [1 -1];
b = [-10];
LB = [1 1];
UB = [max_right_value max_right_value];
ConstraintFunction = @ga_negentropy_constraint;
IntCon = [1,2];
opts = gaoptimset('StallGenLimit',50,'TolFun',1e-10, 'Generations',300, 'Display', 'off');
[x,fval] = ga(FitnessFunction, numberOfVariables, A, b, [], [], LB, UB, ConstraintFunction, IntCon,opts);
effinterval = struct('negentropy', -fval, 'left', x(1), 'right', x(2), 'offset', offset)