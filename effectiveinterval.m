function[effinterval] = effectiveinterval(interval, timeinterval, offset)

record = calcnegentropy(interval);
leftrecord = 1;

rightrecord = length(interval);
if and(timeinterval > 0, timeinterval < length(interval))
    rightrecord = timeinterval;
end


%brute-force search
%
%for i=1:length(interval)
%    for j=1:length(interval)-i
%        curinterval = interval(j:i);
%        result = calcnegentropy(curinterval);
%        if (result > record)
%            record = result;
%            leftrecord = j;
%            rightrecord = i;
%        end
%    end
%end

%Lazarenko's algorithm

stepdiv = 2;
step = rightrecord;
while (step > 1)
    step = fix(step / stepdiv);
    left = leftrecord;
    right = rightrecord;
    %left - step
    if (leftrecord > step)
        curinterval = interval(leftrecord - step : rightrecord - step);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            left = leftrecord - step;
            right = rightrecord - step;
        end 
        
        curinterval = interval(leftrecord - step : rightrecord);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            left = leftrecord - step;
        end
        
        if ((rightrecord + step) <= length(interval))
            curinterval = interval(leftrecord - step : rightrecord + step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord - step;
                right = rightrecord + step;
            end 
        end
    end
    %left
    if ((rightrecord - step) > leftrecord)
        curinterval = interval(leftrecord : rightrecord - step);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            right = rightrecord - step;
        end 
    end

    if ((rightrecord + step) <= length(interval))
        curinterval = interval(leftrecord : rightrecord + step);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            right = rightrecord + step;
        end 
    end
    %left + step
    if ((leftrecord + step) < length(interval))
        if ((rightrecord - step) > (leftrecord + step)) 
            curinterval = interval(leftrecord + step : rightrecord - step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord + step;
                right = rightrecord - step;
            end 
        end
        
        curinterval = interval(leftrecord + step : rightrecord);
        result = calcnegentropy(curinterval);
        if (result > record)
            record = result;
            left = leftrecord + step;
        end
        
        if ((rightrecord + step) <= length(interval))
            curinterval = interval(leftrecord + step : rightrecord + step);
            result = calcnegentropy(curinterval);
            if (result > record)
                record = result;
                left = leftrecord + step;
                right = rightrecord + step;
            end 
        end
    end
    
    leftrecord = left;
    rightrecord = right;
end
effinterval = struct('negentropy', record, 'left', leftrecord, 'right', rightrecord, 'offset', offset);