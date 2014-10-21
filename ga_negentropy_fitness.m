function result = ga_negentropy_fitness(x,full_interval)

curinterval = full_interval(x(1) : x(2));  
%negative for maximization
%result = -((kurt(curinterval))^2);
%result = -calcnegentropy(curinterval);
result = -((kurtosis(curinterval))^2);