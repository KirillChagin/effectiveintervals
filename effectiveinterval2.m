function[effinterval] = effectiveinterval2(interval, timeinterval, offset)

if and(timeinterval > 0, timeinterval < length(interval))
    max_right_value = timeinterval;
else
    max_right_value = length(interval);
end

avg = calcnegentropy(interval);

sumbest = 0;
startbest = 1;
endbest = 1;

sumtemp = 0;
starttemp = 1;

for i=2:max_right_value
    sumtemp = sumtemp + calcnegentropy(interval(starttemp : i)) - avg;
    if sumbest < sumtemp
        sumbest = sumtemp;
        startbest = starttemp;
        endbest = i;
    end
    
    if sumtemp < 0
        sumtemp = 0;
        starttemp = i+1;
    end
end

record = calcnegentropy(interval(startbest : endbest));

effinterval = struct('negentropy', record, 'left', startbest, 'right', endbest, 'offset', offset);